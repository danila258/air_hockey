#ifndef GAMERULES_H
#define GAMERULES_H

#include "../GameObjects/GameObject.h"


class GameRules
{
public:
    GameRules() = delete;
    GameRules(GameObject& userBat, GameObject& aiBat, GameObject& puck);

    void applyGameRules();

private:
    GameObject& _userBat;
    GameObject& _aiBat;
    GameObject& _puck;
};


#endif // GAMERULES_H
