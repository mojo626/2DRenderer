cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 11)

project(OpenGLRenderer)

add_executable(game src/main.cpp lib/glad.c src/util/stb_image.cpp src/util/texture.cpp)

add_subdirectory(lib/glfw)

target_link_libraries(game PUBLIC glfw)
target_include_directories(game PRIVATE includes)
target_include_directories(game PRIVATE lib/glm)
# target_include_directories(game PRIVATE lib/imgui lib/imgui/backends)


