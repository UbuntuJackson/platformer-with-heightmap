#define OLC_PGE_APPLICATION
#include "program.h"
#include "camera.h"
#include "entity.h"
#include "arena.h"
#include "../include/olcPixelGameEngine.h"
#include <iostream>


//class Arena;

Program::Program() : m_arena(new Arena(this))
{
	sAppName = "Camera";
}

bool
Program::OnUserCreate()
{
    m_key_config_1["right"] = olc::Key::RIGHT;
    m_key_config_1["left"] = olc::Key::LEFT;

    AssetSingleton.sprTestSprite = std::make_unique<olc::Sprite>("../res/gfx/test.png");
    AssetSingleton.decTestDecal = std::make_unique<olc::Decal>(AssetSingleton.sprTestSprite.get());
    AssetSingleton.sprBigSprite = std::make_unique<olc::Sprite>("../res/gfx/big.png");
    AssetSingleton.decBigDecal = std::make_unique<olc::Decal>(AssetSingleton.sprBigSprite.get());
    AssetSingleton.sprText = std::make_unique<olc::Sprite>("../res/gfx/uj font 1.png");
    AssetSingleton.decText = std::make_unique<olc::Decal>(AssetSingleton.sprText.get());
    AssetSingleton.sprGroundSprite = std::make_unique<olc::Sprite>("../res/gfx/ground.png");
    AssetSingleton.decGroundDecal = std::make_unique<olc::Decal>(AssetSingleton.sprGroundSprite.get());
    AssetSingleton.sprNorthEastSprite = std::make_unique<olc::Sprite>("../res/gfx/northwest.png");
    AssetSingleton.decNorthEastDecal = std::make_unique<olc::Decal>(AssetSingleton.sprNorthEastSprite.get());
    AssetSingleton.sprNorthWestSprite = std::make_unique<olc::Sprite>("../res/gfx/northeast.png");
    AssetSingleton.decNorthWestDecal = std::make_unique<olc::Decal>(AssetSingleton.sprNorthWestSprite.get());
    AssetSingleton.decFont = std::make_unique<olc::Decal>(GetFontSprite());

    m_game_state = PLAY;
    //m_arena(this);
    m_arena->LoadArena(this);
	/*entities.push_back(std::make_unique<Entity>(olc::vf2d(2.0f, 2.0f)));
    entities.push_back(std::make_unique<Entity>(olc::vf2d(1000.0f, 1000.0f)));
    entities.push_back(std::make_unique<Entity>(olc::vf2d(5.0f, 77.0f)));*/

    //This part can be made into a load_cutscene_objects function.
    /*cutscene.m_involved_actors["dave"] = entities[0].get(); //DANGLING POINTERS IN THE VECTORS!!!!!!! FIX ASAP!!!!!
    cutscene.m_involved_actors["me"] = entities[1].get(); //DANGLING POINTERS IN THE VECTORS!!!!!!! FIX ASAP!!!!!

    camera.m_camera_state = FOLLOW;
    camera.target = entities[0].get();*/

	return true;
}

bool
Program::OnUserUpdate(float fElapsedTime)
{	
    
    Clear(olc::DARK_BLUE);
    SetPixelMode(olc::Pixel::NORMAL);
    switch(m_game_state){
        case CUTSCENE:
            cutscene.RunCutscene(this);
            break;
        case PLAY:
            m_arena->RunArena(this, fElapsedTime);
            break;
        case PAUSE:
            break;
        case LOBBY:
            break;
    }
    SetPixelMode(olc::Pixel::NORMAL);
	return true;
}