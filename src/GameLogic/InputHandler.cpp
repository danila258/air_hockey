#include "InputHandler.h"

InputHandler::InputHandler(Bat& userBat, Bat& puck, float width, float height)
    : _userBat(userBat), _puck(puck), _width(width), _height(height), _lastPosition( userBat.getCenter() )
{}

QVector2D InputHandler::getGlCoordinates(const QVector2D& vertex) const
{
    return {(vertex.x() - _width / 2) / (_width / 2), - (vertex.y() - _height / 2) / (_height / 2)};
}

void InputHandler::mouseMoveEvent(QMouseEvent* event, float width, float height)
{
    _width = width;
    _height = height;

    if ( !_clickFlag )
    {
        return;
    }

    QVector2D position( event->position().rx(), event->position().ry() );
    position = getGlCoordinates(position);

    _userBat.setCenter(position);
    _userBat.setSpeed((position - _lastPosition) / float(USER_INPUT_FACTOR));

    _lastSpeed = (position - _lastPosition) / USER_INPUT_FACTOR;
    _lastPosition = position;
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
        _lastPosition = {position.x(), position.y()};
        _clickFlag = true;
    }
}

void InputHandler::mouseReleaseEvent(QMouseEvent* event, float width, float height)
{
    if (event->button() == Qt::LeftButton)
    {
        _clickFlag = false;
    }
}

void InputHandler::updateUserBatPosition()
{
    _userBat.setCenter(_lastPosition);
    _userBat.setSpeed(_lastSpeed);
}


