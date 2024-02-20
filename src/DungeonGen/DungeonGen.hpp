#ifndef DUNGEON_GEN_H
#define DUNGEON_GEN_H

#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include "../util/delaunator.hpp"
#include "../util/Line.hpp"
#include "../util/emst.hpp"

class Room {
    public:
        glm::vec2 size;
        glm::vec2 pos;

        bool isColliding(Room other) {
            if ((this->pos.x < other.pos.x + other.size.x) && (this->pos.x + this->size.x > other.pos.x) && (this->pos.y < other.pos.y + other.size.y) && (this->pos.y + this->size.y > other.pos.y)) {
                return true;
            }

            return false;
        }

        glm::vec2 middle() {
            return glm::vec2(this->pos.x + this->size.x/2, this->pos.y + this->size.y/2);
        }
};

class Dungeon {
    public:
        std::vector<Room> mainRooms;
        std::vector<Room> hallwayRooms;
        std::vector<std::vector<int>> grid;
        int gridSize;
};

class DungeonGen {
    public:
        static Dungeon GenerateDungeon(int numRooms, int gridSize, glm::vec2 maxSize, glm::vec2 minSize, int maxDistFromOrigin, glm::vec2 centerPoint, float mainRoomThresh, float percentMoreEdges) {

            //generate random rooms
            std::cout << "Generating Random Rooms..." << std::endl;
            std::vector<Room> rooms = DungeonGen::GenerateRandomRooms(numRooms, maxSize, minSize, maxDistFromOrigin, centerPoint, gridSize);

            //seperate rooms with seperation steering behaviour
            std::cout << "Seperating Rooms..." << std::endl;
            rooms = DungeonGen::SeperateRooms(rooms, numRooms, gridSize);

            //pick the main rooms based on a threshold above average room size
            std::cout << "Picking Main Rooms..." << std::endl;
            std::vector<Room> mainRooms = DungeonGen::PickMainRooms(rooms, numRooms, mainRoomThresh);

            //use delaunay triangulation to get connections between rooms
            std::cout << "Triangulating Rooms..." << std::endl;
            std::vector<glm::vec4> lines = DungeonGen::Delaunay(mainRooms);


            std::cout << "Getting Shortest Path..." << std::endl;

            //generate the minimum spanning tree for all rooms to get main path
            std::vector<Point<2>> points(mainRooms.size()); // your data
            // read data ...
            // you can acces any Point<> dimension by index
            // e.g. cin >> points[i][0] >> points[i][1] >> points[i][2]; 

            for (int i = 0; i < mainRooms.size(); i++)
            {
                points[i][0] = mainRooms[i].middle().x;
                points[i][1] = mainRooms[i].middle().y;
            }
            
            KdTreeSolver<2> solver(points);
            
            double total_length = solver.get_total_length();
            
            std::vector<Edge> edges = solver.get_solution(); 

            //add in some random edges for some loops in the dungeon
            std::cout << "Adding In Loops..." << std::endl;
            std::vector<Edge> newEdges = DungeonGen::RandomEdges(lines.size(), mainRooms.size(), percentMoreEdges, edges);

            //add the newEdges to the edges
            edges.insert(edges.end(), newEdges.begin(), newEdges.end());

            //make the edges into straght and L shaped connections
            std::cout << "Making Paths Straight..." << std::endl;
            std::vector<glm::vec4> newConnections = DungeonGen::GenerateStraightConnections(mainRooms, edges);

            //get the rooms that are intersecting with the hallways
            std::cout << "Adding Rooms To Hallways..." << std::endl;
            std::vector<Room> hallwayRooms = DungeonGen::GetHallwayRooms(rooms, mainRooms, newConnections);

            //put all data together into custom object
            std::cout << "Putting Dungeon Together..." << std::endl;
            Dungeon dungeon = makeDungeon(mainRooms, hallwayRooms, newConnections, gridSize);

            return dungeon;
        }
    
