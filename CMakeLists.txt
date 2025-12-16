cmake_minimum_required(VERSION 3.31)
project(InventoryFinal CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Dependencies
include(FetchContent)

set(RAYLIB_VERSION 5.5)
FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

add_executable(${PROJECT_NAME} src/main.cpp
        src/inventory.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE include)
# Link to project
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

