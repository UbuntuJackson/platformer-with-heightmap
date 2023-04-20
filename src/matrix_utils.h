
#ifndef MATRIX_UTILS
#define MATRIX_UTILS
#include "../include/olcPixelGameEngine.h"
struct mat3x3{
    float m[3][3];
};

struct vec3d{
    float x;
    float y;
    float w;
    vec3d(float _x, float _y);
};

mat3x3 makeTranslationMatrix(float ox, float oy);
mat3x3 makeScaleMatrix(float sx, float sy);
vec3d multiply1x3and3x3(vec3d vec, mat3x3 mat);
void RayVsRay(olc::vf2d r1_start, olc::vf2d r1_end, olc::vf2d r2_start, olc::vf2d r2_end, float &t1, float &t2);
olc::vf2d
InverseVector(const olc::vf2d _side);
#endif