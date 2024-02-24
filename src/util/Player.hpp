#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <vector>
#include "WindowManager.hpp"
#include "AnimationManager.hpp"

class Player {
    public:
        glm::vec2 pos;
        float speed;
        bool facingLeft = false;
        AnimationManager idleAnim;
        Player(glm::vec2 pos, float speed)
        {
            this->pos = pos;
            this->speed = speed;
            std::vector<glm::vec2> frames = {glm::vec2(4,0), glm::vec2(5,0), glm::vec2(6,0), glm::vec2(5,0)};
            this->idleAnim = AnimationManager(frames, 0.3f);
        }

        //input from 0-1
        void Move(Inputs inputs, float deltaTime)
        {
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
                facingLeft = true;
            }
            if (inputs.RIGHT)
            {
                camMove.x = 1;
                facingLeft = false;
            }

            this->pos += camMove * speed * deltaTime;
        }

        void Render(float deltaTime, int tilesetWidth, SpriteRenderer renderer)
        {
            glm::vec2 frame = idleAnim.GetFrame(deltaTime);
            renderer.SetTile(frame, tilesetWidth);
            if (this->facingLeft)
            {
                renderer.DrawSprite(glm::vec2(this->pos.x + 5, this->pos.y), glm::vec2(-5, 5), 0.0f, glm::vec3(1.0, 1.0, 1.0));
            } else {
                renderer.DrawSprite(this->pos, glm::vec2(5, 5), 0.0f, glm::vec3(1.0, 1.0, 1.0));
            }
        }
};


#endif