cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 23)
project(SQL)

include_directories(${PROJECT_SOURCE_DIR}/vendor/sqlite)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/fmt/)
include_directories(${PROJECT_SOURCE_DIR}/vendor/fmt/include)

file(GLOB_RECURSE EXE
	#exe
	"${PROJECT_SOURCE_DIR}/source/main.cpp"
	)

file(GLOB_RECURSE sqlite
	#sqlite cpp c
	"${PROJECT_SOURCE_DIR}/vendor/sqlite/sqlite3.c"
	"${PROJECT_SOURCE_DIR}/vendor/sqlite/sqlite3.h"
	)

file(GLOB_RECURSE CONSOLE
	"${PROJECT_SOURCE_DIR}/source/console.h"
	"${PROJECT_SOURCE_DIR}/source/console.cpp"
	)

file(GLOB_RECURSE DB
	"${PROJECT_SOURCE_DIR}/source/database.h"
	"${PROJECT_SOURCE_DIR}/source/database.cpp"
	)

file(GLOB_RECURSE PATIENT
	"${PROJECT_SOURCE_DIR}/source/patient.h"
	"${PROJECT_SOURCE_DIR}/source/patient.cpp"
	)

add_executable(SQL
	${EXE}
	${sqlite}
	${CONSOLE}
	${DB}
	${PATIENT}
	)

target_link_libraries(SQL PRIVATE fmt::fmt)