#include <iostream>
struct spot
{
    int m_x;
    int m_y;
    bool is_obstacle;
    spot(int x, int y):m_x(x), m_y(y), is_obstacle(false){};
    bool operator == (spot a, spot b){return a.m_x == b.m_x && a.m_y == b.m_y};
}

class gridMap
{
public:
    gridMap(int size);
    ~gridMap() = default;
    checkSpot(int x, int y);
    initObstacle();
private:
    int m_size;
    map<spot, bool> maps;

};

gridMap(int size)
{
    m_size = size;
}
checkSpot(int x, int y)
{

}