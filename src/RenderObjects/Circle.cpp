#include "Circle.h"

Circle::Circle() : RenderObject(), _rotationAngle(ZERO), _fractionOfCircle(1.0f), _numSegments(8)
{
    setupRenderObject();
}

Circle::Circle(float x, float y, float radius, float rotationAngle, float fractionOfCircle, int numSegments)
     : RenderObject(x, y, radius * 2.0f, radius * 2.0f, radius), _rotationAngle(rotationAngle),
       _fractionOfCircle(fractionOfCircle), _numSegments(numSegments)
{
    setupRenderObject();
}

Circle::Circle(const QVector2D& center, float radius, float rotationAngle, float fractionOfCircle, int numSegments)
     : RenderObject(center, {radius * 2.0f, radius * 2.0f}, radius), _rotationAngle(rotationAngle),
       _fractionOfCircle(fractionOfCircle), _numSegments(numSegments)
{
    setupRenderObject();
}

void Circle::userInputCheck()
{
    if (_radius < ZERO || _rotationAngle < ZERO || _fractionOfCircle <= ZERO ||
        _fractionOfCircle > 1.0f || _numSegments < 2.0f)
    {
        throw std::logic_error("incorrectly passed data to the constructor of circle");
    }
}

void Circle::setVertexArray()
{
    _vertexArray.emplace_back(_center);

    for (int i = 0; i < _numSegments; ++i)
    {
        if (i != 0 && i != 1)
        {
            _vertexArray.push_back(_center);
            _vertexArray.push_back(_vertexArray[_vertexArray.size() - 2]);
        }

        float theta = (_rotationAngle / 180.0f) * PI + _fractionOfCircle * 2 * PI * float(i) / float(_numSegments);
        float x = _radius * cos(theta) + _center.x();
        float y = _radius * sin(theta) + _center.y();

        _vertexArray.emplace_back(x, y);

        if (i == _numSegments - 1)
        {
            _vertexArray.push_back(_center);
            _vertexArray.push_back(_vertexArray[_vertexArray.size() - 2]);

            theta = (_rotationAngle / 180.0f) * PI + _fractionOfCircle * 2 * PI * float(i + 1.0f) / float(_numSegments);
            x = _radius * cos(theta) + _center.x();
            y = _radius * sin(theta) + _center.y();

            _vertexArray.emplace_back(x, y);
        }
    }
}

void Circle::setVertexArrayByteSize()
{
    _vertexArrayByteSize = _vertexArray.size() * 2 * sizeof(float);
}
