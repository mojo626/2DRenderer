#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <vector>
#include "WindowManager.hpp"

class Player {
    public:
        glm::vec2 pos;
        float speed;
        Player(glm::vec2 pos, float speed)
        {
            this->pos = pos;
            this->speed = speed;
        }

        //input from 0-1
        void Move(Inputs inputs)
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
            }
            if (inputs.RIGHT)
            {
                camMove.x = 1;
            }

            this->pos += camMove * speed;
        }
};


#endif