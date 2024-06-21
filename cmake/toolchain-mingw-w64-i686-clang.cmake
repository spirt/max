set(CMAKE_SYSTEM_NAME Windows)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PREFIX c:/msys64/mingw32)
set(TOOLSET "i686-w64-mingw32")

set(CMAKE_FIND_ROOT_PATH ${PREFIX}/${TOOLSET})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

find_program(CMAKE_RC_COMPILER NAMES llvm-windres REQUIRED)
find_program(CMAKE_C_COMPILER NAMES clang REQUIRED)
find_program(CMAKE_CXX_COMPILER NAMES clang++ REQUIRED)

set(CONFIGURE_EXTRA_ARGS
	--target=${TOOLSET}
	--host=${TOOLSET}
	--build=${TOOLSET}
	CC=${CMAKE_C_COMPILER}
	CXX=${CMAKE_CXX_COMPILER}
	CFLAGS=-m32
	CXXFLAGS=-m32
	LDFLAGS=-m32
)

add_compile_options(
	-m32
)
