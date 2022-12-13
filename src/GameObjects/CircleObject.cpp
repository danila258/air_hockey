#include "CircleObject.h"

CircleObject::CircleObject() : GameObject()
{}

CircleObject::CircleObject(float x, float y, float dx, float dy, float radius, float numSegments,
                           const QVector3D& color, bool controlledFlag)
    : GameObject(x, y, dx, dy, radius, numSegments, color, controlledFlag)
{}

CircleObject::CircleObject(const QVector2D& center, const QVector2D& speed, float radius, float numSegments,
                           const QVector3D& color, bool controlledFlag)
    : GameObject(center, speed, radius, numSegments, color, controlledFlag)
{}

void CircleObject::create()
{
    for (auto&& item : _sceneObjects)
    {
        item->create();
    }
}

void CircleObject::render()
{
    regularTransformations();

    for (auto&& item : _sceneObjects)
    {
        item->translate(_translateVector);
        item->render();
    }

    if (_translateFlag)
    {
        _translateVector = {ZERO, ZERO};
        _translateFlag = false;
    }
    else if (!_userControllFlag && _translateVector == _speed)
    {
        _translateVector = {ZERO, ZERO};
    }
}
