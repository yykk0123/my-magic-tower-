cmake_minimum_required(VERSION 3.10)
project(MAGIC_TOWER)

set(CMAKE_CXX_STANDARD 17)

# Use pkg-config to find SDL2 and SDL2_image
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

# Add source files
add_executable(${PROJECT_NAME} main.cpp map.cpp hero.cpp gui.cpp operation.cpp
                               global.cpp)

# Include directories
include_directories(${SDL2_INCLUDE_DIRS}
                    ${SDL2_IMAGE_INCLUDE_DIRS}${SDL2_TTF_INCLUDE_DIRS})

# # Link directories (usually optional on Linux but safe to add)
# link_directories(${SDL2_LIBRARY_DIRS} ${SDL2_IMAGE_LIBRARY_DIRS})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES}
                      ${SDL2_TTF_LIBRARIES})

# Set output path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
