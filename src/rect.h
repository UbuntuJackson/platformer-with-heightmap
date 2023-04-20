
#ifndef RECT
#define RECT
#include "../include/olcPixelGameEngine.h"
struct Rect{
    olc::vf2d pos;
    olc::vf2d size;
    Rect(olc::vf2d _pos, olc::vf2d _size);
};
struct Line{
    olc::vf2d p1;
    olc::vf2d p2;
    olc::vf2d normal;
};
#endif