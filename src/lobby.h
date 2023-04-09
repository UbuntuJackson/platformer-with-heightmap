#include <vector>
#include "entity.h"

class Lobby{
    std::vector<std::unique_ptr<Entity>> m_lobby_entities; //This will contain the entities specific to the arena.
                                                            //They will have the same lifetime as the arena, and I thought
                                                            //that seems easier to keep track of than if they were still
                                                            //accessible from for example the game start menu. That'd be weird
                                                            //wouldn't it?
    Lobby();
    void LoadLobby();

};