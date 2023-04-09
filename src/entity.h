#ifndef ENTITY
#define ENTITY



class Program;
#include <string.h>
#include "../include/olcPixelGameEngine.h"
#include "rect.h"

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
    olc::vf2d size;
    olc::vf2d sprite_size;
    std::string name = "";
    float r;
    std::vector<std::unique_ptr<Entity>> collision_targets;

    Entity(olc::vf2d, Program* program);
    void HitTest(Rect _ent_rect, Rect _rect, char _tile);
    void FindSlopeTop(Rect _ent_rect, Rect _rect, char _tile);
    virtual bool CircleVsCircle(Entity* _ent, float _fElapsedTime);
    virtual void Update(Program*, float _fElapsedTime);
    virtual void Draw(Program*, float _fElapsedTime);

};
#endif