        //make private
        static std::vector<Room> GenerateRandomRooms(int numRooms, glm::vec2 maxRoomSize, glm::vec2 minRoomSize, int maxDistFromOrigin, glm::vec2 center, int tileSize) {
            std::vector<Room> rooms;

            for (int i = 0; i < numRooms; i++)
            {
                Room room;
                //getting a random size and rounding it to the grid
                room.size = glm::vec2(round(randRange(minRoomSize.x, maxRoomSize.x)/tileSize)*tileSize, round(randRange(minRoomSize.y, maxRoomSize.y)/tileSize)*tileSize);

                //calculating a random point within a circle
                float r = maxDistFromOrigin * sqrt((float)rand()/RAND_MAX);
                float theta = ((float)rand()/RAND_MAX) * 2 * 3.141592;
                

                float x = center.x + r * cos(theta);
                float y = center.y + r * sin(theta);

                room.pos = glm::vec2(round(x/tileSize)*tileSize, round(y/tileSize)*tileSize);

                rooms.push_back(room);
            }


            return rooms;
        }

        static std::vector<Room> SeperateRooms(std::vector<Room> rooms, int numRooms, int tileSize)
        {
            bool cont = true;
            std::vector<Room> newRooms = rooms;

            //loop while there are still at least two rooms colliding
            while (cont)
            {
                if (!AnyRoomOverlapped(newRooms, numRooms))
                {
                    cont = false;
                    break;
                }

                for (int current = 0; current < numRooms; current++)
                {
                    for (int other = 0; other < numRooms; other++)
                    {
                        if (current == other || !newRooms[current].isColliding(newRooms[other]))
                        {
                            continue;
                        }

                        glm::vec2 dir = glm::normalize(newRooms[other].middle() - newRooms[current].middle());

                        //move the rooms away from each other
                        newRooms[current].pos.x -= round(dir.x)*tileSize;
                        newRooms[current].pos.y -= round(dir.y)*tileSize;
                        newRooms[other].pos.x += round(dir.x)*tileSize;
                        newRooms[other].pos.y += round(dir.y)*tileSize;
                    }   
                }
            }

            return newRooms;
        }

        //pick the rooms that are a certian amount above the average room size
        static std::vector<Room> PickMainRooms(std::vector<Room> rooms, int numRooms, float threshold)
        {
            glm::vec2 averageSize = AverageRoomSize(rooms, numRooms);

            std::vector<Room> mainRooms;
            for (int i = 0; i < numRooms; i++)
            {    
                if ((rooms[i].size.x >= averageSize.x * threshold) && (rooms[i].size.y >= averageSize.y * threshold))
                {
                    mainRooms.push_back(rooms[i]);
                }
            }

            std::cout << mainRooms.size() << std::endl;

            return mainRooms;
        }

        static std::vector<glm::vec4> Delaunay(std::vector<Room> mainRooms)
        {
            std::vector<double> coords;

            std::vector<glm::vec4> lines;

            for (int i = 0; i < mainRooms.size(); i++)
            {
                coords.push_back(mainRooms[i].middle().x);
                coords.push_back(mainRooms[i].middle().y);
            }

            delaunator::Delaunator d(coords);

            for(std::size_t i = 0; i < d.triangles.size(); i+=3) {
                printf(
                    "Triangle points: [[%f, %f], [%f, %f], [%f, %f]]\n",
                    d.coords[2 * d.triangles[i]],        //tx0
                    d.coords[2 * d.triangles[i] + 1],    //ty0
                    d.coords[2 * d.triangles[i + 1]],    //tx1
                    d.coords[2 * d.triangles[i + 1] + 1],//ty1
                    d.coords[2 * d.triangles[i + 2]],    //tx2
                    d.coords[2 * d.triangles[i + 2] + 1] //ty2
                );

                lines.push_back(glm::vec4(d.coords[2 * d.triangles[i]], d.coords[2 * d.triangles[i] + 1], d.coords[2 * d.triangles[i + 1]], d.coords[2 * d.triangles[i + 1] + 1]));

                lines.push_back(glm::vec4(d.coords[2 * d.triangles[i + 1]], d.coords[2 * d.triangles[i + 1] + 1], d.coords[2 * d.triangles[i + 2]], d.coords[2 * d.triangles[i + 2] + 1]));


                lines.push_back(glm::vec4(d.coords[2 * d.triangles[i + 2]], d.coords[2 * d.triangles[i + 2] + 1], d.coords[2 * d.triangles[i]], d.coords[2 * d.triangles[i] + 1]));
            }


            return lines;
        }

