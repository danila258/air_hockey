#include "RoundedRectangle.h"

RoundedRectangle::RoundedRectangle() : ComplexObject(ZERO, ZERO, 0.5f, 0.25f), _roundingRadius(0.1f),
    _roundingNumSegments(3)
{
    userInputCheck();
    setupSceneObjects();
}

RoundedRectangle::RoundedRectangle(float x, float y, float width, float height, float roundingRadius,
                                   float roundingNumSegments, const QVector3D& color)
    : ComplexObject(x, y, width, height, ZERO, color), _roundingRadius(roundingRadius),
      _roundingNumSegments(roundingNumSegments)
{
    userInputCheck();
    setupSceneObjects();
}

RoundedRectangle::RoundedRectangle(const QVector2D& center, const QVector2D& dimension, float roundingRadius,
                                   float roundingNumSegments, const QVector3D& color)
    : ComplexObject(center, dimension, ZERO, color), _roundingRadius(roundingRadius),
      _roundingNumSegments(roundingNumSegments)
{
    userInputCheck();
    setupSceneObjects();
}

void RoundedRectangle::userInputCheck()
{
    if (_roundingRadius > width() / 2.0f || _roundingRadius > height() / 2.0f || width() < ZERO ||  height() < ZERO ||
        _roundingNumSegments < 2)
    {
        throw std::logic_error("incorrectly passed data to the constructor of rounded rectangle");
    }
}

void RoundedRectangle::setupSceneObjects()
{
    Circle* rightTopCircle = new Circle(x() + width() / 2.0f - _roundingRadius,
                                        y() + height() / 2.0f - _roundingRadius,
                                        _roundingRadius,
                                        ZERO,
                                        0.25f,
                                        _roundingNumSegments,
                                        _color);

    Circle* leftTopCircle = new Circle(x() + _roundingRadius - width() / 2.0f,
                                       y() + height() / 2.0f - _roundingRadius,
                                       _roundingRadius,
                                       90.0f,
                                       0.25f,
                                       _roundingNumSegments,
                                       _color);

    Circle* leftBottomCircle = new Circle(x() + _roundingRadius - width() / 2.0f,
                                          y() + _roundingRadius - height() / 2.0f,
                                          _roundingRadius,
                                          180.0f,
                                          0.25f,
                                          _roundingNumSegments,
                                          _color);

    Circle* rightBottomCircle = new Circle(x() + width() / 2.0f - _roundingRadius,
                                           y() + _roundingRadius - height() / 2.0f,
                                           _roundingRadius,
                                           270.0f,
                                           0.25f,
                                           _roundingNumSegments,
                                           _color);

    _sceneObjects.push_back(rightTopCircle);
    _sceneObjects.push_back(leftTopCircle);
    _sceneObjects.push_back(leftBottomCircle);
    _sceneObjects.push_back(rightBottomCircle);

    Rectangle* topRectangle = new Rectangle(x(),
                                            y() + height() / 2.0f - _roundingRadius / 2.0f,
                                            width() - 2 * _roundingRadius,
                                            _roundingRadius,
                                            _color);

    Rectangle* middleRectangle = new Rectangle(_center.x(), _center.y(), width(), height() - 2.0f * _roundingRadius,
                                               _color);

    Rectangle* bottomRectangle = new Rectangle(x(),
                                               y() - height() / 2.0f + _roundingRadius / 2.0f,
                                               width() - 2 * _roundingRadius,
                                               _roundingRadius,
                                               _color);

    _sceneObjects.push_back(topRectangle);
    _sceneObjects.push_back(middleRectangle);
    _sceneObjects.push_back(bottomRectangle);
}
