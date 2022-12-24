#include "Bat.h"

Bat::Bat() : CircleObject()
{
    setupSceneObjects();
}

Bat::Bat(float x, float y, float dx, float dy, float radius, float numSegments, const QVector3D& color,
         bool controlledFlag) : CircleObject(x, y, dx, dy, radius, numSegments, color, controlledFlag)
{
    setupSceneObjects();
}

Bat::Bat(const QVector2D& center, const QVector2D& speed, float radius, float numSegments, const QVector3D& color,
         bool controlledFlag) : CircleObject(center, speed, radius, numSegments, color, controlledFlag)
{
    setupSceneObjects();
}

void Bat::setupSceneObjects()
{
    _sceneObjects.push_back(new Circle(ZERO, ZERO, _radius * 0.5f, ZERO, 1.0f, _numSegments, _color));
    _sceneObjects.push_back(new Ring(ZERO, ZERO, _radius, _radius * 0.75f, ZERO, 1.0f,
                                     _numSegments, _color));
}
