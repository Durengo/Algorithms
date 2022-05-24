cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 11)
project(FIBONACCI)

include_directories("${PROJECT_SOURCE_DIR}/vendor/C-Turtle")

file(GLOB_RECURSE EXE
	#exe
	"${PROJECT_SOURCE_DIR}/source/main.cpp"
	)

add_executable(FIBONACCI
	${EXE}
	)