cmake_minimum_required(VERSION 4.3.3)
project(Day8 VERSION 4.3.3)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

set(SOURCES
	main.cpp
)
set(HEADERS
)

add_subdirectory(src)

add_executable(${PROJECT_NAME}
	${SOURCES}
	${HEADERS}
)

target_link_libraries(
	${PROJECT_NAME}
PUBLIC
	lib
	tbb
)

