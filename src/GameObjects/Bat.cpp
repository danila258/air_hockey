#include "Bat.h"

Bat::Bat() : GameObject()
{
    setupSceneObjects();
}

Bat::Bat(float x, float y, float dx, float dy, float radius, float numSegments, bool controlledFlag) :
    GameObject(x, y, dx, dy, radius, numSegments, controlledFlag)
{
    setupSceneObjects();
}

Bat::Bat(const QVector2D& center, const QVector2D& speed, float radius, float numSegments,
                           bool controlledFlag) :
    GameObject(center, speed, radius, numSegments, controlledFlag)
{
    setupSceneObjects();
}

void Bat::create()
{
    for (auto&& item : _sceneObjects)
    {
        item->create();
    }
}

void Bat::render()
{
    regularTransformations();
    customTransformations();

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

void Bat::setupSceneObjects()
{
    _sceneObjects.push_back( new Circle({ZERO, ZERO}, _radius, _numSegments, ZERO, 1.0f) );
}

void Bat::customTransformations()
{
    //...
}