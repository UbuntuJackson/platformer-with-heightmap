
#ifndef ASSETS
#define ASSETS
#include "../include/olcPixelGameEngine.h"

class Assets{
public:
    std::unique_ptr<olc::Sprite> sprTestSprite;
    std::unique_ptr<olc::Decal> decTestDecal;
    std::unique_ptr<olc::Sprite> sprBigSprite;
    std::unique_ptr<olc::Decal> decBigDecal;
    std::unique_ptr<olc::Sprite> sprGroundSprite;
    std::unique_ptr<olc::Decal> decGroundDecal;
    std::unique_ptr<olc::Sprite> sprNorthEastSprite;
    std::unique_ptr<olc::Decal> decNorthEastDecal;
    std::unique_ptr<olc::Sprite> sprNorthWestSprite;
    std::unique_ptr<olc::Decal> decNorthWestDecal;
    std::unique_ptr<olc::Sprite> sprText;
    std::unique_ptr<olc::Decal> decText;
    std::unique_ptr<olc::Decal> decFont;
    Assets();
};

#endif