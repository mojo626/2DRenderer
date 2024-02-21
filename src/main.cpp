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
#include "util/RuleTile.hpp"
#include "util/Player.hpp"

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



    Dungeon dungeon = DungeonGen::GenerateDungeon(80, 5, glm::vec2(80, 80), glm::vec2(20, 20), 80, glm::vec2(400, 300), 1.15, 0.1);


    

    Inputs inputs;
    Player player(dungeon.mainRooms[0].middle(), 1.5);

    Camera cam(0.15);
    cam.SetPos(player.pos);


    while(!glfwWindowShouldClose(window))
    {
        //input
        inputs = man.processInput(window);

        player.Move(inputs);

        cam.Move(glm::vec2((player.pos.x - cam.pos.x)/10, (player.pos.y - cam.pos.y)/10));

        //rendering
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 projection = cam.GetProjection(WINDOW_WIDTH, WINDOW_HEIGHT);

        spriteShader.SetMatrix4("projection", projection);
        

        for (int x = 0; x < dungeon.grid.size(); x++)
        {
            for (int y = 0; y < dungeon.grid[0].size(); y++)
            {
                if (dungeon.grid[x][y] == 1)
                {
                    renderer.SetTile(glm::vec2(2, 3), 4);
                    renderer.DrawSprite(glm::vec2(x * 5, y * 5), glm::vec2(5, 5), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
                } else if (dungeon.grid[x][y] == 2) {
                    renderer.SetTile(RuleTile::GetTile(glm::vec2(x, y), &dungeon.grid), 4);
                    renderer.DrawSprite(glm::vec2(x * 5, y * 5), glm::vec2(5, 5), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
                }
            }
        }

        // for (int i = 0; i < dungeon.mainRooms.size(); i++)
        // {
        //     renderer.DrawSprite(dungeon.mainRooms[i].pos, dungeon.mainRooms[i].size, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        // }


        renderer.SetTile(glm::vec2(0, 0), 4);
        renderer.DrawSprite(player.pos, glm::vec2(5, 5), 0.0f, glm::vec3(1.0, 1.0, 1.0));



        //check events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}