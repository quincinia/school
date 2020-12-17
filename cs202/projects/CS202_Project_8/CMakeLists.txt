cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_STANDARD 11)

project(proj8)

include_directories(include)

set(ARRAYLIST_SOURCES src/ArrayList/ArrayList.cpp)
add_library(ArrayList ${ARRAYLIST_SOURCES})

set(DATATYPE_SOURCES src/DataType/DataType.cpp)
add_library(DataType ${DATATYPE_SOURCES})

set(NODELIST_SOURCES src/NodeList/NodeList.cpp)
add_library(NodeList ${NODELIST_SOURCES})

add_executable(proj8 src/proj8.cpp)
target_link_libraries(proj8 ArrayList DataType NodeList)

install(TARGETS proj8 ArrayList DataType NodeList
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/devel/bin
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib
        ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib/static)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION ${PROJECT_SOURCE_DIR}/devel/include
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
