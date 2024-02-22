cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 11)

project(OpenGLRenderer)


add_subdirectory(lib/glfw)
add_subdirectory(lib/enet)

set(IMGUI_INCLUDE lib/imgui/imgui.cpp lib/imgui/imgui_draw.cpp lib/imgui/imgui_tables.cpp lib/imgui/imgui_widgets.cpp  lib/imgui/backends/imgui_impl_opengl3.cpp lib/imgui/backends/imgui_impl_glfw.cpp)

add_executable(game src/main.cpp includes/glad.c src/util/stb_image.cpp src/util/texture.cpp ${IMGUI_INCLUDE})




target_link_libraries(game PUBLIC glfw enet)
target_include_directories(game PRIVATE includes)
target_include_directories(game PRIVATE lib/glm)
target_include_directories(game PRIVATE lib/enet/include)
target_include_directories(game PRIVATE lib/imgui lib/imgui/backends)


