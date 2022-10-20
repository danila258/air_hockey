#include "GameObject.h"

GameObject::GameObject() : _center(0.0, 0.0), _difCenter(_center), _speed(0.0, 0.0), _radius(0.5), _numSegments(4)
{}

GameObject::GameObject(float x, float y, float dx, float dy, float radius, float numSegments)
    : _center(x, y), _difCenter(_center), _speed(dx, dy), _radius(radius), _numSegments(numSegments)
{}

GameObject::GameObject(const QVector2D& center, const QVector2D& speed, float radius,  float numSegments)
    : _center(center), _difCenter(_center), _speed(speed), _radius(radius), _numSegments(numSegments)
{}

const QMatrix4x4& GameObject::getTransform()
{
    if (_translateFlag)
    {
        _transform.translate(_difCenter.x(), _difCenter.y());
        _translateFlag = false;
    }
    else
    {
        _transform.translate(_speed.x(), _speed.y());
    }


    return _transform;
}

const QVector2D& GameObject::getCenter()
{
    return _center;
}

const int GameObject::getX()
{
    return _center.x();
}
const int GameObject::getY()
{
    return _center.y();
}

int GameObject::getRadius()
{
    return _radius;
}

int GameObject::getNumSegments()
{
    return _numSegments;
}

const QVector2D& GameObject::getSpeed()
{
    return _speed;
}

void GameObject::setCenter(float x, float y)
{
    setCenter({x, y});
}

void GameObject::setCenter(const QVector2D& center)
{
    _translateFlag = true;
    _difCenter = center - _center;

    _center = center;
}

void GameObject::setSpeed(const QVector2D& speed)
{
    _speed = speed;
}

void GameObject::changeCenter(const QVector2D& center)
{
    _translateFlag = true;
    _difCenter = center;

    _center += center;
}

void GameObject::changeCenter(float x, float y)
{
    changeCenter({x, y});
}

void GameObject::changeSpeed(const QVector2D& speed)
{
    _speed += speed;
}

void GameObject::changeSpeed(float x, float y)
{
    changeSpeed({x, y});
}
