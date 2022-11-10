#include "SceneObject.h"

SceneObject::SceneObject() : _center(ZERO, ZERO), _width(0.5f), _height(0.5f), _radius(0.25f), _numSegments(4)
{}

SceneObject::SceneObject(float x, float y, float width, float height, float radius, float numSegments)
    : _center(x, y), _width(width), _height(height), _radius(radius), _numSegments(numSegments)
{}

SceneObject::SceneObject(const QVector2D& center, const QVector2D& dimension, float radius,  float numSegments)
    : _center(center), _width(dimension.x()), _height(dimension.y()), _radius(radius), _numSegments(numSegments)
{}

void SceneObject::setupRenderObject()
{
    setVertexArray();
    setVertexArrayByteSize();
}
