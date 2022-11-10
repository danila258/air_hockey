#include "GameObject.h"

GameObject::GameObject() : RenderObject(), _center(ZERO, ZERO), _difVector(_center), _speed(ZERO, ZERO), _radius(0.5),
    _numSegments(4.0f), _userControllFlag(true)
{}

GameObject::GameObject(float x, float y, float dx, float dy, float radius, float numSegments, bool controlledFlag)
    : RenderObject(), _center(x, y), _difVector(_center), _speed(dx, dy), _radius(radius), _numSegments(numSegments),
      _userControllFlag(controlledFlag)
{}

GameObject::GameObject(const QVector2D& center, const QVector2D& speed, float radius, float numSegments,
                       bool controlledFlag)
    : RenderObject(), _center(center), _difVector(_center), _speed(speed), _radius(radius), _numSegments(numSegments),
      _userControllFlag(controlledFlag)
{}

GameObject::~GameObject()
{
   destroy();
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

void GameObject::setSpeed(float x, float y)
{
    _speed = {x, y};
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

const QMatrix4x4& GameObject::getTransform()
{
    if (_userControllFlag)
    {
        if (_translateFlag)
        {
            _transform.translate(_difVector.x(), _difVector.y());

            _translateFlag = false;
            _difVector = {ZERO, ZERO};
        }
        else
        {
            _transform.translate(ZERO, ZERO);
        }
    }
    else
    {
        if (_translateFlag)
        {
            _transform.translate(_difVector.x(), _difVector.y());
            _translateFlag = false;

            _difVector = {ZERO, ZERO};
        }
        else
        {
            _center += _speed;
            _transform.translate(_speed.x(), _speed.y());
        }       
    }

    return _transform;
}
