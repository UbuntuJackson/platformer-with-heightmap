#include "cutscenes.h"
#include "camera.h"
#include "program.h"
#include "../include/olcPixelGameEngine.h"
TestCutscene::TestCutscene(){
    m_cutscene_step = ENTRY;
}

void
TestCutscene::RunCutscene(Program *program){

    switch(m_cutscene_step){
        case ENTRY:
            
            
            m_cutscene_step = 101;
            program->camera.target = m_involved_actors["dave"];
            program->camera.SetStateZoom(5.0f);
            break;
        case 101:
            
            if(program->GetKey(olc::Key::SPACE).bPressed){
                m_cutscene_step = 102;
                program->camera.SetStateZoom(0.1f);
            }
            break;
        case 102:
            if(program->GetKey(olc::Key::SPACE).bPressed){
                m_cutscene_step = 103;
                program->camera.SetStateSwitch(m_involved_actors["me"]);
            }
            break;
        case 103:
            if(program->GetKey(olc::Key::SPACE).bPressed)
                m_cutscene_step = ENDING_DIALOGUE;
                //program->camera.SetStateSwitch(m_involved_actors["dave"]);
            break;
        case ENDING_DIALOGUE:
            program->camera.SetStateZoom(1.0f);
            //program->camera.m_camera_state = MOVE;
            program->m_game_state = PLAY;
            //break out of cutscene
            break;
        
    }

}