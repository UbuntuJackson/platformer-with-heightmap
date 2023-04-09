#ifndef CAMERA
#define CAMERA
#include <string>
#include "../include/olcPixelGameEngine.h"
#include "entity.h"
class Program;

enum CameraStates{
  FOLLOW, //Camera will be set to seem like it focuses on the center point of a sprite.
  SWITCH, //Transitions from one target to another
    MOVE, //Applies a movement vector to the camera position.
	    //This state would require some parameters I guess
    ZOOM,  //Transitions into a different scaling factor. Need to give the program a scaling factor
	    // Transition into
  OFF
};

class Camera{
public:
    float scale;
    olc::vf2d pos;
    olc::vf2d vel;
    int m_camera_state;
    Entity* target;
    float target_scale;
    float m_initial_scale_difference;
    float m_delta_scale;
    float m_slow_down_target;

    olc::vf2d m_delta_pos;
    olc::vf2d pos_diff;
    Entity* new_target;
    olc::vf2d m_decal_wh_offset;

    Camera();
    void SetTarget(Entity *entity);
    void Zoom(float _fElapsedTime);
    void Follow();
    void Move();
    void Off();
    void Switch(float _fElapsedTime);
    void SetStateSwitch(Entity *entity);
    void SetStateZoom(float _target_scale);
    void SetStateMove(olc::vf2d _vel);
    void DrawDecal(Program *program, olc::vf2d _pos, olc::Decal *_decal, float _fElapsedTime);
    int test();
};
#endif