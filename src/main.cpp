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
#include <enet/enet.h>
#include "util/NetworkManager.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    //TODO: instead of doing this, can add seeds
    //srand((unsigned int)time(NULL));
    srand(111);

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

    bool isServer = true;
    

    bool done = false;
    while (!done)
    {
        //rendering
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Another Window");   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked
        if (ImGui::Button("Server", ImVec2(80,20)))
        {
            isServer = true;
        }
        if (ImGui::Button("Client", ImVec2(80,20)))
        {
            isServer = false;
        }
        done = ImGui::Button("Begin", ImVec2(80, 20));
        ImGui::End();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //check events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    NetworkManager networkMan(isServer);

    while(!glfwWindowShouldClose(window))
    {
        // update delta deltaTime
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        networkMan.Update();

        //input
        inputs = man.processInput(window);

        player.Move(inputs);

        networkMan.SendPos(player.pos);

        cam.Move(glm::vec2((player.pos.x - cam.pos.x)/10, (player.pos.y - cam.pos.y)/10));

        //rendering
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Another Window");   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked
        ImGui::Text("%.3fms  %.1ffps", deltaTime*1000, 1/deltaTime);
        ImGui::Text(isServer ? "Server" : "Client");
        ImGui::End();

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


        renderer.SetTile(glm::vec2(0, 0), 4);
        renderer.DrawSprite(player.pos, glm::vec2(5, 5), 0.0f, glm::vec3(1.0, 1.0, 1.0));

        for (auto const& x : networkMan.GetPlayers())
        {
            renderer.DrawSprite(x.second->getPos(), glm::vec2(5, 5), 0.0f, glm::vec3(1.0, 1.0, 1.0));
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //check events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    networkMan.Disconnect();
    return 0;
}