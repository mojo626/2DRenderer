#ifndef RUlE_TILE_H
#define RUlE_TILE_H

#include <glm/glm.hpp>
#include <vector>


//TODO: should make this more generic
class RuleTile {
    public:
        static glm::vec2 GetTile(glm::vec2 pos, std::vector<std::vector<int>> *grid)
        {
            glm::vec2 tile = glm::vec2(1, 0);


            if ((*grid)[pos.x - 1][pos.y - 1] == 1)
            {
                tile = glm::vec2(1, 3);
            }
            if ((*grid)[pos.x + 1][pos.y - 1] == 1)
            {
                tile = glm::vec2(0, 3);
            }
            if ((*grid)[pos.x - 1][pos.y + 1] == 1)
            {
                tile = glm::vec2(1, 1);
            }
            if ((*grid)[pos.x + 1][pos.y + 1] == 1)
            {
                tile = glm::vec2(0, 1);
            }
            if ((*grid)[pos.x + 1][pos.y] == 1)
            {
                tile = glm::vec2(0, 1);
            }
            if ((*grid)[pos.x - 1][pos.y] == 1)
            {
                tile = glm::vec2(1, 1);
            }
            if ((*grid)[pos.x][pos.y + 1] == 1)
            {
                tile = glm::vec2(2, 1);
            }
            if ((*grid)[pos.x + 1][pos.y] == 1)
            {
                tile = glm::vec2(0, 1);
            }
            if ((*grid)[pos.x - 1][pos.y] == 1)
            {
                tile = glm::vec2(1, 1);
            }
            if ((*grid)[pos.x][pos.y - 1] == 1)
            {
                tile = glm::vec2(0, 2);
            }
            if ((*grid)[pos.x][pos.y - 1] == 1 && (*grid)[pos.x - 1][pos.y] == 1 )
            {
                tile = glm::vec2(1, 2);
            } 
            if ((*grid)[pos.x][pos.y - 1] == 1 && (*grid)[pos.x + 1][pos.y] == 1 )
            {
                tile = glm::vec2(2, 2);
            } 
            if ((*grid)[pos.x][pos.y + 1] == 1 && (*grid)[pos.x + 1][pos.y] == 1 )
            {
                tile = glm::vec2(3, 1);
            } 
            if ((*grid)[pos.x][pos.y + 1] == 1 && (*grid)[pos.x - 1][pos.y] == 1 )
            {
                tile = glm::vec2(3, 2);
            } 
            


            return tile;
        }
};



#endif