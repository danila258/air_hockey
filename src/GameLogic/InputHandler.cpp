#include "InputHandler.h"

InputHandler::InputHandler(CircleObject& userBat, CircleObject& puck, float width, float height)
    : _userBat(userBat), _puck(puck), _width(width), _height(height)
{}

void InputHandler::mouseMoveEvent(QMouseEvent* event, float width, float height)
{
    _width = width;
    _height = height;

    if (!_clickFlag)
    {
        return;
    }

    QVector2D position( event->position().rx(), event->position().ry() );
    _touchVertexes.push_back( {getGlCoordinates(position), true} );
}

void InputHandler::mousePressEvent(QMouseEvent* event, float width, float height)
{
    _width = width;
    _height = height;

    QVector2D position( event->position().rx(), event->position().ry() );
    position = getGlCoordinates(position);

    if (!(_userBat.getX() - _userBat.getRadius() <= position.x() &&
          position.x() <= _userBat.getX() + _userBat.getRadius() &&
          _userBat.getY() - _userBat.getRadius() <= position.y() &&
          position.y() <= _userBat.getY() + _userBat.getRadius()))
    {
        return;
    }

    if (event->button() == Qt::LeftButton)
    {
        _touchVertexes.push_back({{position.x(), position.y()}, true});
        _clickFlag = true;
    }
}

void InputHandler::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        _clickFlag = false;
        _touchVertexes.clear();
    }
}

void InputHandler::updateUserBatPosition()
{
    if (_touchVertexes.length() == 0)
    {
        return;
    }

    QVector2D nextPosition = _touchVertexes.first().first;
    QVector2D motionVector = nextPosition - _userBat.getCenter();

    if ( detectPuckOnTrajectory(motionVector) )
    {
        return;
    }

    if (_touchVertexes.first().second)
    {
        _userBat.setSpeed(nextPosition - _userBat.getCenter());
        _touchVertexes.first().second = false;
    }

    if (motionVector.length() < _userBat.getRadius() * 2.0f + PUCK_RADIUS - 0.1f * PUCK_RADIUS)
    {
        _userBat.setCenter(nextPosition);
        _touchVertexes.pop_front();
    }
    else
    {
        _userBat.changeCenter( motionVector * (_userBat.getRadius() / motionVector.length()) );
    }
}

bool InputHandler::detectPuckOnTrajectory(const QVector2D& motionVector)
{
    if (_puck.getCenter().distanceToLine(motionVector, _userBat.getCenter()) > _userBat.getRadius())
    {
        return false;
    }

    // два случая и еще разные направления

    return true;
}

QVector2D InputHandler::getGlCoordinates(const QVector2D& vertex) const
{
    return {(vertex.x() - _width / 2) / (_width / 2), - (vertex.y() - _height / 2) / (_height / 2)};
}
