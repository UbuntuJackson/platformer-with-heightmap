#ifndef COLLISION_UTILS
#define COLLISION_UTILS

enum CollisionType {
    NONE,
    RECTANGLE,
    SLOPE_CEIL,
    SLOPE_FLOOR
};

class CollisionUtils{
public:
    int m_height_map_south_west[32];
    int m_height_map_south_east[32];
    int m_height_map_north_west[32]= {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
    int m_height_map_north_east[32] = {32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
    int m_height_map_north_west_1_half[32]= {1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,16,16};
    int m_height_map_north_east_1_half[32] = {32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
    CollisionUtils() = default;
};
#endif