#ifndef COLLIDERS_H
#define COLLIDERS_H

#include <glm/glm.hpp>

class RectCollider {
    public:
        glm::vec2 topLeft;
        glm::vec2 bottomRight;

        RectCollider(){}
        RectCollider(glm::vec2 topLeft, glm::vec2 size)
        {
            this->topLeft = topLeft;
            this->bottomRight = topLeft + size;
        }

        void UpdateCollider(glm::vec2 topLeft, glm::vec2 size)
        {
            this->topLeft = topLeft;
            this->bottomRight = topLeft + size;
        }

        bool RectCollide(RectCollider other)
        {
            if (this->topLeft.x < other.bottomRight.x && this->bottomRight.x > other.topLeft.x && this->topLeft.y < other.bottomRight.y && this->bottomRight.y > other.topLeft.y)
            {
                return true;
            }

            return false;
        }
};


#endif