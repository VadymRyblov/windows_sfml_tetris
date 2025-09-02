cmake_minimum_required(VERSION 3.15)
project(Tetris VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set path to SFML library
set(SFML_DIR "D:/libraries/sfml/SFML-2.5.1-windows-vc15-64-bit/SFML-2.5.1/lib/cmake/SFML")

# Find the SFML package with required components
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Create the executable from source files
add_executable(Tetris main.cpp Map.cpp)

# Link the SFML libraries to the executable
target_link_libraries(Tetris PRIVATE sfml-graphics sfml-window sfml-system)
