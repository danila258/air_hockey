#include "Rectangle.h"

Rectangle::Rectangle() : RenderObject()
{
    setupRenderObject();
}

Rectangle::Rectangle(float x, float y, float width, float height, const QVector3D& color)
    : RenderObject(x, y, width, height, ZERO, color)
{
    setupRenderObject();
}

Rectangle::Rectangle(const QVector2D& center, const QVector2D& dimension, const QVector3D& color)
    : RenderObject(center, dimension, ZERO, color)
{
    setupRenderObject();
}

void Rectangle::userInputCheck()
{
    if (width() < ZERO || height() < ZERO)
    {
        throw std::logic_error("incorrectly passed data to the constructor of rectangle");
    }
}

void Rectangle::setVertexArray()
{
    // triangle 1

    // left top vertex
    _vertexArray.emplace_back(x() - width() / 2.0f, y() + height() / 2.0f);

    // left bottom vertex
    _vertexArray.emplace_back(x() - width() / 2.0f, y() - height() / 2.0f);

    // right bottom vertex
    _vertexArray.emplace_back(x() + width() / 2.0f, y() - height() / 2.0f);

    // triangle 2

    // right top vertex
    _vertexArray.emplace_back(x() + width() / 2.0f, y() + height() / 2.0f);

    // left top vertex
    _vertexArray.emplace_back(x() - width() / 2.0f, y() + height() / 2.0f);

    // right bottom vertex
    _vertexArray.emplace_back(x() + width() / 2.0f, y() - height() / 2.0f);
}

void Rectangle::setVertexArrayByteSize()
{
    _vertexArrayByteSize = _vertexArray.size() * 2 * sizeof(float);
}
