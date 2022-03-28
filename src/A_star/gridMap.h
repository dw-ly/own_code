// #include <iostream>
// #include <set>

// #define MAX_MAP_SIZE 10
// #define OBSTACLE_COUNT 5

// using namespace std;
// struct Spot
// {
//     int m_x;
//     int m_y;
//     // bool is_obstacle;
//     Spot(int x, int y):m_x(x), m_y(y)/*, is_obstacle(false)*/{};
//     Spot():m_x(0), m_y(0){};//默认构造函数
//     bool operator == (Spot spot){return spot.m_x == m_x && spot.m_y == m_y;};
//     Spot operator = (Spot spot){return Spot(spot.m_x, spot.m_y);};
// };

// class gridMap
// {
// public:
//     gridMap(int size);
//     ~gridMap() = default;
//     bool checkSpot(Spot spot);
//     void initObstacle(int count);
//     void initStartAndEnd(Spot start = Spot(0, 0), Spot end = Spot(MAX_MAP_SIZE - 1, MAX_MAP_SIZE - 1));
//     void init();
// private:
//     int m_size;
//     Spot m_start;//不带参数会提示没有默认构造函数，或者添加一个默认构造函数
//     Spot m_end;
//     set<Spot> obstacleSpots;
//     // map<Spot, bool> mapSpots;

// };

