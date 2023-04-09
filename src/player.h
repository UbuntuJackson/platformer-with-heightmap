#include "../include/olcPixelGameEngine.h"
#include "entity.h"
class Player : public Entity{
public:
    Player(olc::vf2d _pos, Program* program);
    virtual void Update(Program* program, float _fElapsedTime);
    virtual void Draw(Program* program, float _fElapsedTime);
};