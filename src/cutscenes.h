#ifndef CUTSCENES
#define CUTSCENES

#include <map>
#include <string>
#include "entity.h"

enum CutsceneStates{
    ENTRY,
    ENDING_DIALOGUE,
    DAVE_SPEAKS_ABOUT_BASEBALL,
    I_SPEAK,
    ZOOMS_IN_ON_DAVE,
    BOOGIDYBOOGIDYBOO
    
};

class TestCutscene{
public:
    int m_cutscene_step;
    bool next_button_pressed;
    std::map<std::string, Entity*> m_involved_actors;
    TestCutscene();
    void RunCutscene(Program *program);
};
#endif