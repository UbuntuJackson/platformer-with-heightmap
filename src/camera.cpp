#include "camera.h"
#include "program.h"
#include "matrix_utils.h"
#include <string>
#include "../include/olcPixelGameEngine.h"

//struct vec3d;

Camera::Camera(){
    scale = 1.0f;
    vel = {200.0f, 200.0f};
}

void Camera::SetTarget(Entity* entity){
    target = entity;
    m_decal_wh_offset = entity->sprite_size/2;
}

void
Camera::Follow(){
    pos = target->pos;
}

void
Camera::Zoom(float _fElapsedTime){
    
    if(std::abs(scale - target_scale) < std::abs(m_delta_scale/5.0f)){
    
        m_delta_scale /= 1.1f;
    }
    scale += (m_delta_scale * _fElapsedTime);
    
}
void
Camera::SetStateZoom(float _target_scale){
    m_camera_state = ZOOM;
    target_scale = _target_scale;
    pos = {0.0, 0.0};
    m_initial_scale_difference = target_scale - scale;

    m_delta_scale = (target_scale - scale) / 2.0f;
    m_slow_down_target = m_initial_scale_difference * 0.2f;
}

void
Camera::Switch(float _fElapsedTime){
    
    if(std::sqrt(std::abs((new_target -> pos - pos).x)*std::abs((new_target -> pos - pos).x) +
        std::abs((new_target -> pos - pos).y)*std::abs((new_target -> pos - pos).y))
        < std::sqrt(std::abs((m_delta_pos).x)*std::abs((m_delta_pos).x) +
        std::abs((m_delta_pos).y)*std::abs((m_delta_pos).y)) / 2.5f
    ){
        m_delta_pos /= 1.5f;
    }
    if(std::sqrt(std::abs((new_target -> pos - pos).x)*std::abs((new_target -> pos - pos).x) +
        std::abs((new_target -> pos - pos).y)*std::abs((new_target -> pos - pos).y)) <
        0.2f
    ){
        target = new_target;
        m_camera_state = FOLLOW;
    }
    pos += (m_delta_pos * _fElapsedTime);
}

void
Camera::SetStateSwitch(Entity *entity){
    m_camera_state = SWITCH;
    new_target = entity;
    pos_diff = new_target -> pos - pos;
    m_delta_pos = pos_diff / 1.0f;
}

void
Camera::SetStateMove(olc::vf2d _vel){
    m_camera_state = MOVE;
    vel = _vel;
}

void
Camera::Move(){
    pos += vel;
}
void
Camera::Off(){
    pos = {0.0f, 0.0f};
}

void
Camera::DrawDecal(Program *program, olc::vf2d _pos, olc::Decal *_decal, float _fElapsedTime){

    switch(m_camera_state){
        case ZOOM:
            Zoom(_fElapsedTime);
            break;
        case FOLLOW:
            Follow();
            break;
        case SWITCH:
            Switch(_fElapsedTime);
            break;
        case MOVE:
            Move();
            break;
        case OFF:
            Off();
            break;
    }

    mat3x3 scaleMat = makeScaleMatrix(
        scale, scale
        );

    vec3d vec_pos {_pos.x, _pos.y};
    vec3d vec_pos_scaled = multiply1x3and3x3(vec_pos, scaleMat);

    vec3d scaled_decal = {
        multiply1x3and3x3(vec3d(m_decal_wh_offset.x, m_decal_wh_offset.y), scaleMat) //we want the decal that the target has
    };

    vec3d cam_pos {pos.x, pos.y};
    vec3d scaled_cam_pos = multiply1x3and3x3(cam_pos, scaleMat);

    mat3x3 translationMat = makeTranslationMatrix(
        scaled_cam_pos.x - program->ScreenWidth()/2.0f + scaled_decal.x/2.0f,
        scaled_cam_pos.y - program->ScreenHeight()/2.0f + scaled_decal.y/2.0f
        );
    vec3d vec_translated = multiply1x3and3x3(vec_pos_scaled, translationMat);

    program->DrawDecal(
        olc::vf2d(vec_translated.x, vec_translated.y),
        _decal,
        olc::vf2d(scale, scale));
}

int Camera::test(){
    return ZOOM;
}