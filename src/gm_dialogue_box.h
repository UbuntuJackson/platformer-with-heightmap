#include <string>
#include "../include/olcPixelGameEngine.h"
#include "program.h"

class DialogueBox{
    std::map<char, int> letter_width_table {
        {' ', 5},
        {'!', 5},
        {'#', 5},
        {'$', 5},
        {'%', 5},
        {'&', 5},
        {'\'', 5},
        {'(', 5},
        {')', 5},
        {'*', 5},
        {'+', 5},
        {',', 5},
        {'-', 5},
        {'.', 5},
        {'/', 5},
        {'0', 5},
        {'1', 5},
        {'2', 5},
        {'3', 5},
        {'4', 5},
        {'5', 5},
        {'6', 5},
        {'7', 5},
        {'8', 5},
        {'9', 5},
        {':', 5},
        {';', 5},
        {'<', 5},
        {'=', 5},
        {'?', 5},
        {'@', 5},
        {'A', 5},
        {'B', 5},
        {'C', 5},
        {'D', 5},
        {'E', 5},
        {'F', 5},
        {'G', 5},
        {'H', 5},
        {'I', 5},
        {'J', 5},
        {'K', 5},
        {'L', 5},
        {'M', 5},
        {'N', 5},
        {'O', 5},
        {'P', 5},
        {'Q', 5},
        {'R', 5},
        {'S', 5},
        {'T', 5},
        {'U', 5},
        {'V', 5},
        {'W', 5},
        {'X', 5},
        {'Y', 5},
        {'Z', 5},
        {'a', 5},
        {'b', 5},
        {'c', 5},
        {'d', 5},
        {'e', 5},
        {'f', 5},
        {'g', 5},
        {'h', 5}
    };

    std::string m_text;
    std::vector<std::string> m_lines; //vector with strings.
    olc::vf2d pos;
    olc::vf2d size;
    DialogueBox();
    void
    DrawBox(); //Text will be drawn
    void
    SeparateText();
    //temp_str = ""
    //foreach char in m_text: temp_str += char, text_width += char.width,
    //  if text_width > allowed_width: m_text_strings.push(temp_str), temp_str = ""
    //
    void
    DrawText();
    //foreach line_index in m_text_strings: DrawString(x, y + general_char_height * line_index)
};

void
DialogueBox::SeparateText(){
    std::string temp_str = "";
    int text_width = 0;
    for(int ch_index = 0; ch_index < temp_str.size(); ch_index++){
        temp_str += m_text[ch_index];
        //text_width += char.width //char shenanigans
        
        if(text_width > size.x){
            m_lines.push_back(temp_str); //copy
        }
    }
}

void
DrawText(Program *program){
    for(int ln_index = 0; ln_index < m_lines.size(); ln_index++){
        //program->DrawStringDecal();
    }
}