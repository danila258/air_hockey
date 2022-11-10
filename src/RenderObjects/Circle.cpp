#include "Circle.h"

Circle::Circle() : SceneObject(), _rotationAngle(ZERO), _fractionOfCircle(1.0f)
{}

Circle::Circle(float x, float y, float radius, float numSegments, float rotationAngle, float fractionOfCircle)
     : SceneObject(x, y, radius * 2.0f, radius * 2.0f, radius, numSegments), _rotationAngle(rotationAngle),
       _fractionOfCircle(fractionOfCircle)
{
    setupRenderObject();
}

Circle::Circle(const QVector2D& center, float radius, float numSegments, float rotationAngle, float fractionOfCircle)
     : SceneObject(center, {radius * 2.0f, radius * 2.0f}, radius, numSegments), _rotationAngle(rotationAngle),
       _fractionOfCircle(fractionOfCircle)
{
    setupRenderObject();
}

void Circle::setVertexArray()
{
    for(int i = 0; i < _numSegments; ++i)
    {
        float theta = (_rotationAngle / 180.0f) * PI + _fractionOfCircle * PI * float(i) / float(_numSegments);
        float x = _radius * cos(theta);
        float y = _radius * sin(theta);

        _vertexArray.emplace_back(x, y);
    }
}

void Circle::setVertexArrayByteSize()
{
    _vertexArrayByteSize = _numSegments * 2 * sizeof(float);
}
