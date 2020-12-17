cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_STANDARD 11)

project(proj11)


include_directories(include)

add_executable(proj11_test src/proj11_test.cpp)
add_executable(proj11_assess src/proj11_assess.cpp)

install(TARGETS proj11_test proj11_assess
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/devel/bin
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib
        ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib/static)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION ${PROJECT_SOURCE_DIR}/devel/include
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
