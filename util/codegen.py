#!/usr/bin/python3
# vim:sw=4

"""
The code generator takes a *.in resource file and post-processes it into a re-compilable GAS compliant assembler
module, generates access providers to exposed routines and injects alternative implementations to replaced routines.
The settings are passed in a human readable json configuration file.

The script aims to support the various x86 calling conventions originally supported by the Watcom 10.x C/C++ compiler
including limited support for the big code model for __far calls and the big data model for __far pointers.
"""

__author__ = "M.A.X. Port Team"
__copyright__ = "Copyright (c) 2020 M.A.X. Port Team"
__license__ = "MIT License"
__version__ = "0.40"

import re
import sys
import os
from getopt import gnu_getopt, GetoptError
from io import StringIO
import json


class Codegen:
    debug_all = False
    underscore = False
    config_file = ""
    config = None
    input_file = ""
    output_directory = ""
    replace_function_regex = None
    replace_function_list = None
    expose_function_regex = None
    expose_function_list = None
    reference_function_regex = None
    function_list = {}
    reference_list = {}
    output_file = None
    operands = ['a', 'd', 'b', 'c']
    registers_32bit = ["%eax", "%edx", "%ebx", "%ecx"]
    registers_16bit = ["%ax", "%dx", "%bx", "%cx"]

    @staticmethod
    def print_help():
        print(
            ("Usage: %s OPTIONS <config.json>\n"
             "\n"
             "<config.json> path to configuration file\n"
             "OPTIONS:\n"
             "  -h  --help          shows this help text\n"
             "  -i  --input         input resource file to process\n"
             "  -o  --output        output directory to emit generated source files\n"
             "  -u  --underscore    prefixes symbol names with an underscore\n"
             "  -d  --debug-all     enable console log for all replaced functions\n") % (sys.argv[0]))

    @staticmethod
    def minify(file_path):
        """ Remove optional comments from JSON like configuration files and loads the resulting JSON string

        :param file_path: path to JSON like configuration file
        :return: object
        """
        with open(file_path, 'r') as f:
            json_list = json.loads('\n'.join([row for row in f.readlines() if len(row.split('//')) == 1]))
        return json_list

    def read_config(self, mode):
        """ Return a regexp that will match all the function names that are meant to be replaced or exposed
        """
        r = StringIO()

        for function in self.config["functions"]:
            if function["mode"] == mode:
                r.write(function["symbol"])
                r.write("|")
        return r.getvalue()[:-1]

    def get_replace_regex(self):
        """ Return a regexp that will match all the function names that are meant to be replaced
        """
        if self.replace_function_regex is None:
            r = StringIO()
            r.write(r"(^\s*)\b((")
            r.write(self.replace_function_list)
            r.write(r"):)(.*)")
            self.replace_function_regex = re.compile(r.getvalue())
        return self.replace_function_regex

    def get_expose_regex(self):
        """ Return a regexp that will match all the function names that are meant to be exposed
        """
        if self.expose_function_regex is None:
            r = StringIO()
            r.write(r"(^\s*)\b((")
            r.write(self.expose_function_list)
            r.write(r"):)(.*)")
            self.expose_function_regex = re.compile(r.getvalue())
        return self.expose_function_regex

    def get_reference_regex(self):
        """ Return a regexp that will match all the function names that are
            supposed to be referenced in the resource file
        """
        if self.reference_function_regex is None:
            r = StringIO()
            r.write(r"(\b(")
            r.write(self.replace_function_list)
            if r.tell() > 4:
                r.write(r"|")
            r.write(self.expose_function_list)
            r.write(r")\b)")
            self.reference_function_regex = re.compile(r.getvalue())
        return self.reference_function_regex

    def read_config_file_positions(self):
        with open(self.config_file) as f:
            for index, line in enumerate(f):
                for function in self.config["functions"]:
                    if "file_position" in function:
                        continue
                    position = line.find("\"name\": \"" + function["name"] + "\",")
                    if position != -1:
                        function["file_position"] = [index, position]
                        break

    def prefix_name(self, name):
        if not self.underscore:
            return "%s" % name
        return "_%s" % name

    @staticmethod
    def generate_out_args(f):
        if f["return"]:
            return "\"=a\"(result)"
        else:
            return ""

    @staticmethod
    def get_operand(index):
        try:
            return Codegen.operands[index]
        except IndexError:
            return 'g'

    @staticmethod
    def generate_in_args(f):
        if f["arguments_list"]:
            args = StringIO()
            for index, arg in enumerate(f["arguments_list"]):
                assert not arg["is_far"]
                args.write(" \"%s\"(%s)," % (Codegen.get_operand(index), arg["arg_name"]))
            return args.getvalue()[:-1]
        else:
            return ""

    def generate_function_body(self, f):
        n_args = len(f["arguments_list"])
        n_args_offset = -1

        if f["return"]:
            self.write_line("\t%s result;" % f["return"]["type_name"])
            self.write_line()
            n_args_offset = 0

        self.write_line("\t__asm__ __volatile__(")
        if n_args > len(Codegen.registers_32bit):
            for index in range(n_args, len(Codegen.registers_32bit), -1):
                self.write_line("\t\t\"\tpushl\t%%%i\\n\"" % (index + n_args_offset))
        self.write_line("\t\t\"\tcall\t%s\\n\"" % self.prefix_name(f["symbol"]))
        self.write_line("\t\t: /* out  */%s" % self.generate_out_args(f))
        self.write_line("\t\t: /* in   */%s" % self.generate_in_args(f))
        self.write_line("\t\t: /* clob */%s);" % "")

        if f["return"]:
            self.write_line()
            self.write_line("\treturn result;")

    def create_access_providers(self):
        file_name = "wrappers"

        self.output_file = open(self.output_directory + "/" + file_name + ".h", "w")
        self.output_file.write(self.config["copyrights"]["port"])

        self.write_line("#ifndef %s_H" % file_name.upper())
        self.write_line("#define %s_H" % file_name.upper())
        for function in self.config["functions"]:
            if function["mode"] == "expose":
                assert function["name"] != function["symbol"]
                self.write_line()

                if function["type"] == "watcall":
                    self.write_line("static inline %s {" % (function["prototype"]))
                    self.generate_function_body(function)
                    self.write_line("}")
                    self.write_line()

                elif function["type"] == "variadic" or function["type"] == "cdecl":
                    self.write_line(
                        "extern %s\t__asm(\"%s\");\n" % (function["prototype"], self.prefix_name(function["symbol"])))
                else:
                    assert False

        for variable in self.config["variables"]:
            self.write_line("extern %s;" % variable["prototype"])
            self.write_line()

        self.write_line("#endif /* %s_H */" % file_name.upper())

        self.output_file.close()
        self.output_file = None

    def create_resource_header(self):
        file_name, _ = os.path.splitext(os.path.basename(self.input_file))

        self.output_file = open(self.output_directory + "/" + file_name + ".h", "w")
        self.output_file.write(self.config["copyrights"]["port"])
        self.write_line("/* Helper macros */")
        self.write_line("#define GLOBAL(sym) .global sym")
        self.write_line("#define REPLACE(sym) REMOVED_##sym")
        self.write_line()
        self.write_line("#include \"user.h\"")
        self.write_line()
        self.write_line("/* Replaced and exposed symbols */")

        for function in self.config["functions"]:
            if function["mode"] == "replace":
                self.generate_wrapper(function)
                self.write_line()
            elif function["mode"] == "expose":
                if self.underscore:
                    self.write_line("#define %s %s\n" % (function["symbol"], self.prefix_name(function["symbol"])))
                self.write_line("GLOBAL(%s)" % (self.prefix_name(function["symbol"])))
                self.write_line()

        for variable in self.config["variables"]:
            if variable["mode"] == "expose":
                self.write_line(
                    "#define %s %s\n" % (variable["symbol"], self.prefix_name(variable["name"])))
                self.write_line("GLOBAL(%s)" % (variable["symbol"]))
                self.write_line()

        self.output_file.close()
        self.output_file = None

    def process_resource_file(self):
        file_name, _ = os.path.splitext(os.path.basename(self.input_file))

        input_file = open(self.input_file, 'r')
        self.output_file = open(self.output_directory + "/" + file_name + ".S", "w")
        self.output_file.write(self.config["copyrights"]["proprietary"])
        self.output_file.write("#include \"%s.h\"\n\n" % file_name)

        count = 0
        while True:
            line = input_file.readline().rstrip(" \t")
            count += 1
            if len(line) == 0:
                break

            m = self.get_replace_regex().match(line)
            if m:
                line = "%sREPLACE(%s):%s\n" % (m.group(1), m.group(3), m.group(4))
                if m.group(3) in self.function_list:
                    self.function_list[m.group(3)] += 1
                else:
                    self.function_list[m.group(3)] = 1

                print("%s:%i:0: warning: replaced function %s is still defined" % (
                    self.input_file, count, m.group(3)))

            m = self.get_expose_regex().match(line)
            if m:
                if m.group(3) in self.function_list:
                    self.function_list[m.group(3)] += 1
                else:
                    self.function_list[m.group(3)] = 1

            m = self.get_reference_regex().search(line)
            if m:
                if m.group(2) in self.reference_list:
                    self.reference_list[m.group(2)] += 1
                else:
                    self.reference_list[m.group(2)] = 1

            self.output_file.write(line)
        self.output_file.close()
        self.output_file = None

        self.read_config_file_positions()
        for function in self.config["functions"]:
            if function["mode"] == "expose" and not function["symbol"] in self.function_list:
                print("%s:%i:%i: warning: configuration for %s is not in use" % (
                    self.config_file, function["file_position"][0] + 1, function["file_position"][1] + 9,
                    function["name"]))
            elif not function["symbol"] in self.reference_list:
                print("%s:%i:%i: warning: configuration for %s is not referenced" % (
                    self.config_file, function["file_position"][0] + 1, function["file_position"][1] + 9,
                    function["name"]))

        input_file.close()

    def write_line(self, line=''):
        self.output_file.write(line)
        self.output_file.write('\n')

    def bitness(self, f):
        self.write_line(".code%i" % (f["bitness"]))

    def section(self, f):
        self.write_line(".text")

    def align(self, f):
        self.write_line(".align %i" % (f["align"]))

    def label(self, f):
        self.write_line('%s: /* %s %s; */' % (f["symbol"], f["type"], f["prototype"]))

    def prologue(self, f):
        prologue_args = 0
        self.write_line('\t\tpush\t%ebp')
        self.write_line('\t\tmov\t%esp,%ebp')
        if f["stack_align"] > 4:
            prologue_args += 1
            if f["debug"] or self.debug_all:
                prologue_args += 1

        if prologue_args > 0:
            self.write_line('\t\tsub\t$0x%x,%%esp' % (4 * prologue_args))
        self.write_line()

    def store_registers(self):
        """
        Store registers that should be preserved by a Watcom function. The System V ABI for i386 says that cdecl
        functions preserve ebx, esi, edi, ebp, esp, so we only need to store the remaining registers.
        """
        self.write_line('\t\tpush\t%ecx')
        self.write_line('\t\tpush\t%edx')

    def align_push(self, f, st_var_index=0):
        if f["stack_align"] <= 4:
            return
        n_args = len(f["arguments_list"]) + st_var_index
        self.write_line()
        self.write_line('\t\tmov\t%%esp,-0x%x(%%ebp)' % (4 * (st_var_index + 1)))
        if n_args > 0:
            self.write_line('\t\tsub\t$0x%x,%%esp' % (4 * n_args))
        self.write_line('\t\tand\t$-0x%x,%%esp' % f["stack_align"])
        if n_args > 0:
            self.write_line('\t\tadd\t$0x%x,%%esp' % (4 * n_args))

    @staticmethod
    def get_argument(f, index):
        assert f["type"] == "watcall"
        try:
            return Codegen.registers_32bit[index]
        except IndexError:
            return "0x%x(%%ebp)" % ((index - len(Codegen.registers_32bit)) * 4 + 8)

    def push_arguments(self, f):
        n_args = len(f["arguments_list"])

        if f["type"] == "watcall":
            if not f["arguments_list"]:
                f["argument_count"] = 0
                return

            self.write_line()
            arg_list = []
            index = 0
            for arg in f["arguments_list"]:
                if arg["is_far"] and index % 2 != 0:
                    index += 1
                arg_list.append(
                    "\t\tpush\t%s /* %s %s */" % (self.get_argument(f, index), arg["type_name"], arg["arg_name"]))
                if arg["is_far"]:
                    index += 1
                index += 1

            f["argument_count"] = index

            for arg in reversed(arg_list):
                self.write_line(arg)

        elif f["type"] == "cdecl":
            f["argument_count"] = 0
            if n_args == 0:
                return

            self.write_line()
            for n in range(n_args):
                self.write_line("\t\tpush\t0x%x(%%ebp)" % ((n_args - n + 1) * 4))
        elif f["type"] == "variadic":
            f["argument_count"] = 0
            assert n_args > 0

            self.write_line()
            self.write_line('\t\tlea\t0x%x(%%ebp),%%eax' % ((n_args + 1) * 4))
            self.write_line('\t\tpush\t%eax')
            for n in range(n_args - 1):
                self.write_line("\t\tpush\t0x%x(%%ebp)" % ((n_args - n) * 4))

    def debug(self, f):
        if not f["debug"] and not self.debug_all:
            return
        self.align_push(f, 1)
        self.push_arguments(f)
        self.write_line('\t\tpush\t$0f')
        self.write_line('\t\tcall\t%s' % self.prefix_name("printf"))
        arg_count = len(f["arguments_list"])
        if arg_count == 0:
            return
        self.write_line('\t\tadd\t$0x%x,%%esp' % ((arg_count + 1) * 4))
        self.align_pop(f, 1)

    def call(self, f):
        self.write_line('\t\tcall\t%s' % self.prefix_name(f["name"]))
        arg_count = len(f["arguments_list"])
        if arg_count == 0:
            return
        self.write_line('\t\tadd\t$0x%x,%%esp' % (arg_count * 4))

    def align_pop(self, f, st_var_index=0):
        if f["stack_align"] <= 4:
            return
        self.write_line()
        self.write_line('\t\tmov\t-0x%x(%%ebp),%%esp' % (4 * (st_var_index + 1)))

    def restore_registers(self):
        self.write_line()
        self.write_line('\t\tpop\t%edx')
        self.write_line('\t\tpop\t%ecx')

    def epilogue(self):
        self.write_line()
        self.write_line('\t\tleave')

    def ret(self, f):
        if f["argument_count"] and f["argument_count"] > 4:
            self.write_line('\t\tret $0x%x' % ((f["argument_count"] - 4) * 4))
        else:
            self.write_line('\t\tret')

    @staticmethod
    def arg_string(args):
        buf = StringIO()
        for n, arg in enumerate(args):
            if n > 0:
                buf.write(', ')
            if arg["type_class"] == "integer":
                buf.write('%i')
            elif arg["type_class"] == "double":
                buf.write('%lf')
            elif arg["type_class"] == "float":
                buf.write('%f')
            elif arg["type_class"] == "hex":
                buf.write('0x%x')
            elif arg["type_class"] == "pointer":
                buf.write('%p')
            elif arg["type_class"] == "string":
                buf.write('\\"%s\\"')
            elif arg["type_class"] == "character":
                buf.write('\'%c\'')
            elif arg["type_class"] == "stdarg":
                buf.write('...')
            elif arg["type_class"] == "varargs":
                buf.write('(va_list) %p')
        return buf.getvalue()

    def generate_format_string(self, f):
        self.write_line('.data')
        self.write_line('\t0:\t.string "%s (%s)\\n"' % (f["name"], self.arg_string(f["arguments_list"])))

    def generate_wrapper(self, f):
        self.write_line()
        self.bitness(f)
        self.section(f)
        self.align(f)
        self.label(f)
        self.prologue(f)
        self.store_registers()
        self.align_push(f)
        self.push_arguments(f)
        self.debug(f)
        self.write_line()
        self.call(f)
        self.align_pop(f)
        self.restore_registers()
        self.epilogue()
        self.ret(f)

        if f["debug"] or self.debug_all:
            self.generate_format_string(f)

    def main(self):
        try:
            opts, args = gnu_getopt(sys.argv[1:], 'hi:o:ud', ('help', 'input=', 'output=', 'underscore', 'debug-all'))

        except GetoptError as message:
            print('Error:', message, file=sys.stderr)
            sys.exit(1)

        for opt, arg in opts:
            if opt in ('-h', '--help'):
                self.print_help()
                sys.exit(0)
            elif opt in ('-i', '--input'):
                self.input_file = arg
            elif opt in ('-o', '--output'):
                self.output_directory = arg
            elif opt in ('-u', '--underscore'):
                self.underscore = True
            elif opt in ('-d', '--debug-all'):
                self.debug_all = True

        if len(args) != 1:
            print('Error: Wrong number of arguments\n', file=sys.stderr)
            self.print_help()
            sys.exit(1)

        self.config_file = args[0]
        self.config = self.minify(self.config_file)
        self.replace_function_list = self.read_config("replace")
        self.expose_function_list = self.read_config("expose")
        self.process_resource_file()
        self.create_resource_header()
        self.create_access_providers()


Codegen().main()
