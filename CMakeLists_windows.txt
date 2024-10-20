cmake_minimum_required(VERSION 3.29)
project(TreeVisualizerSFML)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.0)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 20)

add_executable(TreeVisualizerSFML main.cpp
        TreeNode.h
        TreeNode.cpp
        InputBox.h
        InputBox.cpp)

target_link_libraries(TreeVisualizerSFML sfml-graphics)