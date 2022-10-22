#ifndef Physics_H
#define Physics_H

#include "Configuration.h"
#include "../GameObjects/CircleObject.h"


class Physics
{
public:
    Physics(CircleObject& userBat, CircleObject& aiBat, CircleObject& puck);

    void calulatePhysics();

private:
    CircleObject& _userBat;
    CircleObject& _aiBat;
    CircleObject& _puck;

    void checkUserInput();
};


#endif // Physics_H
