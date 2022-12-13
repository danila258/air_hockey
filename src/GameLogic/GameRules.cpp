#include "GameRules.h"

GameRules::GameRules(GameObject& userBat, GameObject& aiBat, GameObject& puck)
    : _userBat(userBat), _aiBat(aiBat), _puck(puck)
{}

void GameRules::applyGameRules()
{
    if (_userBat.getY() + _userBat.getRadius() > ZERO)
    {
        _userBat.setCenter(_userBat.getX(), ZERO - _userBat.getRadius());
    }

    if (_aiBat.getY() + _aiBat.getRadius() < ZERO)
    {
        _aiBat.setCenter(_aiBat.getX(), ZERO + _aiBat.getRadius());
    }

    if (std::abs( _puck.getY() ) >= 1.0f)
    {
        _puck.setSpeed(ZERO, ZERO);
        _puck.setCenter(ZERO, ZERO);
    }
}
