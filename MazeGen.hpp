#include <vector>
#include "Maze.hpp"
#include "MazeGenerator.hpp"
#ifndef MAZEGEN_HPP
#define MAZEGEN_HPP

using namespace std;

class MazeGen: public MazeGenerator
{
    public:
        MazeGen();
        void generateMaze(Maze& maze);
        void setup(Maze& maze);
        void move(int x, int y, Maze& maze);
        void step(int& x, int& y, Direction dir);
        vector<Direction> possible(int x, int y, Maze& maze);
        bool within(int x, int y, Direction dir, Maze& maze);
    private:
        vector<vector<int>> tracker;
};

#endif