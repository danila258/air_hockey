#include "SceneObject.h"

SceneObject::SceneObject() : _center(ZERO, ZERO), _dimension(0.5f, 0.5f), _radius(0.25f)
{}

SceneObject::SceneObject(float x, float y, float width, float height, float radius)
    : _center(x, y), _dimension(height, width), _radius(radius)
{}

SceneObject::SceneObject(const QVector2D& center, const QVector2D& dimension, float radius)
    : _center(center), _dimension(dimension), _radius(radius)
{}

const QVector2D& SceneObject::center() const
{
    return _center;
}

float SceneObject::x() const
{
    return _center.x();
}

float SceneObject::y() const
{
    return _center.y();
}

const QVector2D& SceneObject::dimension() const
{
    return _dimension;
}

float SceneObject::width() const
{
    return _dimension.x();
}

float SceneObject::height() const
{
    return _dimension.y();
}

float SceneObject::radius() const
{
    return _radius;
}
