#include "MazeSolver.hpp"
#include "Maze.hpp"
#include "MazeSolution.hpp"
#ifndef SOLVER_HPP
#define SOLVER_HPP

using namespace std;

class Solver: public MazeSolver
{
    public:
        Solver();
        void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
        void setup(const Maze& maze);
        void solve(int x, int y, const Maze& maze, MazeSolution& mazeSolution);
        void step(int& x, int& y, Direction dir);
        Direction opposite(Direction dir);
        vector<Direction> possible(int x, int y, const Maze& maze);
        bool within(int x, int y, Direction dir, const Maze& maze);
    private:
        vector<vector<int>> tracker;
        vector<Direction> dirs;
};

#endif