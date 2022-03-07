#include "gridMap.h"

void gridMap::initStartAndEnd(Spot start, Spot end)
{
    m_start = move(start);
    m_end = move(end);
}

gridMap::gridMap(int size)
{
    m_size = size;
}

bool gridMap::checkSpot(Spot spot)
{
    return obstacleSpots.find(spot) == obstacleSpots.end();
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
