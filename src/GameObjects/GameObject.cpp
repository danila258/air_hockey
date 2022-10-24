#include "GameObject.h"

GameObject::GameObject() : _center(ZERO, ZERO), _difVector(_center), _speed(ZERO, ZERO), _radius(0.5), _numSegments(4),
    _controlledFlag(true)
{}

GameObject::GameObject(float x, float y, float dx, float dy, float radius, float numSegments, bool controlledFlag)
    : _center(x, y), _difVector(_center), _speed(dx, dy), _radius(radius), _numSegments(numSegments),
      _controlledFlag(controlledFlag)
{}

GameObject::GameObject(const QVector2D& center, const QVector2D& speed, float radius, float numSegments,
                       bool controlledFlag)
    : _center(center), _difVector(_center), _speed(speed), _radius(radius), _numSegments(numSegments),
      _controlledFlag(controlledFlag)
{}

GameObject::~GameObject()
{
   destroy();
}

void GameObject::destroy()
{
    _vao.destroy();
    _vbo.destroy();
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
    if (_controlledFlag)
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
            qDebug() << "translate and center = " << _center;
            _transform.translate(_difVector.x(), _difVector.y());

            _translateFlag = false;
            _difVector = {ZERO, ZERO};
        }
        else
        {
            qDebug() << "use speed = " << _speed;
            _center += _speed;
            _transform.translate(_speed.x(), _speed.y());
        }       
    }

    return _transform;
}
