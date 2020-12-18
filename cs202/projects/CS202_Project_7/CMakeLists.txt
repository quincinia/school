cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
project(proj7)

include_directories(include)

set(MYSTRING_SOURCES src/MyString/MyString.cpp)
add_library(MyString ${MYSTRING_SOURCES})

add_executable(proj7 src/proj7.cpp)
target_link_libraries(proj7 MyString)

install(TARGETS proj7 MyString
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/devel/bin
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib
        ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib/static)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION ${PROJECT_SOURCE_DIR}/devel/include
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
