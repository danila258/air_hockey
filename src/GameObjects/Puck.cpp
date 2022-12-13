#include "Puck.h"

Puck::Puck() : CircleObject()
{
    setupSceneObjects();
}

Puck::Puck(float x, float y, float dx, float dy, float radius, float numSegments, const QVector3D& color,
         bool controlledFlag) : CircleObject(x, y, dx, dy, radius, numSegments, color, controlledFlag)
{
    setupSceneObjects();
}

Puck::Puck(const QVector2D& center, const QVector2D& speed, float radius, float numSegments, const QVector3D& color,
         bool controlledFlag) : CircleObject(center, speed, radius, numSegments, color, controlledFlag)
{
    setupSceneObjects();
}

void Puck::setupSceneObjects()
{
    _sceneObjects.push_back(new Circle(ZERO, ZERO, _radius, ZERO, 1.0f, _numSegments, _color));
}
