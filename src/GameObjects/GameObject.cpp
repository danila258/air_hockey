#include "GameObject.h"

GameObject::GameObject() : _center(ZERO, ZERO), _speed(ZERO, ZERO), _radius(0.5), _numSegments(4.0f),
    _color(1.0f, 1.0f, 1.0f), _userControllFlag(true), _translateVector(_center)
{}

GameObject::GameObject(float x, float y, float dx, float dy, float radius, float numSegments, const QVector3D& color,
                       bool controlledFlag)
    : _center(x, y), _speed(dx, dy), _radius(radius), _numSegments(numSegments), _color(color),
      _userControllFlag(controlledFlag), _translateVector(_center)
{}

GameObject::GameObject(const QVector2D& center, const QVector2D& speed, float radius, float numSegments,
                       const QVector3D& color, bool controlledFlag)
    : _center(center), _speed(speed), _radius(radius), _numSegments(numSegments), _color(color),
      _userControllFlag(controlledFlag), _translateVector(_center)
{}

GameObject::~GameObject()
{
    for (auto&& item : _sceneObjects)
    {
        delete item;
    }
}

void GameObject::resetDifVector()
{
    _center -= _translateVector;
    _translateVector = {ZERO, ZERO};
}

const QVector2D& GameObject::getCenter() const
{
    return _center;
}

float GameObject::getX() const
{
    return _center.x();
}
float GameObject::getY() const
{
    return _center.y();
}

float GameObject::getRadius() const
{
    return _radius;
}

int GameObject::getNumSegments() const
{
    return _numSegments;
}

const QVector2D& GameObject::getSpeed() const
{
    return _speed;
}

bool GameObject::getUserControlFlag() const
{
    return _userControllFlag;
}

void GameObject::setCenter(float x, float y)
{
    setCenter({x, y});
}

void GameObject::setCenter(const QVector2D& center)
{
    _translateFlag = true;
    _translateVector += center - _center;

    _center = center;
}

void GameObject::setSpeed(const QVector2D& speed)
{
    _speed = speed;
}

void GameObject::setSpeed(float x, float y)
{
    setSpeed({x, y});
}

void GameObject::setSpeedX(float x)
{
    _speed[0] = x;
}

void GameObject::setSpeedY(float y)
{
    _speed[1] = y;
}

void GameObject::changeCenter(const QVector2D& center)
{
    _translateFlag = true;
    _translateVector += center;

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

void GameObject::regularTransformations()
{
    if (_userControllFlag)
    {
        if ( !_translateFlag )
        {
            _translateVector = {ZERO, ZERO};
        }
    }
    else
    {
        if ( !_translateFlag )
        {
            _center += _speed;
            _translateVector = _speed;
        }
    }
}
