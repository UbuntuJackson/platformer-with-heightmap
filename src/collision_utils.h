

#ifndef COLLISION_UTILS
#define COLLISION_UTILS

#include "rect.h"
#include "../include/olcPixelGameEngine.h"

class Program;

enum CollisionType {
    NONE,
    RECTANGLE,
    SLOPE_CEIL,
    SLOPE_FLOOR
};

struct CollisionStruct{
    Rect rect;
    char tile;
    olc::vf2d offset_from_up_left;
};

class CollisionUtils{
public:
    Program* program_ptr;
    int m_height_map_south_west[32];
    int m_height_map_south_east[32];
    int m_height_map_north_west[32]= {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
    int m_height_map_north_east[32] = {32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
    int m_height_map_north_west_1_half[32]= {1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,16,16};
    int m_height_map_north_east_1_half[32] = {32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
    CollisionUtils(Program* program);
    olc::vf2d GetCollisionNormal(std::array<Line ,4> four_sides, Rect _player_rect, olc::vf2d _vel);
    float CustomAtan2(olc::vf2d vec);
    float GetDotProduct(olc::vf2d vec_1, olc::vf2d vec_2);
    bool RectVsRect(Rect _rect_1, Rect _rect_2);
    std::vector<CollisionStruct> GetCollisionInfo(Rect _ent);
};
#endif