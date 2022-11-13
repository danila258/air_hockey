#include "Circle.h"

Circle::Circle() : RenderObject(), _rotationAngle(ZERO), _fractionOfCircle(1.0f), _numSegments(7)
{
    setupRenderObject();
}

Circle::Circle(float x, float y, float radius, int numSegments, float rotationAngle, float fractionOfCircle)
     : RenderObject(x, y, radius * 2.0f, radius * 2.0f, radius), _numSegments(numSegments),
       _rotationAngle(rotationAngle), _fractionOfCircle(fractionOfCircle)
{
    setupRenderObject();
}

Circle::Circle(const QVector2D& center, float radius, int numSegments, float rotationAngle, float fractionOfCircle)
     : RenderObject(center, {radius * 2.0f, radius * 2.0f}, radius), _numSegments(numSegments),
       _rotationAngle(rotationAngle), _fractionOfCircle(fractionOfCircle)
{
    setupRenderObject();
}

void Circle::setVertexArray()
{
    for (int i = 0; i < _numSegments; ++i)
    {
        float theta = (_rotationAngle / 180.0f) * PI + _fractionOfCircle * 2 * PI * float(i) / float(_numSegments);
        float x = _radius * cos(theta) + _center.x();
        float y = _radius * sin(theta) + _center.y();

        _vertexArray.emplace_back(x, y);
    }
}

void Circle::setVertexArrayByteSize()
{
    _vertexArrayByteSize = _numSegments * 2 * sizeof(float);
}
