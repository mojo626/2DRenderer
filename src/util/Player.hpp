#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <vector>
#include "WindowManager.hpp"
#include "AnimationManager.hpp"
#include "Colliders.hpp"
#include "../DungeonGen/DungeonGen.hpp"

class Player {
    public:
        glm::vec2 pos;
        float speed;
        bool facingLeft = false;
        bool moving = false;
        AnimationManager idleAnim;
        AnimationManager walkAnim;
        RectCollider coll;
        Player(glm::vec2 pos, float speed)
        {
            this->pos = pos;
            this->speed = speed;
            std::vector<glm::vec2> frames = {glm::vec2(4,0), glm::vec2(5,0), glm::vec2(6,0), glm::vec2(5,0)};
            this->idleAnim = AnimationManager(frames, 0.3f);
            std::vector<glm::vec2> frames2 = {glm::vec2(7,0), glm::vec2(4,1), glm::vec2(5,1), glm::vec2(4,1), glm::vec2(7,0), glm::vec2(6,1), glm::vec2(7,1), glm::vec2(6,1)};
            this->walkAnim = AnimationManager(frames2, 0.08f);
            
            this->coll = RectCollider(this->pos, glm::vec2(5, 5));
        }

        //input from 0-1
        void Move(Inputs inputs, float deltaTime, Dungeon dungeon)
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

            glm::vec2 xMove = glm::vec2(camMove.x, 0.0);
            glm::vec2 yMove = glm::vec2(0.0, camMove.y);


            //check x
            bool colliding = false;
            this->UpdateCollider(this->pos + xMove * speed * deltaTime);
            for (int x = 0; x < dungeon.grid.size(); x++)
            {
                for (int y = 0; y < dungeon.grid[0].size(); y++)
                {
                    if (dungeon.grid[x][y] == 2) {
                        RectCollider wallColl(glm::vec2(x * dungeon.gridSize, y * dungeon.gridSize), glm::vec2(dungeon.gridSize, dungeon.gridSize));

                        if (this->coll.RectCollide(wallColl))
                        {
                            colliding = true;
                        }
                    }
                }
            }

            if (!colliding)
            {
                this->pos += xMove * speed * deltaTime;   
            }

            //check y
            colliding = false;
            this->UpdateCollider(this->pos + yMove * speed * deltaTime);
            for (int x = 0; x < dungeon.grid.size(); x++)
            {
                for (int y = 0; y < dungeon.grid[0].size(); y++)
                {
                    if (dungeon.grid[x][y] == 2) {
                        RectCollider wallColl(glm::vec2(x * dungeon.gridSize, y * dungeon.gridSize), glm::vec2(dungeon.gridSize, dungeon.gridSize));

                        if (this->coll.RectCollide(wallColl))
                        {
                            colliding = true;
                        }
                    }
                }
            }

            if (!colliding)
            {
                this->pos += yMove * speed * deltaTime;   
            }
            


            moving = glm::length(camMove) > 0;
            this->UpdateCollider(this->pos);
        }

        void UpdateCollider(glm::vec2 pos)
        {
            this->coll.UpdateCollider(pos + glm::vec2(0, 2.5), glm::vec2(5, 2.5));
        }

        void Render(float deltaTime, int tilesetWidth, SpriteRenderer renderer)
        {
            glm::vec2 frame;
            if (moving)
            {
                frame = walkAnim.GetFrame(deltaTime);
            } else {
                frame = idleAnim.GetFrame(deltaTime);
            }
            
            renderer.SetTile(frame, tilesetWidth);
            if (this->facingLeft)
            {
                renderer.DrawSprite(glm::vec2(this->pos.x + 5, this->pos.y), glm::vec2(-5, 5), 0.0f, glm::vec3(1.0, 1.0, 1.0));
            } else {
                renderer.DrawSprite(this->pos, glm::vec2(5, 5), 0.0f, glm::vec3(1.0, 1.0, 1.0));
            }
        }

        void CheckWallCollisions(Dungeon dungeon)
        {
            // this->coll.UpdateCollider(this->pos, glm::vec2(5,5));

            // for (int x = 0; x < dungeon.grid.size(); x++)
            // {
            //     for (int y = 0; y < dungeon.grid[0].size(); y++)
            //     {
            //         if (dungeon.grid[x][y] == 2) {
            //             RectCollider wallColl(glm::vec2(x * dungeon.gridSize, y * dungeon.gridSize), glm::vec2(dungeon.gridSize, dungeon.gridSize));

            //             if (this->coll.RectCollide(wallColl))
            //             {
            //                 glm::vec2 centerWall = glm::vec2(x*dungeon.gridSize + dungeon.gridSize/2.0, y*dungeon.gridSize + dungeon.gridSize/2.0);
            //                 glm::vec2 centerPlayer = glm::vec2(this->pos.x + dungeon.gridSize/2.0, this->pos.y + dungeon.gridSize/2.0);

            //                 glm::vec2 vec = centerWall - centerPlayer;
            //                 if (vec.x > vec.y)
            //                 {
            //                     this->pos.x = (vec.x > 0 ? -dungeon.gridSize : dungeon.gridSize) + (x*dungeon.gridSize);
            //                 } else {
            //                     this->pos.y = (vec.y > 0 ? -dungeon.gridSize : dungeon.gridSize) + (y*dungeon.gridSize);
            //                 }
            //             }
            //         }
            //     }
            // }
        }
};


#endif