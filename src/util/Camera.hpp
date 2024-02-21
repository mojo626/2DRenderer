#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class Camera {
    public:
        float zoom;
        glm::vec2 pos;
        float speed;
        Camera(float zoom, float speed)
        {
            this->zoom = zoom;
            this->speed = speed;
            pos = glm::vec2(0, 0);
        }

        void SetPos(glm::vec2 newPos)
        {
            this->pos = newPos;
        }

        //input from 0-1
        void Move(glm::vec2 move)
        {
            this->pos += move * speed;
        }

        glm::mat4 GetProjection(int WINDOW_WIDTH, int WINDOW_HEIGHT)
        {
            return glm::ortho(this->pos.x, this->pos.x + zoom * WINDOW_WIDTH, this->pos.y + zoom * WINDOW_HEIGHT, this->pos.y, -1.0f, 1.0f);
        }
};


#endif