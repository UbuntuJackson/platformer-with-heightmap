#include "matrix_utils.h"
#include "../include/olcPixelGameEngine.h"

vec3d::vec3d(float _x, float _y):x{_x}, y{_y}, w{1.0f}{}

mat3x3 makeTranslationMatrix(float ox, float oy){


    
    mat3x3 mat;

    mat.m[0][0] = 1.0f;
    mat.m[0][1] = 0.0f;
    mat.m[0][2] = 0.0f;
    mat.m[1][0] = 0.0f;
    mat.m[1][1] = 1.0f;
    mat.m[1][2] = 0.0f;
    mat.m[2][0] = -ox;
    mat.m[2][1] = -oy;
    mat.m[2][2] = 0.0f;
    
    return mat;
}

mat3x3 makeScaleMatrix(float sx, float sy){


    
    mat3x3 mat;

    mat.m[0][0] = sx;
    mat.m[0][1] = 0.0f;
    mat.m[0][2] = 0.0f;
    mat.m[1][0] = 0.0f;
    mat.m[1][1] = sy;
    mat.m[1][2] = 0.0f;
    mat.m[2][0] = 0.0f;
    mat.m[2][1] = 0.0f;
    mat.m[2][2] = 1;
    
    return mat;
}

vec3d multiply1x3and3x3(vec3d vec, mat3x3 mat){
    vec3d out_p_vec {0.0f, 0.0f};
    out_p_vec.x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.w * mat.m[2][0];
    out_p_vec.y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.w * mat.m[2][1];
    out_p_vec.w = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.w * mat.m[2][2];
    
    return out_p_vec;
}

void
RayVsRay(olc::vf2d r1_start, olc::vf2d r1_end, olc::vf2d r2_start, olc::vf2d r2_end, float &t1, float &t2) {
		
    olc::vf2d line_r1s = r1_start;
    olc::vf2d line_r1e = r1_end;
    olc::vf2d line_r2s = r2_start;
    olc::vf2d line_r2e = r2_end;

    float h = (line_r2e.x - line_r2s.x) * (line_r1s.y - line_r1e.y) - (line_r1s.x - line_r1e.x) * (line_r2e.y - line_r2s.y);
    t1 = ((line_r2s.y - line_r2e.y) * (line_r1s.x - line_r2s.x) + (line_r2e.x - line_r2s.x) * (line_r1s.y - line_r2s.y)) / h;
    t2 = ((line_r1s.y - line_r1e.y) * (line_r1s.x - line_r2s.x) + (line_r1e.x - line_r1s.x) * (line_r1s.y - line_r2s.y)) / h;
    
}

olc::vf2d
InverseVector(const olc::vf2d _side) {
    olc::vf2d inverse_vec;
    
    inverse_vec.x = _side.y;
    inverse_vec.y = -_side.x;
    
    return inverse_vec.norm();
    
}