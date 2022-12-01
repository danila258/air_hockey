#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "RenderObject.h"


class Rectangle : public RenderObject
{
public:
    Rectangle();
    Rectangle(float x, float y, float width, float height, const QVector3D& color);
    Rectangle(const QVector2D& center, const QVector2D& dimension, const QVector3D& color);

    ~Rectangle() override = default;

    void userInputCheck() override;
    void setVertexArray() override;
    void setVertexArrayByteSize() override;

private:
    int _numSegments;
};


#endif // RECTANGLE_H
