#ifndef CIRCLE_H
#define CIRCLE_H

#include "RenderObject.h"


class Circle : public RenderObject
{
public:
    Circle();
    Circle(float x, float y, float radius, int numSegments, float rotationAngle, float fractionOfCircle);
    Circle(const QVector2D& center, float radius, int numSegments, float rotationAngle, float fractionOfCircle);

    ~Circle() override = default;

private:
    void setVertexArray() override;
    void setVertexArrayByteSize() override;

    float _rotationAngle;
    float _fractionOfCircle;

    int _numSegments;
};


#endif // CIRCLE_H
