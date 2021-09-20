/* Copyright (c) 2020 M.A.X. Port Team
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "inifile.hpp"

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "SDL_assert.h"
#include "resource_manager.hpp"

extern "C" {
#include "gnw.h"
}

/// \todo Convert this module to C++
#include "ginit.h"

/// \todo Fix includes and dependencies
extern "C" {
typedef ResourceID GAME_RESOURCE;
typedef void GameResourceMeta;
#include "mvelib32.h"
#include "unitinfo.h"
#include "units.h"
#include "wrappers.h"
}

enum IniKeyValueType_e {
    INI_SECTION = 0x1,
    INI_NUMERIC = 0x2,
    INI_STRING = 0x4,
};

struct IniKey {
    const char *const name;
    const char *const value;
    const IniKeyValueType_e type;
};

extern "C" {
unsigned short ini_setting_victory_type;
unsigned short ini_setting_victory_limit;
}

static const IniKey ini_keys_table[] = {{"DEBUG", NULL, INI_SECTION},
                                        {"debug", "0", INI_NUMERIC},
                                        {"all_visible", "0", INI_NUMERIC},
                                        {"disable_fire", "0", INI_NUMERIC},
                                        {"quick_build", "0", INI_NUMERIC},
                                        {"real_time", "0", INI_NUMERIC},
                                        {"exclude_range", "3", INI_NUMERIC},
                                        {"proximity_range", "14", INI_NUMERIC},
                                        {"log_file_debug", "0", INI_NUMERIC},
                                        {"raw_normal_low", "0", INI_NUMERIC},
                                        {"raw_normal_high", "5", INI_NUMERIC},
                                        {"raw_concentrate_low", "13", INI_NUMERIC},
                                        {"raw_concentrate_high", "16", INI_NUMERIC},
                                        {"raw_concentrate_seperation", "23", INI_NUMERIC},
                                        {"raw_concentrate_diffusion", "6", INI_NUMERIC},
                                        {"fuel_normal_low", "2", INI_NUMERIC},
                                        {"fuel_normal_high", "3", INI_NUMERIC},
                                        {"fuel_concentrate_low", "12", INI_NUMERIC},
                                        {"fuel_concentrate_high", "16", INI_NUMERIC},
                                        {"fuel_concentrate_seperation", "24", INI_NUMERIC},
                                        {"fuel_concentrate_diffusion", "5", INI_NUMERIC},
                                        {"gold_normal_low", "0", INI_NUMERIC},
                                        {"gold_normal_high", "0", INI_NUMERIC},
                                        {"gold_concentrate_low", "10", INI_NUMERIC},
                                        {"gold_concentrate_high", "16", INI_NUMERIC},
                                        {"gold_concentrate_seperation", "32", INI_NUMERIC},
                                        {"gold_concentrate_diffusion", "5", INI_NUMERIC},
                                        {"mixed_resource_seperation", "40", INI_NUMERIC},
                                        {"min_resources", "9", INI_NUMERIC},
                                        {"max_resources", "20", INI_NUMERIC},
                                        {"attack_factor", "16", INI_NUMERIC},
                                        {"shots_factor", "16", INI_NUMERIC},
                                        {"range_factor", "8", INI_NUMERIC},
                                        {"armor_factor", "32", INI_NUMERIC},
                                        {"hits_factor", "32", INI_NUMERIC},
                                        {"speed_factor", "16", INI_NUMERIC},
                                        {"scan_factor", "8", INI_NUMERIC},
                                        {"cost_factor", "8", INI_NUMERIC},
                                        {"steal_percent", "30", INI_NUMERIC},
                                        {"disable_percent", "50", INI_NUMERIC},
                                        {"max_percent", "90", INI_NUMERIC},
                                        {"step_percent", "10", INI_NUMERIC},
                                        {"repair_turns", "10", INI_NUMERIC},
                                        {"alien_seperation", "60", INI_NUMERIC},
                                        {"alien_unit_value", "0", INI_NUMERIC},
                                        {"red_strategy", "random", INI_STRING},
                                        {"green_strategy", "random", INI_STRING},
                                        {"blue_strategy", "random", INI_STRING},
                                        {"gray_strategy", "random", INI_STRING},

                                        {"SETUP", NULL, INI_SECTION},
                                        {"player_name", "Player 1", INI_STRING},
                                        {"player_clan", "0", INI_NUMERIC},
                                        {"intro_movie", "0", INI_NUMERIC},
                                        {"ipx_socket", "0x51E7", INI_NUMERIC},
                                        {"music_level", "100", INI_NUMERIC},
                                        {"fx_sound_level", "100", INI_NUMERIC},
                                        {"voice_level", "100", INI_NUMERIC},
                                        {"disable_music", "0", INI_NUMERIC},
                                        {"disable_fx", "0", INI_NUMERIC},
                                        {"disable_voice", "0", INI_NUMERIC},
                                        {"auto_save", "1", INI_NUMERIC},
                                        {"game_file_number", "1", INI_NUMERIC},
                                        {"game_file_type", "0", INI_NUMERIC},
                                        {"demo_turns", "0", INI_NUMERIC},
                                        {"enhanced_graphics", "1", INI_NUMERIC},
                                        {"last_campaign", "1", INI_NUMERIC},
                                        {"movie_play", "0", INI_NUMERIC},
                                        {"alt_movie_res", "0", INI_NUMERIC},

                                        {"OPTIONS", NULL, INI_SECTION},
                                        {"world", "0", INI_NUMERIC},
                                        {"timer", "180", INI_NUMERIC},
                                        {"endturn", "45", INI_NUMERIC},
                                        {"start_gold", "150", INI_NUMERIC},
                                        {"play_mode", "1", INI_NUMERIC},
                                        {"victory_type", "0", INI_NUMERIC},
                                        {"victory_limit", "50", INI_NUMERIC},
                                        {"opponent", "1", INI_NUMERIC},
                                        {"raw_resource", "1", INI_NUMERIC},
                                        {"fuel_resource", "1", INI_NUMERIC},
                                        {"gold_resource", "1", INI_NUMERIC},
                                        {"alien_derelicts", "0", INI_NUMERIC},

                                        {"PREFERENCES", NULL, INI_SECTION},
                                        {"effects", "1", INI_NUMERIC},
                                        {"click_scroll", "1", INI_NUMERIC},
                                        {"quick_scroll", "16", INI_NUMERIC},
                                        {"fast_movement", "1", INI_NUMERIC},
                                        {"follow_unit", "0", INI_NUMERIC},
                                        {"auto_select", "0", INI_NUMERIC},
                                        {"enemy_halt", "1", INI_NUMERIC},

                                        {"MODEM", NULL, INI_SECTION},
                                        {"modem_port", "3f8 (Com1)", INI_STRING},
                                        {"modem_baud", "9600", INI_NUMERIC},
                                        {"modem_irq", "4", INI_NUMERIC},
                                        {"modem_init", "ATZ", INI_STRING},
                                        {"modem_answer", "ATS0=1", INI_STRING},
                                        {"modem_call", "ATDT", INI_STRING},
                                        {"modem_hangup", "~~~+++~~~ATH0", INI_STRING},
                                        {"modem_phone", "", INI_STRING},

                                        {"TEAMS", NULL, INI_SECTION},
                                        {"red_team_name", "Player 1", INI_STRING},
                                        {"green_team_name", "Player 2", INI_STRING},
                                        {"blue_team_name", "Player 3", INI_STRING},
                                        {"gray_team_name", "Player 4", INI_STRING},
                                        {"red_team_player", "1", INI_NUMERIC},
                                        {"green_team_player", "2", INI_NUMERIC},
                                        {"blue_team_player", "0", INI_NUMERIC},
                                        {"gray_team_player", "0", INI_NUMERIC},
                                        {"red_team_clan", "0", INI_NUMERIC},
                                        {"green_team_clan", "0", INI_NUMERIC},
                                        {"blue_team_clan", "0", INI_NUMERIC},
                                        {"gray_team_clan", "0", INI_NUMERIC},

                                        {"DIGITAL", NULL, INI_SECTION},
                                        {"Device_Name", "None", INI_STRING},
                                        {"Device_IRQ", "5", INI_NUMERIC},
                                        {"Device_DMA", "1", INI_NUMERIC},
                                        {"Device_Port", "0x220", INI_NUMERIC},
                                        {"Device_ID", "-1", INI_NUMERIC},
                                        {"Channels_Reversed", "0", INI_NUMERIC}};

static const int ini_keys_table_size = sizeof(ini_keys_table) / sizeof(struct IniKey);

static const char *const clan_ini_attrib_name_lut[] = {"turns", "hits",  "armor",  "attack", "reload",
                                                       "speed", "range", "rounds", "scan",   "storage",
                                                       "ammo",  "area",  "disable"};

static const int ini_attribs_table_size = sizeof(clan_ini_attrib_name_lut) / sizeof(char *);

static const char *const clan_ini_section_name_lut[] = {"Clan ?", "Clan A", "Clan B", "Clan C", "Clan D",
                                                        "Clan E", "Clan F", "Clan G", "Clan H"};

static const int ini_clans_table_size = sizeof(clan_ini_section_name_lut) / sizeof(char *);

static_assert(ini_keys_table_size == 118, "M.A.X. v1.04 has 118 configuration ini parameters");

static_assert(ini_attribs_table_size == 13, "M.A.X. v1.04 has 13 clan attributes");

static_assert(ini_clans_table_size == 9, "M.A.X. v1.04 has 9 clans");

IniSettings ini_config;
IniClans ini_clans;

IniSettings::IniSettings() {
    ini.buffer = NULL;

    for (int ini_index = 0; ini_index < ini_keys_table_size; ++ini_index) {
        item[ini_index] = 0;
    }
}

IniSettings::~IniSettings() { Destroy(); }

void IniSettings::Destroy() { inifile_save_to_file_and_free_buffer(&ini); }

void IniSettings::Init() {
    int v1;
    int value;
    char s1[50];
    char filename[PATH_MAX];
    FILE *fp;
    int index;

    strcpy(filename, file_path_game_install);
    strcat(filename, "MAX.INI");
    fp = fopen(filename, "rt");

    if (!fp) {
        SDL_Log("\nMAX.INI File not found..  Using Defaults...\n");
        fp = fopen(filename, "wt");

        if (!fp) {
            SDL_Log("\nUnable to Write File..  Disk Full?\n");
            gexit(12);
        }

        for (index = 0; index < ini_keys_table_size; ++index) {
            if (ini_keys_table[index].type & INI_SECTION) {
                if (index) {
                    strcpy(s1, "\n[");
                } else {
                    strcpy(s1, "[");
                }

                strcat(s1, ini_keys_table[index].name);
                strcat(s1, "]");
            } else {
                strcpy(s1, ini_keys_table[index].name);
                strcat(s1, "=");
                strcat(s1, ini_keys_table[index].value);
            }

            strcat(s1, "\n");
            fprintf(fp, s1, value);
        }
    }

    fclose(fp);

    if (!inifile_init_ini_object_from_ini_file(&ini, filename)) {
        gexit(12);
    }

    for (index = 0; index < ini_keys_table_size; index++) {
        if (ini_keys_table[index].type & INI_SECTION) {
            inifile_ini_seek_section(&ini, ini_keys_table[index].name);
        } else if (ini_keys_table[index].type & INI_NUMERIC) {
            if (inifile_ini_get_numeric_value(&ini, ini_keys_table[index].name, &value)) {
                SetNumericValue(static_cast<GAME_INI>(index), value);
            } else {
                if (!strncmp(ini_keys_table[index].value, "0x", 2)) {
                    v1 = inifile_hex_to_dec(ini_keys_table[index].value + 2);
                } else {
                    v1 = strtol(ini_keys_table[index].value, NULL, 10);
                }

                SetNumericValue(static_cast<GAME_INI>(index), v1);
            }
        }
    }
}

void IniSettings::Save() { inifile_save_to_file(&ini); }

const char *IniSettings::SeekToSection(GAME_INI param) {
    int index = param;

    do {
        if (ini_keys_table[index].type & INI_SECTION) {
            break;
        }

        --index;
    } while (index);

    return ini_keys_table[index].name;
}

int IniSettings::SetNumericValue(GAME_INI param, int value) {
    unsigned int old_value;

    if (param >= ini_keys_table_size) {
        return 0;
    }

    old_value = item[param];
    item[param] = value;

    if (inifile_ini_seek_section(&ini, IniSettings::SeekToSection(param)) &&
        inifile_ini_seek_param(&ini, ini_keys_table[param].name)) {
        inifile_ini_set_numeric_value(&ini, value);
    }

    return old_value;
}

int IniSettings::GetNumericValue(GAME_INI param) {
    int value;

    if (param >= ini_keys_table_size) {
        value = 0;
    } else {
        value = item[param];
    }

    return value;
}

int IniSettings::SetStringValue(GAME_INI param, char *value) {
    int result;

    if (inifile_ini_seek_section(&ini, IniSettings::SeekToSection(param)) &&
        inifile_ini_seek_param(&ini, ini_keys_table[param].name)) {
        result = inifile_ini_set_string_value(&ini, value);
    } else {
        result = 0;
    }
    return result;
}

int IniSettings::GetStringValue(GAME_INI param, char *buffer, int buffer_size) {
    int result;

    if (inifile_ini_seek_section(&ini, IniSettings::SeekToSection(param)) &&
        inifile_ini_seek_param(&ini, ini_keys_table[param].name)) {
        result = inifile_ini_get_string(&ini, buffer, buffer_size, 1);
    } else {
        result = 0;
    }

    return result;
}

void IniSettings::SaveSection(void *smartfile_handle, GAME_INI section) {
    char buffer[30];
    int victory_type;
    int backup_victory_limit;
    int index = section;

    backup_victory_limit = ini_get_setting(ini_victory_limit);
    victory_type = ini_get_setting(ini_victory_type);

    ini_set_setting(ini_victory_limit, ini_setting_victory_limit);
    ini_set_setting(ini_victory_type, ini_setting_victory_type);

    while (!(ini_keys_table[++index].type & INI_SECTION) && index < ini_keys_table_size) {
        if (ini_keys_table[index].type & INI_NUMERIC) {
            smartfile_write_int(smartfile_handle, GetNumericValue(static_cast<GAME_INI>(index)));
        } else {
            GetStringValue(static_cast<GAME_INI>(index), buffer, sizeof(buffer));
            smartfile_write(smartfile_handle, buffer, sizeof(buffer));
        }
    }

    ini_set_setting(ini_victory_limit, backup_victory_limit);
    ini_set_setting(ini_victory_type, victory_type);
}

void IniSettings::LoadSection(void *smartfile_handle, GAME_INI section, char mode) {
    char buffer[30];
    int value;
    int victory_type;
    int backup_victory_limit;
    int index = section;

    backup_victory_limit = ini_get_setting(ini_victory_limit);
    victory_type = ini_get_setting(ini_victory_type);

    while (!(ini_keys_table[++index].type & INI_SECTION) && index < ini_keys_table_size) {
        if (ini_keys_table[index].type & INI_NUMERIC) {
            smartfile_read_int(smartfile_handle, &value);
            if (mode) {
                SetNumericValue(static_cast<GAME_INI>(index), value);
            }
        } else {
            smartfile_read(smartfile_handle, buffer, sizeof(buffer));
            if (mode) {
                SetStringValue(static_cast<GAME_INI>(index), buffer);
            }
        }
    }

    if (mode) {
        if (section == ini_OPTIONS) {
            ini_setting_victory_type = ini_get_setting(ini_victory_type);
            ini_setting_victory_limit = ini_get_setting(ini_victory_limit);

            ini_set_setting(ini_victory_limit, backup_victory_limit);
            ini_set_setting(ini_victory_type, victory_type);
        }
    }
}

int ini_get_setting(GAME_INI index) { return ini_config.GetNumericValue(static_cast<GAME_INI>(index)); }

int ini_set_setting(GAME_INI param, int value) { return ini_config.SetNumericValue(param, value); }

IniClans::IniClans() { ini.buffer = NULL; }

IniClans::~IniClans() { inifile_save_to_file_and_free_buffer(&ini); }

void IniClans::Init() { inifile_load_from_resource(&ini, CLANATRB); }

int IniClans::SeekUnit(int clan, int unit) {
    return inifile_ini_seek_section(&ini, clan_ini_section_name_lut[clan]) &&
           inifile_ini_seek_param(&ini, units2[unit].singular_name);
}

int IniClans::GetNextUnitUpgrade(short *attrib_id, short *value) {
    const char *cstr;

    if (!inifile_ini_process_string_value(&ini, buffer, sizeof(buffer))) {
        return 0;
    }

    cstr = buffer;

    if (!strlen(cstr)) {
        return 0;
    }

    *value = strtol(cstr, NULL, 10);

    while (*cstr != ' ') {
        cstr++;
    }

    cstr++;

    for (*attrib_id = 0; *attrib_id != ini_attribs_table_size && stricmp(clan_ini_attrib_name_lut[*attrib_id], cstr);
         (*attrib_id)++) {
        ;
    }

    SDL_assert(*attrib_id < ini_attribs_table_size);

    return 1;
}

void IniClans::GetStringValue(char *buffer, int buffer_size) { inifile_ini_get_string(&ini, buffer, buffer_size, 0); }

int IniClans::GetClanGold(int clan) {
    int result;

    if (inifile_ini_seek_section(&ini, clan_ini_section_name_lut[clan]) && inifile_ini_seek_param(&ini, "Gold") &&
        inifile_ini_process_string_value(&ini, buffer, sizeof(buffer))) {
        result = strtol(buffer, NULL, 10);
    } else {
        result = 0;
    }

    return result;
}

void IniClans::GetClanText(int clan, char *buffer, int buffer_size) {
    if (!inifile_ini_seek_section(&ini, clan_ini_section_name_lut[clan]) || !inifile_ini_seek_param(&ini, "Text") ||
        !inifile_ini_process_string_value(&ini, buffer, buffer_size)) {
        strcpy(buffer, "No clan chosen - computer will choose a clan at random.");
    }
}

void IniClans::GetClanName(int clan, char *buffer, int buffer_size) {
    if (inifile_ini_seek_section(&ini, clan_ini_section_name_lut[clan])) {
        if (inifile_ini_seek_param(&ini, "Name")) {
            inifile_ini_process_string_value(&ini, buffer, buffer_size);
        }
    }
}

IniSoundVolumes::IniSoundVolumes() { ini.buffer = NULL; }

IniSoundVolumes::~IniSoundVolumes() { inifile_save_to_file_and_free_buffer(&ini); }

void IniSoundVolumes::Init() { inifile_load_from_resource(&ini, SOUNDVOL); }

int IniSoundVolumes::GetUnitVolume(ResourceID id) {
    int value;

    if (!this->ini.buffer) {
        return 0x7FFF;
    }

    if (inifile_ini_seek_section(&ini, "Unit Volumes")) {
        if (ResourceManager_GetResourceFileID(id) != -1) {
            if (inifile_ini_get_numeric_value(&ini, ResourceManager_GetResourceID(id), &value)) {
                return 0x7FFF * value / 100u;
            }
        }
    }

    return 0x7FFF;
}
