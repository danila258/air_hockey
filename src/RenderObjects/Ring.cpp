#include "Ring.h"

Ring::Ring() : RenderObject(), _bigRadius(0.5f), _smallRadius(0.3f), _rotationAngle(ZERO), _fractionOfCircle(1.0f),
               _numSegments(8)
{
    setupRenderObject();
}

Ring::Ring(float x, float y, float bigRadius, float smallRadius, float rotationAngle, float fractionOfCircle,
           int numSegments, const QVector3D& color)
    : RenderObject(x, y, bigRadius * 2.0f, bigRadius * 2.0f, bigRadius, color), _bigRadius(bigRadius),
      _smallRadius(smallRadius), _rotationAngle(rotationAngle), _fractionOfCircle(fractionOfCircle),
      _numSegments(numSegments)
{
    setupRenderObject();
}

Ring::Ring(const QVector2D& center, float bigRadius, float smallRadius, float rotationAngle, float fractionOfCircle,
           int numSegments, const QVector3D& color)
    : RenderObject(center, {bigRadius * 2.0f, bigRadius * 2.0f}, bigRadius, color), _bigRadius(bigRadius),
      _smallRadius(smallRadius), _rotationAngle(rotationAngle), _fractionOfCircle(fractionOfCircle),
      _numSegments(numSegments)
{
    setupRenderObject();
}

void Ring::userInputCheck()
{
    if (_bigRadius < ZERO || _smallRadius < ZERO || _bigRadius <= _smallRadius || _rotationAngle < ZERO ||
        _fractionOfCircle <= ZERO || _fractionOfCircle > 1.0f || _numSegments < 2.0f)
    {
        throw std::logic_error("incorrectly passed data to the constructor of ring");
    }
}

void Ring::setVertexArray()
{
    for (int i = 0; i < _numSegments; ++i)
    {
        float theta = (_rotationAngle / 180.0f) * PI + _fractionOfCircle * 2 * PI * float(i) / float(_numSegments);
        float x = _smallRadius * cos(theta) + _center.x();
        float y = _smallRadius * sin(theta) + _center.y();

        _vertexArray.emplace_back(x, y);

        x = _bigRadius * cos(theta) + _center.x();
        y = _bigRadius * sin(theta) + _center.y();

        _vertexArray.emplace_back(x, y);

        theta = (_rotationAngle / 180.0f) * PI + _fractionOfCircle * 2 * PI * float(i + 1) / float(_numSegments);

        x = _smallRadius * cos(theta) + _center.x();
        y = _smallRadius * sin(theta) + _center.y();

        _vertexArray.emplace_back(x, y);

        _vertexArray.push_back( _vertexArray.last() );
        _vertexArray.push_back( _vertexArray[_vertexArray.size() - 3] );

        x = _bigRadius * cos(theta) + _center.x();
        y = _bigRadius * sin(theta) + _center.y();

        _vertexArray.emplace_back(x, y);
    }
}

void Ring::setVertexArrayByteSize()
{
    _vertexArrayByteSize = _vertexArray.size() * 2 * sizeof(float);
}
