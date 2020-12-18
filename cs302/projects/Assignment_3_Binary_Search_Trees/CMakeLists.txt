cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_STANDARD 14)

project(assignment3)

include_directories(include)

add_executable(assignment3 src/main.cpp)
target_link_libraries(assignment3)

install(TARGETS assignment3
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/devel/bin
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib
        ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib/static)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION ${PROJECT_SOURCE_DIR}/devel/include
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
