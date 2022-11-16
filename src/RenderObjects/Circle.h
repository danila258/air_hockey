#ifndef CIRCLE_H
#define CIRCLE_H

#include "RenderObject.h"


class Circle : public RenderObject
{
public:
    Circle();
    Circle(float x, float y, float radius, float rotationAngle, float fractionOfCircle, int numSegments);
    Circle(const QVector2D& center, float radius, float rotationAngle, float fractionOfCircle, int numSegments);

    ~Circle() override = default;

private:
    void userInputCheck() override;
    void setVertexArray() override;
    void setVertexArrayByteSize() override;

    float _rotationAngle;
    float _fractionOfCircle;

    int _numSegments;
};


#endif // CIRCLE_H
