#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "util/Shaders.hpp"
#include "util/SpriteRenderer.hpp"
#include "util/WindowManager.hpp"

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

int main()
{
    WindowManager man = WindowManager();

    GLFWwindow* window = man.init(WINDOW_WIDTH, WINDOW_HEIGHT);
    


    Shader spriteShader("../res/shaders/sprite.vert", "../res/shaders/sprite.frag");
    spriteShader.use();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WINDOW_WIDTH), 
        static_cast<float>(WINDOW_HEIGHT), 0.0f, -1.0f, 1.0f);

    spriteShader.SetMatrix4("projection", projection);

    SpriteRenderer renderer = SpriteRenderer(spriteShader, NULL);
    


    while(!glfwWindowShouldClose(window))
    {
        //input
        man.processInput(window);

        //rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.DrawSprite(glm::vec2(0.0f, 0.0f), glm::vec2(200.0f, 200.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));


        //check events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}