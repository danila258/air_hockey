#ifndef CIRCLE_H
#define CIRCLE_H

#include "SceneObject.h"


class Circle : public SceneObject
{
public:
    Circle();
    Circle(float x, float y, float radius, float numSegments, float rotationAngle, float fractionOfCircle);
    Circle(const QVector2D& center, float radius,  float numSegments, float rotationAngle, float fractionOfCircle);

    ~Circle() override;

private:    
    void setVertexArray() override;
    void setVertexArrayByteSize() override;

    float _rotationAngle;
    float _fractionOfCircle;
};


#endif // CIRCLE_H
