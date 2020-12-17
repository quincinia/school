cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_STANDARD 11)

project(proj9)

include_directories(include)


set(DATATYPE_SOURCES src/DataType/DataType.cpp)
add_library(DataType ${DATATYPE_SOURCES})

set(ARRAYQUEUE_SOURCES src/ArrayQueue/ArrayQueue.cpp)
add_library(ArrayQueue ${ARRAYQUEUE_SOURCES})

set(NODEQUEUE_SOURCES src/NodeQueue/NodeQueue.cpp)
add_library(NodeQueue ${NODEQUEUE_SOURCES})

add_executable(proj9 src/proj9.cpp)
target_link_libraries(proj9 DataType ArrayQueue NodeQueue)

install(TARGETS proj9 DataType ArrayQueue NodeQueue
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/devel/bin
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib
        ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib/static)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION ${PROJECT_SOURCE_DIR}/devel/include
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
