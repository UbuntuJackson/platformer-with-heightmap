#include "arena.h"
#include "../include/olcPixelGameEngine.h"
#include "program.h"
#include "player.h"

Arena::Arena(){
    tiles = "........................................"
            "................1......................."
            "........................................"
            "..............1........................."
            "........................................"
            "...........1...............2111111111111"
            "..........................2............."
            ".........................2.............."
            "........................2..............."
            "...........21111.......2................"
            ".........2111.........2................."
            ".......2111..........2.................."
            ".....211.......213..2..................."
            "1111111111111111.1111111111111..........";
    map_size = {40, 14};
    
}
void
Arena::LoadArena(Program *program){
    m_arena_entities.push_back(std::make_unique<Player>(olc::vf2d(2.0f, 2.0f), program));
    program->camera.m_camera_state = FOLLOW;
    program->camera.SetTarget(m_arena_entities[0].get());
    program->camera.scale = 3.0f;
}

void
Arena::RunArena(Program* program, float _fElapsedTime){
    for(int e = 0; e < m_arena_entities.size(); e++){
        m_arena_entities[e]->Update(program, _fElapsedTime);
    }
	for(int e = 0; e < m_arena_entities.size(); e++){
        m_arena_entities[e]->Draw(program, _fElapsedTime);
    }
    for(int y = 0; y < int(map_size.y); y++){
        for(int x = 0; x < int(map_size.x); x++){
            char tile = tiles[y * map_size.x + x];
            if(tile == '1'){
                program->camera.DrawDecal(program, olc::vf2d(float(x)*32.0f, float(y)*32.0f), program -> AssetSingleton.decGroundDecal.get(), _fElapsedTime);
                //program->DrawDecal(olc::vf2d(x*32.0f, y*32.0f), program -> AssetSingleton.decGroundDecal.get());
            }
            else if(tile == '2'){
                program->camera.DrawDecal(program, olc::vf2d(float(x)*32.0f, float(y)*32.0f), program -> AssetSingleton.decNorthWestDecal.get(), _fElapsedTime);
                //program->DrawDecal(olc::vf2d(x*32.0f, y*32.0f), program -> AssetSingleton.decNorthEastDecal.get());
            }
            else if(tile == '3'){
                program->camera.DrawDecal(program, olc::vf2d(float(x)*32.0f, float(y)*32.0f), program -> AssetSingleton.decNorthEastDecal.get(), _fElapsedTime);
                //program->DrawDecal(olc::vf2d(x*32.0f, y*32.0f), program -> AssetSingleton.decNorthWestDecal.get());
            }
        }
    }
}