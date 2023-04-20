#include "player.h"
#include "program.h"
#include "../include/olcPixelGameEngine.h"
//#include "entity.h"
#include "collision_utils.h"
#include "arena.h"


Player::Player(olc::vf2d _pos, Program* program) : Entity{_pos, program}
{
    vel = {0.0f, 0.0f};
    size = {32.0f, 32.0f};
    r = 16.0f;
    acceleration_x = 40.0f;
    acceleration_y = 20.0f;

}

void
Player::Update(Program* program, float _fElapsedTime) {
    
    if(program->GetKey(olc::Key::RIGHT).bHeld) vel.x += acceleration_x;
    if(program->GetKey(olc::Key::LEFT).bHeld) vel.x -= acceleration_x;
    vel.y += acceleration_y;
    
    if(program->GetKey(olc::Key::Z).bPressed) vel.y = -500.0f;

    vel.x *= 0.9;
    vel.y *= 0.99;

    std::vector<CollisionStruct> collision_info;
    std::vector<CollisionStruct> terrain_info;

    //Rect player_rect(olc::vf2d(pos.x, pos.y), size);
    Rect player_rect(olc::vf2d(pos.x, pos.y), size);
    collision_info = program_ptr->m_arena->m_collision_utils->GetCollisionInfo(player_rect);

    for(auto& info : collision_info){
        
        std::array<Line, 4> four_sides = {
            Line{info.rect.pos, info.rect.pos + olc::vf2d(info.rect.size.x, 0.0f), olc::vf2d(0.0f,-1.0f)},
            Line{info.rect.pos + olc::vf2d(info.rect.size.x, 0.0f), info.rect.pos + info.rect.size, olc::vf2d(1.0f,0.0f)},
            Line{info.rect.pos + info.rect.size, info.rect.pos + info.rect.size - olc::vf2d(info.rect.size.x, 0.0f), olc::vf2d(0.0f,1.0f)},
            Line{info.rect.pos + info.rect.size - olc::vf2d(info.rect.size.x, 0.0f), info.rect.pos, olc::vf2d(-1.0f,0.0f)}
        };
        
        olc::vf2d collision_normal = program_ptr->m_arena->m_collision_utils->GetCollisionNormal(four_sides, Rect(player_rect.pos, player_rect.size), vel);
        
        if(collision_normal.y < 0.0f){
            pos.y = info.rect.pos.y - size.y;
        }
        if(collision_normal.x < 0.0f){
            pos.x = info.rect.size.x - size.y;
        }
        if(collision_normal.y > 0.0f){
            pos.y = info.rect.pos.y + info.rect.size.y;
        }
        if(collision_normal.x > 0.0f){
            pos.x = info.rect.pos.x + info.rect.size.x;
        }
        
        vel += vel * collision_normal;
    }
    
    pos+=vel*_fElapsedTime;
    
}

void
Player::Draw(Program* program, float _fElapsedTime){
    //program->camera.DrawDecal(program, olc::vf2d(pos.x, pos.y+32.0f), program -> AssetSingleton.decTestDecal.get(), _fElapsedTime);
    program->camera.DrawDecal(program, pos, program -> AssetSingleton.decTestDecal.get(), _fElapsedTime);
}