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

    std::vector<std::pair<Rect, char>> m_collision_info;
    std::vector<std::pair<Rect, char>> m_terrain_info;

    m_is_grounded = false;

    for(int y = 0; y < int(program->m_arena.map_size.y); y++){
        for(int x = 0; x < int(program->m_arena.map_size.x); x++){
            char tile = program->m_arena.tiles[y * program->m_arena.map_size.x + x];
            if(tile != '.'){
                Rect player_rect(olc::vf2d(pos.x+vel.x*_fElapsedTime, pos.y), size);
                Rect rect(olc::vf2d(float(x)*32.0f, float(y)*32.0f),olc::vf2d(32.0f, 32.0f));
                if (RectVsRect(player_rect, rect)) m_collision_info.push_back(std::make_pair(rect, tile));    
            }
            
        }
        
    }
    std::sort(m_collision_info.begin(), m_collision_info.end(), [](std::pair<Rect, char> a, std::pair<Rect, char> b)
    {
        return a.first.pos.y > b.first.pos.y;
    });

    float y_before = pos.y;

    for(auto &info : m_collision_info){
        Rect player_rect(olc::vf2d(pos.x+vel.x*_fElapsedTime, pos.y), size);
        if(HitTest(player_rect, info.first, info.second)) m_is_grounded = true;
        Resolve(player_rect ,info.first, info.second);
    }
    
    m_collision_info.clear(); 
    
    m_was_grounded = m_is_grounded;
    m_is_grounded = false;
    pos+=vel*_fElapsedTime;

    for(int y = 0; y < int(program->m_arena.map_size.y); y++){
        for(int x = 0; x < int(program->m_arena.map_size.x); x++){
            char tile = program->m_arena.tiles[y * program->m_arena.map_size.x + x];
            if(tile != '.'){
                Rect player_rect(olc::vf2d(pos.x+vel.x*_fElapsedTime, pos.y), size);
                Rect rect(olc::vf2d(float(x)*32.0f, float(y)*32.0f),olc::vf2d(32.0f, 32.0f));
                Rect snap_rect(olc::vf2d(pos.x+vel.x*_fElapsedTime, pos.y+32.0f), size);

                if (RectVsRect(player_rect, rect)) m_collision_info.push_back(std::make_pair(rect, tile));
                if (RectVsRect(snap_rect, rect) && tile != '1') m_terrain_info.push_back(std::make_pair(rect, tile));       
            }
            
        }
        
    }
    
    float y_after = pos.y;

    for(auto &info : m_collision_info){
        Rect player_rect(olc::vf2d(pos.x+vel.x*_fElapsedTime, pos.y), size);
        std::cout << HitTest(player_rect, info.first, info.second) << std::endl;
        if(HitTest(player_rect, info.first, info.second)) m_is_grounded = true;
        
    }
    
    std::sort(m_terrain_info.begin(), m_terrain_info.end(), [](std::pair<Rect, char> a, std::pair<Rect, char> b)
    {
        return a.first.pos.y > b.first.pos.y;
    });

    /*std::vector<std::pair<Rect, char>>::iterator max_available_slope;
    max_available_slope = std::max_element(m_terrain_info.begin(), m_terrain_info.end(),
        [](std::pair<Rect, char> a, std::pair<Rect, char> b)
        {
            return a.first.pos.y > b.first.pos.y;
        }
    );*/
    
    
    for(auto &slope : m_terrain_info){
        if(m_was_grounded && /*!(y_before >= y_after) &&*/ !m_is_grounded && m_terrain_info.size() != 0){
            Rect player_rect(olc::vf2d(pos.x+vel.x*_fElapsedTime, pos.y+32.0f), size);
            SnapToGround(player_rect, slope.first, slope.second);
        }
    }
    
    
    
}

void
Player::Draw(Program* program, float _fElapsedTime){
    program->camera.DrawDecal(program, olc::vf2d(pos.x, pos.y+32.0f), program -> AssetSingleton.decTestDecal.get(), _fElapsedTime);
    program->camera.DrawDecal(program, pos, program -> AssetSingleton.decTestDecal.get(), _fElapsedTime);
}