        //returns lines in form glm::vec4(x1, y1, x2, y2)
        static std::vector<glm::vec4> GenerateStraightConnections(std::vector<Room> rooms, std::vector<Edge> connections)
        {
            std::vector<glm::vec4> newConnections;
            std::vector<glm::vec2> pos;

            for (int i = 0; i < rooms.size(); i++)
            {
                pos.push_back(rooms[i].middle());
            }

            for (int i = 0; i < connections.size(); i++)
            {
                glm::vec2 pointA = pos[connections[i].first];
                glm::vec2 pointB = pos[connections[i].second];

                glm::vec2 middlePoint = glm::vec2((pointA.x + pointB.x)/2, (pointA.y + pointB.y)/2);

                //check if we can draw any vertical lines between rooms
                if (middlePoint.x >= rooms[connections[i].first].pos.x && middlePoint.x <= rooms[connections[i].first].pos.x + rooms[connections[i].first].size.x && middlePoint.x >= rooms[connections[i].second].pos.x && middlePoint.x <= rooms[connections[i].second].pos.x + rooms[connections[i].second].size.x)
                {
                    newConnections.push_back(glm::vec4(middlePoint.x, pointA.y, middlePoint.x, pointB.y));
                } else if (middlePoint.y >= rooms[connections[i].first].pos.y && middlePoint.y <= rooms[connections[i].first].pos.y + rooms[connections[i].first].size.y && middlePoint.y >= rooms[connections[i].second].pos.y && middlePoint.y <= rooms[connections[i].second].pos.y + rooms[connections[i].second].size.y)
                {

                    newConnections.push_back(glm::vec4(pointA.x, middlePoint.y, pointB.x, middlePoint.y));
                } else {
                    if (randRange(0.0, 1.0) > 0.5f)
                    {   
                        newConnections.push_back(glm::vec4(pointA.x, pointA.y, pointA.x, pointB.y));
                        newConnections.push_back(glm::vec4(pointB.x, pointB.y, pointA.x, pointB.y));
                    } else {
                        newConnections.push_back(glm::vec4(pointA.x, pointA.y, pointB.x, pointA.y));
                        newConnections.push_back(glm::vec4(pointB.x, pointB.y, pointB.x, pointA.y));
                    }
                    
                }
            }

            return newConnections;
        }

        static std::vector<Edge> RandomEdges(int totalEdges, int totalRooms, float percentMore, std::vector<Edge> edges)
        {
            int numEdges = round(totalEdges * percentMore);
            std::vector<Edge> newEdges;

            for (int i = 0; i < numEdges; i++)
            {
                bool duplicate = true;

                int pointA;
                int pointB;

                while (duplicate)
                {
                    pointA = round(randRange(0, totalRooms));
                    pointB = round(randRange(0, totalRooms));


                    duplicate = false;


                    if (pointA == pointB)
                    {
                        duplicate = true;
                    }

                    

                    for (int j = 0; j < edges.size(); j++)
                    {
                        if ((edges[i].first == pointA && edges[i].second == pointB) || (edges[i].first == pointB && edges[i].second == pointA))
                        {
                            duplicate = true;
                        }
                    }

                    for (int j = 0; j < newEdges.size(); j++)
                    {
                        if ((newEdges[i].first == pointA && newEdges[i].second == pointB) || (newEdges[i].first == pointB && newEdges[i].second == pointA))
                        {
                            duplicate = true;
                        }
                    }

                    
                }

                Edge edge = Edge(pointA, pointB);
                

                newEdges.push_back(edge);
            }

            return newEdges;
        }

