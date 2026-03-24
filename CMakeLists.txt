cmake_minimum_required(VERSION 3.20)
project(Ignis)

set(CMAKE_CXX_STANDARD 20)

# 1. Tell CMake where to find the SDL3 configuration files
set(SDL3_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern/SDL3/lib/cmake/SDL3")

# 2. Find the SDL3 package
find_package(SDL3 REQUIRED CONFIG)

# 3. Create your executable
add_executable(Ignis src/main.cpp)

# 4. Link SDL3 to your project
target_link_libraries(Ignis PRIVATE SDL3::SDL3)

# 5. Professional touch: Copy the SDL3.dll to your output folder automatically
add_custom_command(TARGET Ignis POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/SDL3/bin/SDL3.dll"
        $<TARGET_FILE_DIR:Ignis>)