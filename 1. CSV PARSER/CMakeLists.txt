cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 23)
project(CSV_PARSER)

#include_directories("${PROJECT_SOURCE_DIR}/vendor/C-Turtle")
#add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/eigen")
#find_package(Eigen3 3.3 REQUIRED NO_MODULE)
#add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/matplotlib-cpp")
add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/fmt")
include_directories("${PROJECT_SOURCE_DIR}/vendor/fmt/include")

#git clone https://github.com/Cryoris/matplotlib-cpp
#git clone https://gitlab.com/libeigen/eigen.git
#git clone https://github.com/fmtlib/fmt
#git clone https://github.com/gabime/spdlog

file(GLOB_RECURSE EXE
	#exe
	"${PROJECT_SOURCE_DIR}/source/main.cpp"
	)

file(GLOB_RECURSE CSV
	#CSV
	"${PROJECT_SOURCE_DIR}/source/CSV/*.h"
	"${PROJECT_SOURCE_DIR}/source/CSV/*.cpp"
	)

file(GLOB_RECURSE ALGO
	#Algorithms
	"${PROJECT_SOURCE_DIR}/source/Algorithms/*.h"
	"${PROJECT_SOURCE_DIR}/source/Algorithms/*.cpp"
	)

file(GLOB_RECURSE DTYPES
	#Algorithms
	"${PROJECT_SOURCE_DIR}/source/DataTypes/*.h"
	"${PROJECT_SOURCE_DIR}/source/DataTypes/*.cpp"
	)

file(GLOB_RECURSE CONSOLE
	#Console
	"${PROJECT_SOURCE_DIR}/source/console/*.h"
	"${PROJECT_SOURCE_DIR}/source/console/*.cpp"
	)

add_executable(CSV_PARSER

	${EXE}
	${CSV}
	${ALGO}
	${DTYPES}
	${CONSOLE}

	)

target_link_libraries(CSV_PARSER PRIVATE fmt::fmt)