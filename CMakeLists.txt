cmake_minimum_required(VERSION 3.20)
project(Minefall LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)



add_executable(Minefall
    src/main.cpp
	src/Minefall.cpp
)

target_link_libraries(Minefall PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

