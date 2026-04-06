cmake_minimum_required(VERSION 3.10)
project(Ignis)

set(CMAKE_CXX_STANDARD 17)

set(SDL3_DIR "C:/My Files/Projects/Ignis/extern/SDL3/lib/cmake/SDL3")

# Find SDL3
find_package(SDL3 REQUIRED)

# Include directories
include_directories(include)

# Define source files
set(SOURCES
        src/main.cpp
        src/Engine.cpp
        src/EntityManager.cpp
)

add_executable(Ignis ${SOURCES})

# Link SDL3
target_link_libraries(Ignis SDL3::SDL3)