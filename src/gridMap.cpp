#include "gridMap.h"

gridMap::gridMap(int size)
{
    m_size = size;
}

void gridMap::init()
{
    initStartAndEnd();
    initObstacle(OBSTACLE_COUNT);
}

void gridMap::initObstacle(int count)
{
    for (int i = 0; i < count; i++)
    {
        int r_x = rand();
        int r_y = rand();
        obstacleSpots.emplace(Spot(r_x, r_y));    
    }
}
void gridMap::initStartAndEnd(Spot start, Spot end)
{
    m_start = move(start);
    m_end = move(end);
}

bool gridMap::checkSpot(Spot spot)
{
    return obstacleSpots.find(spot) == obstacleSpots.end();
}