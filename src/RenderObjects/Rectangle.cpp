#include "Rectangle.h"

Rectangle::Rectangle() : RenderObject()
{
    void setupRenderObject();
}

Rectangle::Rectangle(float x, float y, float width, float height) : RenderObject({x, y}, {width, height})
{
    void setupRenderObject();
}

Rectangle::Rectangle(const QVector2D& center, const QVector2D& dimension) : RenderObject(center, dimension)
{
    void setupRenderObject();
}

void Rectangle::setVertexArray()
{
    // left top vertex
    _vertexArray.emplace_back(_center.x() - width() / 2.0f, _center.y() + height() / 2.0f);

    // left bottom vertex
    _vertexArray.emplace_back(_center.x() - width() / 2.0f, _center.y() - height() / 2.0f);

    // right top vertex
    _vertexArray.emplace_back(_center.x() + width() / 2.0f, _center.y() + height() / 2.0f);

    // right bottom vertex
    _vertexArray.emplace_back(_center.x() + width() / 2.0f, _center.y() - height() / 2.0f);
}

void Rectangle::setVertexArrayByteSize()
{
    _vertexArrayByteSize = 4;
}
