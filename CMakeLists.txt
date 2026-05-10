cmake_minimum_required(VERSION 3.14)

project(Chess)

# 1. Add your source and include directories
include_directories(include)
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE SOURCES "include/src/*.cpp")


# 2. Create Executable
add_executable(Chess ${SOURCES})

# 3. Discover and link SFML modules (including Audio for sounds)
find_package(SFML 3 CONFIG REQUIRED COMPONENTS Graphics Window System Audio)
target_link_libraries(Chess PRIVATE SFML::Graphics SFML::Window SFML::System SFML::Audio)

# Set C++ Standard
target_compile_features(Chess PRIVATE cxx_std_17)

# 4. Copy assets directory to the build directory so the executable can find them at runtime
add_custom_command(TARGET Chess POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets
)