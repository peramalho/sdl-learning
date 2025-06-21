cmake_minimum_required(VERSION 3.16)
project(app)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# Create your game executable target as usual
add_executable(default-hello-world src/default-hello-world/main.c)
add_executable(hello-world src/hello-world/main.cpp src/hello-world/GameManager.cpp)
add_executable(clear src/clear/main.cpp src/clear/GameManager.cpp)
add_executable(points src/points/main.cpp src/points/GameManager.cpp)

# Link to the actual SDL3 library.
target_link_libraries(default-hello-world PRIVATE SDL3::SDL3)
target_link_libraries(hello-world PRIVATE SDL3::SDL3)
target_link_libraries(clear PRIVATE SDL3::SDL3)
target_link_libraries(points PRIVATE SDL3::SDL3)