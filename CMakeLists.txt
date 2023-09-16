cmake_minimum_required(VERSION 3.26.4)

project(
    YATC
    VERSION 1.0
    DESCRIPTION "Yet another tetris clone"
    LANGUAGES CXX
)

# Create an option to switch between a system sdl library and a vendored sdl library
option(MYGAME_VENDORED "Use vendored libraries" OFF)

if (MYGAME_VENDORED)
    add_subdirectory(vendored/sdl EXCLUDE_FROM_ALL)
else ()
    # 1. Look for a SDL2 package, 2. look for the SDL2 component and 3. fail if none can be found
    find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2)
    find_package(SDL2_image REQUIRED CONFIG COMPONENTS SDL2_image)
    find_package(SDL2_mixer REQUIRED CONFIG COMPONENTS SDL2_mixer)
    find_package(SDL2_ttf REQUIRED CONFIG COMPONENTS SDL2_ttf)
    # 1. Look for a SDL2 package, 2. Look for the SDL2main component and 3. DO NOT fail when SDL2main is not available
     find_package(SDL2 CONFIG COMPONENTS SDL2main)
endif ()

file(GLOB_RECURSE yatc_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Create your game executable target
add_executable(yatc WIN32 ${yatc_SOURCES})

# compile features and options
target_compile_features(yatc PRIVATE cxx_std_17)

target_compile_options(yatc PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

    # SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI yatclications
if (TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(yatc PRIVATE SDL2::SDL2main)
endif ()

# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL library.
target_link_libraries(yatc PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf)

