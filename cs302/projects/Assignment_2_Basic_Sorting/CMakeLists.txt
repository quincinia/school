cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_STANDARD 11)

project(assignment2)

include_directories(include)

add_executable(assignment2 src/main.cpp)

install(TARGETS assignment2
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/devel/bin
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib
        ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib/static)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION ${PROJECT_SOURCE_DIR}/devel/include
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
