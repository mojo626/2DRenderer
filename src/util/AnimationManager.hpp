#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include <glm/glm.hpp>
#include <vector>


class AnimationManager {
    public:
        std::vector<glm::vec2> frames;
        float frameTime;
        float time = 0.0f;
        int frameCounter = 0;

        AnimationManager(){}
        AnimationManager(std::vector<glm::vec2> frames, float frameTime)
        {
            this->frameTime = frameTime;
            this->frames = frames;
        }

        glm::vec2 GetFrame(float deltaTime)
        {
            time += deltaTime;

            if (time >= frameTime)
            {
                time = 0;
                frameCounter ++;

                if (frameCounter >= frames.size())
                {
                    frameCounter = 0;
                }
            }

            return frames[frameCounter];
        }
};


#endif