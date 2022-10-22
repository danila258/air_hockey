#include "GameObject.h"

GameObject::GameObject() : _center(ZERO, ZERO), _difVector(_center), _speed(ZERO, ZERO), _radius(0.5), _numSegments(4)
{}

GameObject::GameObject(float x, float y, float dx, float dy, float radius, float numSegments)
    : _center(x, y), _difVector(_center), _speed(dx, dy), _radius(radius), _numSegments(numSegments)
{}

GameObject::GameObject(const QVector2D& center, const QVector2D& speed, float radius,  float numSegments)
    : _center(center), _difVector(_center), _speed(speed), _radius(radius), _numSegments(numSegments)
{}

const QMatrix4x4& GameObject::getTransform()
{
    if (_translateFlag)
    {
        qDebug() << "translate" << _center << _difVector;

        _transform.translate(_difVector.x(), _difVector.y());
        _translateFlag = false;
        _difVector = {ZERO, ZERO};
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

const float GameObject::getX()
{
    return _center.x();
}
const float GameObject::getY()
{
    return _center.y();
}

float GameObject::getRadius()
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

void GameObject::resetDifVector()
{
    _center -= _difVector;
    _difVector = {ZERO, ZERO};
}

void GameObject::setCenter(float x, float y)
{
    setCenter({x, y});
}

void GameObject::setCenter(const QVector2D& center)
{
    _translateFlag = true;
    _difVector += center - _center;

    _center = center;
}

void GameObject::setSpeed(const QVector2D& speed)
{
    _speed = speed;
}

void GameObject::changeCenter(const QVector2D& center)
{
    _translateFlag = true;
    _difVector += center;

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
