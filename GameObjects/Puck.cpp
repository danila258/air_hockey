#include "Puck.h"

Puck::Puck() : GameObject()
{}

Puck::Puck(float x, float y, float dx, float dy, float radius, float numSegments) :
    GameObject(x, y, dx, dy, radius, numSegments)
{}

Puck::Puck(const Vertex<float>& center, const QVector2D speed, float radius,  float numSegments) :
    GameObject(center, speed, radius, numSegments)
{}

const Vertex<float>* const Puck::getVertexArray()
{
    for (int i = 0; i < _numSegments; ++i)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(_numSegments);
        float x = _radius * std::cos(theta);
        float y = _radius * std::sin(theta);

        _vertexes.emplace_back(x, y);
    }

    return _vertexes.data();
}

int Puck::getVertexArrayByteSize()
{
    return _numSegments * 2 * sizeof(float);
}
