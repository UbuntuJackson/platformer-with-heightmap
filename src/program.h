
#ifndef PROGRAM
#define PROGRAM

#include <string>
#include "entity.h"
#include "../include/olcPixelGameEngine.h"
#include "camera.h"
#include "assets.h"
#include "cutscenes.h"

enum GameState{
	PLAY,
	PAUSE,
	CUTSCENE,
	LOBBY
};

class Arena;

class Program : public olc::PixelGameEngine
{
public:

	std::map<std::string,int> m_key_config_1;
	std::map<std::string,int> m_key_config_2;

	int m_game_state;
	Arena *m_arena;
	std::vector<std::unique_ptr<Entity>> entities;
	Assets AssetSingleton;
	Camera camera;
	TestCutscene cutscene;
	Program();

	bool
    OnUserCreate();

	bool
    OnUserUpdate(float fElapsedTime);
};
#endif


