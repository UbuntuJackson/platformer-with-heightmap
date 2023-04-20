#include "entity.h"
#include "program.h"
#include "matrix_utils.h"
#include "rect.h"
#include "collision_utils.h"
#include <string>
#include <vector>
#include "arena.h"
#include "../include/olcPixelGameEngine.h"


Entity::Entity(olc::vf2d _pos, Program* program) : pos{_pos}, program_ptr{program}
{
    sprite_size = {program_ptr->AssetSingleton.decBigDecal.get()->sprite->Size().x,
                    program_ptr->AssetSingleton.decBigDecal.get()->sprite->Size().y};
    size = {32.0f, 32.0f};
    vel = {0.0f, 200.0f};
    acceleration_x = 20.0f;
    acceleration_y = 20.0f;
    r = 32.0f;
    s = 0;

}

/*bool
Entity::RectVsRect(Rect _rect_1, Rect _rect_2){
    if (
        (_rect_1.pos.x > (_rect_2.pos.x + _rect_2.size.x)) || // is the left side greater than the other rect's right side?
        ((_rect_1.pos.x + _rect_1.size.x) < _rect_2.pos.x) ||       // is the right side less than the other rect's left side?
        (_rect_1.pos.y > (_rect_2.pos.y + _rect_2.size.y)) || // is the lower side greater than the other rect's upper side?
        ((_rect_1.pos.y + _rect_1.size.y) < _rect_2.pos.y))         // is the upper side less than the other rect's lower side?
    {
        return false;
    }
    return true;
}
bool
Entity::HitTest(Rect _ent_rect, Rect _rect, char _tile){

    
    if((_tile == '2' || _tile == '3')){
        std::vector<int> valid_heights;

        
    
        int start_x = int(_rect.pos.x);
        int end_x = int(_rect.pos.x + _rect.size.x);

        if(int(_ent_rect.pos.x+_ent_rect.size.x) >= int(_rect.pos.x) && int(_ent_rect.pos.x+_ent_rect.size.x) <= int(_rect.pos.x+_rect.size.x)) end_x = int(_ent_rect.pos.x+size.x); //from right
        if(int(_ent_rect.pos.x) <= int(_rect.pos.x + _rect.size.x) && int(_ent_rect.pos.x) >= int(_rect.pos.x)) start_x = int(_ent_rect.pos.x); //from left

        int start_index = start_x-int(_rect.pos.x);
        int end_index = _rect.size.x - (int(_rect.pos.x + _rect.size.x) - end_x);

        for(int i = start_index; i < end_index; i++){
            
            if(_tile == '2') valid_heights.push_back(program_ptr->m_arena->m_collision_utils->m_height_map_north_west[i]);
            if(_tile == '3') valid_heights.push_back(program_ptr->m_arena->m_collision_utils->m_height_map_north_east[i]);
            
            
        }
        std::vector<int>::iterator top;
        
        top = std::max_element(valid_heights.begin(), valid_heights.end());
        if(valid_heights.size() != 0){
            
            return true;
            
        }
        else{
            if(_tile == '2'){
                if(start_index == end_index){return true;}
                if(end_index == 0){return true;}
            }
            if(_tile == '3'){
                if(start_index == end_index){return true;}
                if(end_index == 0){return true;}
            }
        }
    }
    else if(_tile == '1'){
        return true;
    }
    return false;
    
    
}
void
Entity::Resolve(Rect _ent_rect, Rect _rect, char _tile){

    
    if((_tile == '2' || _tile == '3')){
        std::vector<int> valid_heights;

        
    
        int start_x = int(_rect.pos.x);
        int end_x = int(_rect.pos.x + _rect.size.x);

        if(int(_ent_rect.pos.x+_ent_rect.size.x) >= int(_rect.pos.x) && int(_ent_rect.pos.x+_ent_rect.size.x) <= int(_rect.pos.x+_rect.size.x)) end_x = int(_ent_rect.pos.x+size.x); //from right
        if(int(_ent_rect.pos.x) <= int(_rect.pos.x + _rect.size.x) && int(_ent_rect.pos.x) >= int(_rect.pos.x)) start_x = int(_ent_rect.pos.x); //from left

        int start_index = start_x-int(_rect.pos.x);
        int end_index = _rect.size.x - (int(_rect.pos.x + _rect.size.x) - end_x);

        for(int i = start_index; i < end_index; i++){
            
            if(_tile == '2') valid_heights.push_back(program_ptr->m_arena.m_collision_utils.m_height_map_north_west[i]);
            if(_tile == '3') valid_heights.push_back(program_ptr->m_arena.m_collision_utils.m_height_map_north_east[i]);
            
            
        }
        std::vector<int>::iterator top;
        
        top = std::max_element(valid_heights.begin(), valid_heights.end());
        if(valid_heights.size() != 0){
            if(_ent_rect.pos.y+_ent_rect.size.y >= _rect.pos.y+_rect.size.y-*top){
                pos.y =  _rect.pos.y+_rect.size.y-*top-_ent_rect.size.y;
                vel.y = 0.0f;
            }
            
        }
        else{
            if(_tile == '2'){
                if(start_index == end_index){pos.y =  _rect.pos.y+_rect.size.y-32.0f-_ent_rect.size.y;}
                if(end_index == 0){pos.y =  _rect.pos.y+_rect.size.y-0.0f-_ent_rect.size.y;}
            }
            if(_tile == '3'){
                if(start_index == end_index){pos.y =  _rect.pos.y+_rect.size.y-0.0f-_ent_rect.size.y;}
                if(end_index == 0){pos.y =  _rect.pos.y+_rect.size.y-32.0f-_ent_rect.size.y;}
            }
        }
    }
    else if(_tile == '1'){
        pos.y = _rect.pos.y-size.y;
        vel.y = 0.0f;
    }
    
    
}

void
Entity::SnapToGround(Rect _ent_rect, Rect _rect, char _tile){

    std::vector<int> valid_heights;

    int start_x = int(_rect.pos.x);
    int end_x = int(_rect.pos.x + _rect.size.x);

    if(int(_ent_rect.pos.x+_ent_rect.size.x) >= int(_rect.pos.x) && int(_ent_rect.pos.x+_ent_rect.size.x) <= int(_rect.pos.x+_rect.size.x)) end_x = int(_ent_rect.pos.x+size.x); //from right
    if(int(_ent_rect.pos.x) <= int(_rect.pos.x + _rect.size.x) && int(_ent_rect.pos.x) >= int(_rect.pos.x)) start_x = int(_ent_rect.pos.x); //from left

    int start_index = start_x-int(_rect.pos.x);
    int end_index = _rect.size.x - (int(_rect.pos.x + _rect.size.x) - end_x);

    for(int i = start_index; i < end_index; i++){
        
        if(_tile == '2') valid_heights.push_back(program_ptr->m_arena.m_collision_utils.m_height_map_north_west[i]);
        if(_tile == '3') valid_heights.push_back(program_ptr->m_arena.m_collision_utils.m_height_map_north_east[i]);
        
        
    }
    std::vector<int>::iterator top;
    
    top = std::max_element(valid_heights.begin(), valid_heights.end());
    if(valid_heights.size() != 0){
        
        pos.y =  _rect.pos.y+_rect.size.y-*top-_ent_rect.size.y;
                        
    }
    else{
        if(_tile == '2'){
            if(start_index == end_index){pos.y =  _rect.pos.y+_rect.size.y-32.0f-_ent_rect.size.y;}
            if(end_index == 0){pos.y =  _rect.pos.y+_rect.size.y-0.0f-_ent_rect.size.y;}
        }
        if(_tile == '3'){
            if(start_index == end_index){pos.y =  _rect.pos.y+_rect.size.y-0.0f-_ent_rect.size.y;}
            if(end_index == 0){pos.y =  _rect.pos.y+_rect.size.y-32.0f-_ent_rect.size.y;}
        }
    }
    
    
}*/

void
Entity::Update(Program* program, float _fElapsedTime){pos += vel * _fElapsedTime;}

void
Entity::Draw(Program* program, float _fElapsedTime){
    program->camera.DrawDecal(program, pos, program -> AssetSingleton.decBigDecal.get(), _fElapsedTime);
}
