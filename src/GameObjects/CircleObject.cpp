#include "CircleObject.h"

CircleObject::CircleObject() : GameObject()
{}

CircleObject::CircleObject(float x, float y, float dx, float dy, float radius, float numSegments) :
    GameObject(x, y, dx, dy, radius, numSegments)
{}

CircleObject::CircleObject(const QVector2D& center, const QVector2D& speed, float radius, float numSegments) :
    GameObject(center, speed, radius, numSegments)
{}

QVector2D* const CircleObject::getVertexArray()
{
    for(int i = 0; i < _numSegments; ++i)
    {
        float theta = 2.0f * PI * float(i) / float(_numSegments);
        float x = _radius * cos(theta);
        float y = _radius * sin(theta);

        _vertexes.emplace_back(x, y);
    }

    return _vertexes.data();
}

int CircleObject::getVertexArrayByteSize()
{
    return _numSegments * 2 * sizeof(float);
}
