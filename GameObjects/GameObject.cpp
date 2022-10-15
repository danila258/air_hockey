#include "GameObject.h"

GameObject::GameObject() : _centre(0.0, 0.0), _speed(0.0, 0.0), _radius(0.5), _numSegments(4)
{}

GameObject::GameObject(float x, float y, float dx, float dy, float radius, float numSegments)
    : _centre(x, y), _speed(dx, dy), _radius(radius), _numSegments(numSegments)
{}

GameObject::GameObject(const Vertex<float>& center, const QVector2D speed, float radius,  float numSegments)
    : _centre(center), _speed(speed), _radius(radius), _numSegments(numSegments)
{}

const int GameObject::getX()
{
    return _centre._x;
}
const int GameObject::getY()
{
    return _centre._y;
}
const Vertex<float>& GameObject::getCentre()
{
    return _centre;
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

void GameObject::setCentre(float x, float y)
{
    setCentre({x, y});
}

void GameObject::setCentre(const Vertex<float>& centre)
{
    _centre = centre;
}

void GameObject::setSpeed(const QVector2D& speed)
{
    _speed = speed;
}

void GameObject::moveCentreBy(float x, float y)
{
    _centre += {x, y};
}

void GameObject::changeSpeedBy(float x, float y)
{
    _speed += {x, y};
}
