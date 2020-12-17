cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_STANDARD 11)

project(assignment1)

include_directories(include)

set(STACKARRAY_SOURCES src/StackArray.cpp)
add_library(StackArray ${STACKARRAY_SOURCES})

set(STACKLINKED_SOURCES src/StackLinked.cpp)
add_library(StackLinked ${STACKLINKED_SOURCES})

add_executable(delimiters src/delimiters.cpp)
target_link_libraries(delimiters StackArray StackLinked)

add_executable(test6 src/test6.cpp)
target_link_libraries(test6 StackArray StackLinked)

add_executable(postfix src/postfix.cpp)
target_link_libraries(postfix StackArray StackLinked)

#remember to add postfix here too
install(TARGETS delimiters test6 postfix StackArray StackLinked
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/devel/bin
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib
        ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib/static)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION ${PROJECT_SOURCE_DIR}/devel/include
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
