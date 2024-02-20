#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "util/Shaders.hpp"
#include "util/SpriteRenderer.hpp"
#include "util/WindowManager.hpp"
#include "DungeonGen/DungeonGen.hpp"
#include <vector>
#include <ctime>
#include "util/Line.hpp"
#include "util/emst.hpp"

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

int main()
{
    //TODO: instead of doing this, can add seeds
    srand((unsigned int)time(NULL));

    WindowManager man = WindowManager();

    GLFWwindow* window = man.init(WINDOW_WIDTH, WINDOW_HEIGHT);
    


    Shader spriteShader("../res/shaders/sprite.vert", "../res/shaders/sprite.frag");
    spriteShader.use();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WINDOW_WIDTH), 
        static_cast<float>(WINDOW_HEIGHT), 0.0f, -1.0f, 1.0f);

    spriteShader.SetMatrix4("projection", projection);

    SpriteRenderer renderer = SpriteRenderer(spriteShader, NULL);



    Dungeon dungeon = DungeonGen::GenerateDungeon(100, 5, glm::vec2(80, 80), glm::vec2(20, 20), 80, glm::vec2(400, 300), 1.15, 0.1);





    while(!glfwWindowShouldClose(window))
    {
        //input
        man.processInput(window);

        //rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        

        for (int x = 0; x < dungeon.grid.size(); x++)
        {
            for (int y = 0; y < dungeon.grid[0].size(); y++)
            {
                if (dungeon.grid[x][y] == 1)
                {
                    renderer.DrawSprite(glm::vec2(x * 5, y * 5), glm::vec2(5, 5), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
                }
            }
        }

        // for (int i = 0; i < dungeon.mainRooms.size(); i++)
        // {
        //     renderer.DrawSprite(dungeon.mainRooms[i].pos, dungeon.mainRooms[i].size, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        // }






        //check events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}