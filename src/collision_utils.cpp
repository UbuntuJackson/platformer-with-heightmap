#include "collision_utils.h"
#include "rect.h"
#include "program.h"
#include "arena.h"
#include <complex>
#include <map>

CollisionUtils::CollisionUtils(Program* program) : program_ptr(program){

}

bool
CollisionUtils::RectVsRect(Rect _rect_1, Rect _rect_2){
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

float
CollisionUtils::CustomAtan2(olc::vf2d vec){
    float angle_ = std::atan2(vec.y,vec.x);
    if(angle_ < 0.0f){
        return 2.0f * M_PI - angle_;
    }
    return angle_;
}

float
CollisionUtils::GetDotProduct(olc::vf2d vec_1, olc::vf2d vec_2){
    return vec_1.x * vec_2.x + vec_1.y * vec_2.y;
}

olc::vf2d
CollisionUtils::GetCollisionNormal(std::array<Line ,4> four_sides, Rect _player_rect, olc::vf2d _vel){ //pass in rectangle

    std::vector<Line> valid_sides;
    for(int side_index = 0; side_index < four_sides.size(); side_index++){
        if( GetDotProduct(four_sides[side_index].normal,  _vel) <= 0.0f){ //if not same direction -> has to be negative
            valid_sides.push_back(four_sides[side_index]);
        }
    }

    olc::vf2d ray_origin = _player_rect.pos + _player_rect.size/2.0f;
    std::vector<std::pair<Line, std::pair<float,float>>> valid_angles;

    for(int side_index = 0; side_index < valid_sides.size(); side_index++){
        valid_angles.push_back(
            std::make_pair(
                valid_sides[side_index],
                std::make_pair(CustomAtan2(ray_origin - valid_sides[side_index].p1), CustomAtan2(ray_origin - valid_sides[side_index].p2))
            )
        );    
    }
    for(auto &p : valid_angles){
        if((p.second.first <= CustomAtan2(_vel) && CustomAtan2(_vel) <= p.second.second) ||
            (p.second.first + 2 * M_PI <= CustomAtan2(_vel) && CustomAtan2(_vel) <= p.second.second + 2 * M_PI) ||
            (p.second.first - 2 * M_PI <= CustomAtan2(_vel) && CustomAtan2(_vel) <= p.second.second - 2 * M_PI)
        ){
            std::cout << p.first.normal << std::endl;
            return p.first.normal;
        }
    }
    return olc::vd2d(0.0f, 0.0f);

}

std::vector<CollisionStruct>
CollisionUtils::GetCollisionInfo(Rect _ent_rect){
    std::vector<CollisionStruct> collisions;
    for(int y = 0; y < int(program_ptr->m_arena->map_size.y); y++){
        for(int x = 0; x < int(program_ptr->m_arena->map_size.x); x++){
            char tile = program_ptr->m_arena->tiles[y * program_ptr->m_arena->map_size.x + x];
            if(tile != '.'){
                Rect tile_rect(olc::vf2d(float(x)*32.0f, float(y)*32.0f),olc::vf2d(32.0f, 32.0f));
                if (RectVsRect(_ent_rect, tile_rect)){
                    if((tile == '2' || tile == '3')){
                        std::vector<int> valid_heights;

                        
                    
                        int start_x = int(tile_rect.pos.x);
                        int end_x = int(tile_rect.pos.x + tile_rect.size.x);

                        if(int(_ent_rect.pos.x+_ent_rect.size.x) >= int(tile_rect.pos.x) && int(_ent_rect.pos.x+_ent_rect.size.x) <= int(tile_rect.pos.x+tile_rect.size.x)) end_x = int(_ent_rect.pos.x+_ent_rect.size.x); //from right
                        if(int(_ent_rect.pos.x) <= int(tile_rect.pos.x + tile_rect.size.x) && int(_ent_rect.pos.x) >= int(tile_rect.pos.x)) start_x = int(_ent_rect.pos.x); //from left

                        int start_index = start_x-int(tile_rect.pos.x);
                        int end_index = tile_rect.size.x - (int(tile_rect.pos.x + tile_rect.size.x) - end_x);

                        for(int i = start_index; i < end_index; i++){
                            
                            if(tile == '2') valid_heights.push_back(m_height_map_north_west[i]);
                            if(tile == '3') valid_heights.push_back(m_height_map_north_east[i]);
                            
                            
                        }
                        std::vector<int>::iterator top;
                        
                        top = std::max_element(valid_heights.begin(), valid_heights.end());
                        if(valid_heights.size() != 0){
                            
                            //collisions.push_back(CollisionStruct{});
                            
                        }
                        else{
                            if(tile == '2'){
                                //if(start_index == end_index){collisions.push_back(CollisionStruct{});}
                                //if(end_index == 0){collisions.push_back(CollisionStruct{});}
                            }
                            if(tile == '3'){
                                //if(start_index == end_index){collisions.push_back(CollisionStruct{});}
                                //if(end_index == 0){collisions.push_back(CollisionStruct{});}
                            }
                        }
                    }
                    else if(tile == '1'){
                        olc::vf2d offset = tile_rect.pos;    
                        collisions.push_back(CollisionStruct{tile_rect, tile, offset});
                    }
                    //collisions.push_back(CollisionStruct{});
                                    
                }
            }
            
        }
        
    }
    return collisions;
}