        static std::vector<Room> GetHallwayRooms(std::vector<Room> rooms, std::vector<Room> mainRooms, std::vector<glm::vec4> hallways)
        {
            std::vector<Room> hallwayRooms;

            for (int i = 0; i < rooms.size(); i++)
            {
                bool isMain = false;
                for (int k = 0; k < mainRooms.size(); k++)
                {
                    if (mainRooms[k].pos == rooms[i].pos && mainRooms[k].size == rooms[i].size)
                    {
                        isMain = true;
                    }
                }
                if (isMain)
                {
                    continue;
                }

                bool collided = false;

                for (int j = 0; j < hallways.size(); j++)
                {
                    
                    if (lineRect(rooms[i], hallways[j]) && !collided)
                    {
                        hallwayRooms.push_back(rooms[i]);
                        collided = true;
                    }
                }

            }

            return hallwayRooms;
        }

        static Dungeon makeDungeon(std::vector<Room> mainRooms, std::vector<Room> hallwayRooms, std::vector<glm::vec4> hallways, int gridSize)
        {
            Dungeon dungeon;

            dungeon.gridSize = gridSize;


            //find the furthest corners of the dungeon to size the grid
            glm::vec2 topLeft = glm::vec2(10000000000, 10000000000);
            glm::vec2 bottomRight = glm::vec2(-100000000, -100000000);

            for (int i = 0; i < mainRooms.size(); i++)
            {
                if (mainRooms[i].pos.x < topLeft.x)
                {
                    topLeft.x = mainRooms[i].pos.x;
                }
                if (mainRooms[i].pos.x + mainRooms[i].size.x > bottomRight.x)
                {
                    bottomRight.x = mainRooms[i].pos.x + mainRooms[i].size.x;
                }
                if (mainRooms[i].pos.y < topLeft.y)
                {
                    topLeft.y = mainRooms[i].pos.y;
                }
                if (mainRooms[i].pos.y + mainRooms[i].size.y > bottomRight.y)
                {
                    bottomRight.y = mainRooms[i].pos.y + mainRooms[i].size.y;
                }
            }

            for (int i = 0; i < hallwayRooms.size(); i++)
            {
                if (hallwayRooms[i].pos.x < topLeft.x)
                {
                    topLeft.x = hallwayRooms[i].pos.x;
                }
                if (hallwayRooms[i].pos.x + hallwayRooms[i].size.x > bottomRight.x)
                {
                    bottomRight.x = hallwayRooms[i].pos.x + hallwayRooms[i].size.x;
                }
                if (hallwayRooms[i].pos.y < topLeft.y)
                {
                    topLeft.y = hallwayRooms[i].pos.y;
                }
                if (hallwayRooms[i].pos.y + hallwayRooms[i].size.y > bottomRight.y)
                {
                    bottomRight.y = hallwayRooms[i].pos.y + hallwayRooms[i].size.y;
                }
            }

            glm::vec2 gridDimensions = glm::vec2((bottomRight.x - topLeft.x)/gridSize, (bottomRight.y - topLeft.y)/gridSize);

            for (int x = 0; x < gridDimensions.x; x++)
            {
                std::vector<int> newRow;
                dungeon.grid.push_back(newRow);
                for (int y = 0; y < gridDimensions.y; y++)
                {
                    dungeon.grid[x].push_back(0);
                }
            }




            for (int i = 0; i < mainRooms.size(); i++)
            {
                Room newRoom = mainRooms[i];
                newRoom.pos.x -= topLeft.x;
                newRoom.pos.y -= topLeft.y;
                dungeon.mainRooms.push_back(newRoom);
                for (int x = 0; x < mainRooms[i].size.x/gridSize; x++)
                {
                    for (int y = 0; y < mainRooms[i].size.y/gridSize; y++)
                    {
                        dungeon.grid[newRoom.pos.x/gridSize + x][newRoom.pos.y/gridSize + y] = 1;
                    }
                }
            }

            for (int i = 0; i < hallwayRooms.size(); i++)
            {
                Room newRoom = hallwayRooms[i];
                newRoom.pos.x -= topLeft.x;
                newRoom.pos.y -= topLeft.y;
                dungeon.hallwayRooms.push_back(newRoom);
                for (int x = 0; x < hallwayRooms[i].size.x/gridSize; x++)
                {
                    for (int y = 0; y < hallwayRooms[i].size.y/gridSize; y++)
                    {
                        dungeon.grid[newRoom.pos.x/gridSize + x][newRoom.pos.y/gridSize + y] = 1;
                    }
                }
            }


            for (int i = 0; i < hallways.size(); i++)
            {
                //check if the hallway is vertical or horizontal
                bool vertical = false;
                if (hallways[i].x == hallways[i].z)
                {
                    vertical = true;
                }

                glm::vec2 p1 = glm::vec2(round((hallways[i].x - topLeft.x)/gridSize), round((hallways[i].y - topLeft.y)/gridSize));
                glm::vec2 p2 = glm::vec2(round((hallways[i].z - topLeft.x)/gridSize), round((hallways[i].w - topLeft.y)/gridSize));

                if (!vertical)
                {
                    if (p1.x < p2.x)
                    {
                        for (int x = 0; x < p2.x - p1.x; x++)
                        {
                            dungeon.grid[x + p1.x][p1.y] = 1;
                        }
                    } else if (p1.x > p2.x)
                    {
                        for (int x = 0; x < p1.x - p2.x; x++)
                        {
                            dungeon.grid[x + p2.x][p1.y] = 1;
                        }
                    }
                }

            }
            


            return dungeon;
        }

