cmake_minimum_required(VERSION 3.31)
project(linked-lists)

set(CMAKE_CXX_STANDARD 23)

find_package(7zip CONFIG REQUIRED)
target_link_libraries(main PRIVATE 7zip::7zip)

add_executable(linked-lists main.cpp)