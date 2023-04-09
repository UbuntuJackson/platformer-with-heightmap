#ifndef ARENA
#define ARENA


#include <vector>
#include "entity.h"
#include "../include/olcPixelGameEngine.h"
#include "collision_utils.h"

class Arena{
public:

    CollisionUtils m_collision_utils;
    std::string tiles;
    olc::vf2d map_size;
    std::vector<std::unique_ptr<Entity>> m_arena_entities; //This will contain the entities specific to the arena.
                                                            //They will have the same lifetime as the arena, and I thought
                                                            //that seems easier to keep track of than if they were still
                                                            //accessible from for example the game start menu. That'd be weird
                                                            //wouldn't it?
    Arena();
    void LoadArena(Program *program);
    void RunArena(Program* program, float _fElapsedTime);
};

#endif
//Listening for players when waiting players to choose character