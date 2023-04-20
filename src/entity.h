
#ifndef ENTITY
#define ENTITY
#include <string.h>
#include "../include/olcPixelGameEngine.h"
#include "rect.h"


class Program;


class Entity;

class Entity{
public:
    Program* program_ptr;
    std::array<bool, 4> contact;
    olc::vf2d pos;
    olc::vf2d vel;
    float acceleration_x;
    float acceleration_y;
    bool m_is_grounded;
    bool m_was_grounded;
    int s;
    olc::vf2d size;
    olc::vf2d sprite_size;
    std::string name = "";
    float r;
    std::vector<std::unique_ptr<Entity>> collision_targets;
    
    
    Entity(olc::vf2d, Program* program);
    //bool RectVsRect(Rect _rect_1, Rect _rect_2);
    //bool HitTest(Rect _ent_rect, Rect _rect, char _tile);
    //void Resolve(Rect _ent_rect, Rect _rect, char _tile);
    //void SnapToGround(Rect _ent_rect, Rect _rect, char _tile);
    virtual void Update(Program*, float _fElapsedTime);
    virtual void Draw(Program*, float _fElapsedTime);

};
#endif