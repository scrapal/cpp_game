cmake_minimum_required(VERSION 3.5)
project(main)

# Create an option to switch between a system sdl library and a vendored sdl library
option(MAIN_VENDORED "Use vendored libraries" OFF)

if(MAIN_VENDORED)
  add_subdirectory(vendored/sdl EXCLUDE_FROM_ALL)
else()
  # 1. Look for a SDL2 package, 2. look for the SDL2 component and 3. fail if none can be found
  find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
  find_package(SDL2_image REQUIRED CONFIG REQUIRED COMPONENTS SDL2_image)

  # 1. Look for a SDL2 package, 2. Look for the SDL2maincomponent and 3. DO NOT fail when SDL2main is not available
  find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
  find_package(SDL2_image REQUIRED CONFIG COMPONENTS SDL2_image)
endif()

add_definitions(-std=c++11)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

# Create your game executable target as usual
add_executable(main ${SOURCES})

include_directories(src)

# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
if(TARGET SDL2::SDL2main)
  # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
  target_link_libraries(main PRIVATE SDL2::SDL2main)
endif()

# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL libarary.
target_link_libraries(main PRIVATE SDL2::SDL2)
target_link_libraries(main PRIVATE SDL2_image::SDL2_image)