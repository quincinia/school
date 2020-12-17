cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_STANDARD 11)

project(ArtGalleryEC)

include_directories(include)

set(VERTEX src/vertex.cpp)
add_library(Vertex ${VERTEX})

set(EDGE src/edge.cpp)
add_library(Edge ${EDGE})

set(GENERAL src/General.cpp)
add_library(General ${GENERAL})

set(MESH src/mesh.cpp)
add_library(Mesh ${MESH})

set(DCEL src/dcel.cpp)
add_library(dcel ${DCEL})

add_executable(solver src/main.cpp)
target_link_libraries(solver Vertex Edge General Mesh dcel)


install(TARGETS solver Vertex Edge General Mesh dcel
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/devel/bin
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib
        ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib/static)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION ${PROJECT_SOURCE_DIR}/devel/include
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
