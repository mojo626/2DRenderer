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
#include "util/Camera.hpp"

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

    SpriteRenderer renderer = SpriteRenderer(spriteShader, "../res/images/tileset.png");



    Dungeon dungeon = DungeonGen::GenerateDungeon(100, 5, glm::vec2(80, 80), glm::vec2(20, 20), 80, glm::vec2(400, 300), 1.15, 0.1);


    Camera cam(0.3, 1);

    Inputs inputs;


    while(!glfwWindowShouldClose(window))
    {
        //input
        inputs = man.processInput(window);

        glm::vec2 camMove = glm::vec2(0, 0);
        if (inputs.UP)
        {
            camMove.y = -1;
        }
        if (inputs.DOWN)
        {
            camMove.y = 1;
        }
        if (inputs.LEFT)
        {
            camMove.x = -1;
        }
        if (inputs.RIGHT)
        {
            camMove.x = 1;
        }

        cam.Move(camMove);

        //rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 projection = cam.GetProjection(WINDOW_WIDTH, WINDOW_HEIGHT);

        spriteShader.SetMatrix4("projection", projection);
        

        for (int x = 0; x < dungeon.grid.size(); x++)
        {
            for (int y = 0; y < dungeon.grid[0].size(); y++)
            {
                if (dungeon.grid[x][y] == 1)
                {
                    renderer.SetTile(glm::vec2(0, 0), 4);
                    renderer.DrawSprite(glm::vec2(x * 5, y * 5), glm::vec2(5, 5), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
                }// else {
                //     renderer.SetTile(glm::vec2(1, 0), 4);
                //     renderer.DrawSprite(glm::vec2(x * 5, y * 5), glm::vec2(5, 5), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
                // }
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