    private:

        //look through all pairs of rooms and see if any are colliding
        static bool AnyRoomOverlapped(std::vector<Room> rooms, int numRooms)
        {
            for (int i = 0; i < numRooms; i++)
            {
                for (int j = 0; j < numRooms; j++)
                {
                    if (j == i)
                    {
                        continue;
                    }

                    if (rooms[i].isColliding(rooms[j]))
                    {
                        return true;
                    }
                }
            }

            return false;
        }

        
        //return a random number between min and max
        static float randRange(float min, float max) {
            float range = max - min;

            float num = (float)rand()/RAND_MAX;

            return num * range + min;
        }

        //get the average room size
        static glm::vec2 AverageRoomSize(std::vector<Room> rooms, int numRooms) {
            float x = 0;
            float y = 0;
            for (int i = 0; i < numRooms; i++)
            {
                x += rooms[i].size.x;
                y += rooms[i].size.y;
            }

            return glm::vec2(x/numRooms, y/numRooms);
        }   

        // LINE/RECTANGLE
        static bool lineRect(Room room, glm::vec4 line) {

            float x1 = line.x;
            float y1 = line.y;
            float x2 = line.z;
            float y2 = line.w;
            float rx = room.pos.x;
            float ry = room.pos.y;
            float rw = room.size.x;
            float rh = room.size.y;

            // check if the line has hit any of the rectangle's sides
            // uses the Line/Line function below
            bool left =   lineLine(x1,y1,x2,y2, rx,ry,rx, ry+rh);
            bool right =  lineLine(x1,y1,x2,y2, rx+rw,ry, rx+rw,ry+rh);
            bool top =    lineLine(x1,y1,x2,y2, rx,ry, rx+rw,ry);
            bool bottom = lineLine(x1,y1,x2,y2, rx,ry+rh, rx+rw,ry+rh);

            // if ANY of the above are true, the line
            // has hit the rectangle
            if (left || right || top || bottom) {
                return true;
            }
            return false;
        }

        // LINE/LINE
        static bool lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {

            // calculate the direction of the lines
            float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
            float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

            // if uA and uB are between 0-1, lines are colliding
            if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {

                // optionally, draw a circle where the lines meet
                float intersectionX = x1 + (uA * (x2-x1));
                float intersectionY = y1 + (uA * (y2-y1));

                return true;
            }
            return false;
        }


        
};


#endif