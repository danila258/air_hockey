#include "RoundedRectangle.h"

RoundedRectangle::RoundedRectangle() : ComplexObject(ZERO, ZERO, 0.5f, 0.25f), _roundingRadius(0.1f),
    _roundingNumSegments(3)
{
    setupSceneObjects();
}

RoundedRectangle::RoundedRectangle(float x, float y, float width, float height, float roundingRadius,
                                   float roundingNumSegments)
    : ComplexObject(x, y, width, height), _roundingRadius(roundingRadius), _roundingNumSegments(roundingNumSegments)
{
    setupSceneObjects();
}

RoundedRectangle::RoundedRectangle(const QVector2D& center, const QVector2D& dimension, float roundingRadius,
                 float roundingNumSegments)
    : ComplexObject(center, dimension), _roundingRadius(roundingRadius), _roundingNumSegments(roundingNumSegments)
{
    setupSceneObjects();
}

void RoundedRectangle::setupSceneObjects()
{
    Circle* rightTopCircle = new Circle(width() / 2.0f - _roundingRadius, height() / 2.0f - _roundingRadius,
                                        _roundingRadius, _roundingNumSegments, ZERO, 0.25f);
    Circle* leftTopCircle = new Circle(_roundingRadius - width() / 2.0f, height() / 2.0f - _roundingRadius,
                                        _roundingRadius, _roundingNumSegments, 90.0f, 0.25f);
    Circle* leftBottomCircle = new Circle(_roundingRadius - width() / 2.0f, _roundingRadius - height() / 2.0f,
                                        _roundingRadius, _roundingNumSegments, 180.0f, 0.25f);
    Circle* rightBottomCircle = new Circle(width() / 2.0f - _roundingRadius, _roundingRadius - height() / 2.0f,
                                        _roundingRadius, _roundingNumSegments, 270.0f, 0.25f);

    _sceneObjects.push_back(rightTopCircle);
    _sceneObjects.push_back(leftTopCircle);
    _sceneObjects.push_back(leftBottomCircle);
    _sceneObjects.push_back(rightBottomCircle);
}

//QVector2D* const RoundedLine::getCircleVertexArray(float rotationAngle, float fractionOfCircle)
//{
//    for(int i = 0; i < _roundingNumSegments; ++i)
//    {
//        float theta = (angle / 180.0f) * PI + shareCircle * PI * float(i) / float(_roundingNumSegments);
//        float x = _roundingRadius * cos(theta);
//        float y = _roundingRadius * sin(theta);

//        _vertexes.emplace_back(x, y);
//    }

//    return _vertexes.data();
//}

//int RoundedLine::getCircleVertexArrayByteSize() const
//{
//    return _roundingNumSegments * 2 * sizeof(float);
//}
