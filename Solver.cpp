#include "Solver.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include "MazeSolver.hpp"
#include "Maze.hpp"
#include "MazeSolution.hpp"
#include <iostream>


ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, Solver, "Solver(REQUIRED)")

using namespace std;

Solver::Solver()
{

}

void Solver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
    mazeSolution.restart();
    setup(maze);
    std::pair <int,int> start=mazeSolution.getStartingCell();
    solve(start.first,start.second,maze,mazeSolution);
}

void Solver::setup(const Maze& maze)
{
    int x=maze.getWidth();
    int y=maze.getHeight();
    tracker.resize(x);
    for(int i=0;i<x;i++)
    {
        tracker[i].resize(y);
    }
}

void Solver::solve(int x, int y, const Maze& maze, MazeSolution& mazeSolution)
{
    if(mazeSolution.isComplete())
    {
        return;
    }
    tracker[x][y]=1;
    vector<Direction> poss=possible(x,y,maze);
    if(poss.size()==0)
    {
        mazeSolution.backUp();
        step(x,y,opposite(dirs[dirs.size()-1]));
        dirs.pop_back();
    }
    else
    {
        Direction dir=poss[0];
        dirs.push_back(dir);
        int nextx=x;
        int nexty=y;
        mazeSolution.extend(dir);
        step(nextx,nexty,dir);
        cout<<nextx<<nexty<<endl;
        solve(nextx,nexty,maze,mazeSolution);
        poss=possible(x,y,maze);
    }
    
    /* 
    tracker[x][y]=1;
    cout<<x<<y<<endl;
    vector<Direction> poss=possible(x,y,maze);
    if(!(mazeSolution.isComplete()))
    {
        if(poss.size()==0)
        {
            mazeSolution.backUp();
        }
    }
    while(poss.size()!=0)
    {
        if(mazeSolution.isComplete())
        {
            return;
        }
        if(poss.size()==0)
        {
            mazeSolution.backUp();
        }
        int nextx=x;
        int nexty=y;
        Direction dir=poss[0];
        step(nextx,nexty,dir);
        mazeSolution.extend(dir);
        tracker[nextx][nexty]=1;
        if(possible(nextx,nexty,maze).size()==0)
        {
            mazeSolution.backUp();
            solve(x,y,maze,mazeSolution);
        }
        else
        {
            solve(nextx,nexty,maze,mazeSolution);
        }
        poss=possible(x,y,maze);
    }
    */
}

void Solver::step(int& x, int& y, Direction dir)
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

Direction Solver::opposite(Direction dir)
{
    if(dir==Direction::right)
    {
        return Direction::left;
    }
    else if(dir==Direction::left)
    {
        return Direction::right;
    }
    else if(dir==Direction::up)
    {
        return Direction::down;
    }
    else
    {
        return Direction::up;
    }
}

vector<Direction> Solver::possible(int x, int y, const Maze& maze)
{
    vector<Direction> poss;
    if(within(x,y,Direction::right,maze)&&!(maze.wallExists(x,y,Direction::right))&&tracker[x+1][y]==0)
    {
        cout<<"right"<<endl;
        poss.push_back(Direction::right);
    }
    if(within(x,y,Direction::down,maze)&&!(maze.wallExists(x,y,Direction::down))&&tracker[x][y+1]==0)
    {
        cout<<"down"<<endl;
        poss.push_back(Direction::down);
    }
    if(within(x,y,Direction::left,maze)&&!(maze.wallExists(x,y,Direction::left))&&tracker[x-1][y]==0)
    {
        cout<<"left"<<endl;
        poss.push_back(Direction::left);
    }
    if(within(x,y,Direction::up,maze)&&!(maze.wallExists(x,y,Direction::up))&&tracker[x][y-1]==0)
    {
        cout<<"up"<<endl;
        poss.push_back(Direction::up);
    }
    cout<<"---------------"<<endl;
    return poss;
}

bool Solver::within(int x, int y, Direction dir, const Maze& maze)
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