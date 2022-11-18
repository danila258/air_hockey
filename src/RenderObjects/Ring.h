#ifndef RING_H
#define RING_H

#include "RenderObject.h"


class Ring : public RenderObject
{
public:
    Ring();
    Ring(float x, float y, float bigRadius, float smallRadius, float rotationAngle, float fractionOfCircle,
         int numSegments);
    Ring(const QVector2D& center, float bigRadius, float smallRadius, float rotationAngle, float fractionOfCircle,
         int numSegments);

    ~Ring() override = default;

private:
    void userInputCheck() override;
    void setVertexArray() override;
    void setVertexArrayByteSize() override;

    float _bigRadius;
    float _smallRadius;
    float _rotationAngle;
    float _fractionOfCircle;

    int _numSegments;
};


#endif // RING_H
