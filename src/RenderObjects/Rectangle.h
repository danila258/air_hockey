#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "RenderObject.h"


class Rectangle : public RenderObject
{
public:
    Rectangle();
    Rectangle(float x, float y, float width, float height);
    Rectangle(const QVector2D& center, const QVector2D& dimension);

    ~Rectangle() override = default;

    void setVertexArray() override;
    void setVertexArrayByteSize() override;

private:
    int _numSegments;
};


#endif // RECTANGLE_H
