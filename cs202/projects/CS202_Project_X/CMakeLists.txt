cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_STANDARD 11)

project(projX)

include_directories(include)

set(DATATYPE_SOURCES src/DataType/DataType.cpp)
add_library(DataType ${DATATYPE_SOURCES})

set(SMARTPTR_SOURCES src/SmartPtr/SmartPtr.cpp)
add_library(SmartPtr ${SMARTPTR_SOURCES})

add_executable(projX src/projX.cpp)
target_link_libraries(projX DataType SmartPtr)

install(TARGETS projX DataType SmartPtr
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/devel/bin
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib
        ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib/static)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION ${PROJECT_SOURCE_DIR}/devel/include
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
