#include <iostream>
#include <set>

#define MAX_MAP_SIZE 10
#define OBSTACLE_COUNT 5

using namespace std;
struct Spot
{
    int m_x;
    int m_y;
    // bool is_obstacle;
    Spot(int x, int y):m_x(x), m_y(y)/*, is_obstacle(false)*/{};
    bool operator == (Spot spot){return spot.m_x == m_x && spot.m_y == m_y;};
};

class gridMap
{
public:
    gridMap(int size);
    ~gridMap() = default;
    bool checkSpot(Spot spot);
    void initObstacle(int count);
private:
    int m_size;
    set<Spot> obstacleSpots;
    // map<Spot, bool> mapSpots;

};

