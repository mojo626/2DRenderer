cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 11)

project(OpenGLRenderer)


add_subdirectory(lib/glfw)
add_subdirectory(lib/enet)

add_executable(game src/main.cpp includes/glad.c src/util/stb_image.cpp src/util/texture.cpp)




target_link_libraries(game PUBLIC glfw enet)
target_include_directories(game PRIVATE includes)
target_include_directories(game PRIVATE lib/glm)
target_include_directories(game PRIVATE lib/enet/include)
# target_include_directories(game PRIVATE lib/imgui lib/imgui/backends)


