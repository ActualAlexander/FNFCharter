cmake_minimum_required(VERSION 3.15)
project(FNFCharter)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Automatically find Raylib installed via MSYS2
find_package(raylib REQUIRED)

# Automatically gather all source and header files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "Source/*.cpp"
)
file(GLOB_RECURSE HEADERS "Source/Headers/*.hpp")

include(FetchContent)

FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)

FetchContent_MakeAvailable(json)

# Define the executable target
add_executable(Main ${SOURCES} ${HEADERS})

# Tell the compiler where to find your header files
target_include_directories(Main PRIVATE Source/Headers)

# Link Raylib and required Windows system libraries
target_link_libraries(Main PRIVATE raylib nlohmann_json::nlohmann_json opengl32 gdi32 winmm)

# Output the final Main.exe directly into your Source folder
set_target_properties(Main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Source"
)