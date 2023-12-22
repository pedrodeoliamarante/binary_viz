cmake_minimum_required(VERSION 3.22)
project(binary_viz C)

set(CMAKE_C_STANDARD 99)

# Add the line below - replace with the actual path provided by vcpkg integrate install
set(CMAKE_TOOLCHAIN_FILE "C:/c_stuff/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(PNG REQUIRED)

add_executable(binary_viz main.c)

# Link your executable with the libpng library.
target_link_libraries(binary_viz PRIVATE PNG::PNG)
