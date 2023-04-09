#ifndef RECT
#define RECT

#include "../include/olcPixelGameEngine.h"
struct Rect{
    olc::vf2d pos;
    olc::vf2d size;
    Rect(olc::vf2d _pos, olc::vf2d _size);
};
#endif