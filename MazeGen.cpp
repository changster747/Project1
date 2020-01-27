#include "MazeGen.hpp"
#include "MazeGenerator.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include "Maze.hpp"
#include <vector>
#include <time.h>
#include <iostream>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, MazeGen, "MazeGen(REQUIRED)");

using namespace std;

MazeGen::MazeGen()
{

}

void MazeGen::generateMaze(Maze& maze) 
{
    maze.addAllWalls();
    setup(maze);
    move(0,0,maze);
}

void MazeGen::setup(Maze& maze)
{
    int x=maze.getWidth();
    int y=maze.getHeight();
    tracker.resize(x);
    for(int i=0;i<x;i++)
    {
        tracker[i].resize(y);
    }
}

void MazeGen::move(int x, int y, Maze& maze)
{
    srand(time(0));
    tracker[x][y]=1;
    vector<Direction> poss=possible(x,y,maze);
    while(poss.size()!=0)
    {
        int nextx=x;
        int nexty=y;
        Direction dir=poss[rand()%(poss.size())];
        step(nextx,nexty,dir);
        if(tracker[nextx][nexty]==0)
        {
            if(maze.wallExists(x,y,dir))
            {
                maze.removeWall(x,y,dir);
                move(nextx,nexty,maze);
            }
        }
        poss=possible(x,y,maze);
    }
}

void MazeGen::step(int& x, int& y, Direction dir)
{
    if(dir==Direction::right)
    {
        x+=1;
    }
    else if(dir==Direction::down)
    {
        y+=1;
    }
    else if(dir==Direction::left)
    {
        x-=1;
    }
    else
    {
        y-=1;
    }  
}

vector<Direction> MazeGen::possible(int x, int y, Maze& maze)
{
    vector<Direction> poss;
    if(within(x,y,Direction::right,maze)&&tracker[x+1][y]==0)
    {
        poss.push_back(Direction::right);
    }
    if(within(x,y,Direction::down,maze)&&tracker[x][y+1]==0)
    {
        poss.push_back(Direction::down);
    }
    if(within(x,y,Direction::left,maze)&&tracker[x-1][y]==0)
    {
        poss.push_back(Direction::left);
    }
    if(within(x,y,Direction::up,maze)&&tracker[x][y-1]==0)
    {
        poss.push_back(Direction::up);
    }
    return poss;
}

bool MazeGen::within(int x, int y, Direction dir, Maze& maze)
{
    if(dir == Direction::right)
    {
        if(x+1>maze.getWidth()-1)
        {
            return false;
        }
    }
    else if(dir == Direction::down)
    {
        if(y+1>maze.getHeight()-1)
        {
            return false;
        }
    }
    else if(dir == Direction::left)
    {
        if(x-1<0)
        {
            return false;
        }
    }
    else if(dir == Direction::up)
    {
        if(y-1<0)
        {
            return false;
        }
    }
    else
    {
        return true;
    }
    return true;
}