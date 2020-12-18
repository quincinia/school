cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_STANDARD 14)

project(assignment4)

include_directories(include)

set(RB_NODE src/RedBlackNode.cpp) #these may not be needed
add_library(rb_node ${RB_NODE})

set(LLRB_TREE src/LLRB_T.cpp) #see above
add_library(llrb_tree ${LLRB_TREE})

add_executable(assignment4 src/main.cpp)
target_link_libraries(assignment4 rb_node llrb_tree)

install(TARGETS assignment4 rb_node llrb_tree
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/devel/bin
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib
        ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/devel/lib/static)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION ${PROJECT_SOURCE_DIR}/devel/include
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
