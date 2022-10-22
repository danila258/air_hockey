#include "Physics.h"

Physics::Physics(CircleObject& userBat, CircleObject& aiBat, CircleObject& puck)
    : _userBat(userBat), _aiBat(aiBat), _puck(puck)
{}

void Physics::calulatePhysics()
{
    checkUserInput();
}

void Physics::checkUserInput()
{
    QVector2D newCenter = _userBat.getCenter();

    if (_userBat.getX() + _userBat.getRadius() > MAX_X)
    {
        newCenter[0] = MAX_X - _userBat.getRadius();
    }

    if (_userBat.getX() - _userBat.getRadius() < MIN_X)
    {
        newCenter[0] = MIN_X + _userBat.getRadius();
    }

    if (_userBat.getY() + _userBat.getRadius() > MAX_Y)
    {
        newCenter[1] = MAX_Y - _userBat.getRadius();
    }

    if (_userBat.getY() - _userBat.getRadius() < MIN_Y)
    {
        newCenter[1] = MIN_Y + _userBat.getRadius();
    }

    if (newCenter != _userBat.getCenter())
    {
        _userBat.resetDifVector();
        _userBat.setCenter(newCenter);
    }

    qDebug() << "PH     " << newCenter;
}
