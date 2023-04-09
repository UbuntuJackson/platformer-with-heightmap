#include "player.h"
#include "program.h"
#include "../include/olcPixelGameEngine.h"
//#include "entity.h"

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
    
    vel.x *= 0.9;
    vel.y *= 0.96;

    

    for(int y = 0; y < int(program->m_arena.map_size.y); y++){
        for(int x = 0; x < int(program->m_arena.map_size.x); x++){
            char tile = program->m_arena.tiles[y * program->m_arena.map_size.x + x];
            if(tile != '.'){
                Rect player_rect(olc::vf2d(pos.x+vel.x*_fElapsedTime, pos.y), size);
                Rect rect(olc::vf2d(float(x)*32.0f, float(y)*32.0f),olc::vf2d(32.0f, 32.0f));
                HitTest(player_rect ,rect, tile);      
            }
            
        }
        
    }

    m_was_grounded = m_is_grounded;
    m_is_grounded = false;
    
    pos+=vel*_fElapsedTime;

    for(int y = 0; y < int(program->m_arena.map_size.y); y++){
        for(int x = 0; x < int(program->m_arena.map_size.x); x++){
            char tile = program->m_arena.tiles[y * program->m_arena.map_size.x + x];
            if(tile != '.'){
                Rect player_rect(olc::vf2d(pos.x+vel.x*_fElapsedTime, pos.y), size);
                Rect rect(olc::vf2d(float(x)*32.0f, float(y)*32.0f),olc::vf2d(32.0f, 32.0f));
                HitTest(player_rect ,rect, tile);      
            }
            
        }
        
    }

    for(int y = 0; y < int(program->m_arena.map_size.y); y++){
        for(int x = 0; x < int(program->m_arena.map_size.x); x++){
            char tile = program->m_arena.tiles[y * program->m_arena.map_size.x + x];
            if(tile != '.'){
                Rect player_rect(olc::vf2d(pos.x+vel.x*_fElapsedTime, pos.y+32.0f), size);
                Rect rect(olc::vf2d(float(x)*32.0f, float(y)*32.0f),olc::vf2d(32.0f, 32.0f));
                if(tile != '1' && m_was_grounded){
                    FindSlopeTop(player_rect ,rect, tile);
                }            
                
            }
            
        }
        
    }
    
}

void
Player::Draw(Program* program, float _fElapsedTime){
    program->camera.DrawDecal(program, olc::vf2d(pos.x, pos.y+32.0f), program -> AssetSingleton.decTestDecal.get(), _fElapsedTime);
    program->camera.DrawDecal(program, pos, program -> AssetSingleton.decTestDecal.get(), _fElapsedTime);
    //program->DrawDecal(pos, program -> AssetSingleton.decTestDecal.get());
}