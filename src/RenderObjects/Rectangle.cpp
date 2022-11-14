#include "Rectangle.h"

Rectangle::Rectangle() : RenderObject()
{
    setupRenderObject();
}

Rectangle::Rectangle(float x, float y, float width, float height) : RenderObject(x, y, width, height)
{
    setupRenderObject();
}

Rectangle::Rectangle(const QVector2D& center, const QVector2D& dimension) : RenderObject(center, dimension)
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
    // left top vertex
    _vertexArray.emplace_back(_center.x() - width() / 2.0f, _center.y() + height() / 2.0f);

    // left bottom vertex
    _vertexArray.emplace_back(_center.x() - width() / 2.0f, _center.y() - height() / 2.0f);

    // right bottom vertex
    _vertexArray.emplace_back(_center.x() + width() / 2.0f, _center.y() - height() / 2.0f);

    // right top vertex
    _vertexArray.emplace_back(_center.x() + width() / 2.0f, _center.y() + height() / 2.0f);

    qDebug() << _vertexArray;
}

void Rectangle::setVertexArrayByteSize()
{
    _vertexArrayByteSize = _vertexArray.size() * 2 * sizeof(float);
}
