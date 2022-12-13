#ifndef ROUNDEDLINE_H
#define ROUNDEDLINE_H

#include "../GameLogic/Configuration.h"
#include "ComplexObject.h"
#include "Rectangle.h"
#include "Circle.h"


class RoundedRectangle : public ComplexObject
{
public:
    RoundedRectangle();
    RoundedRectangle(float x, float y, float width, float height, float roundingRadius, float roundingNumSegments,
                     const QVector3D& color);
    RoundedRectangle(const QVector2D& center, const QVector2D& dimension, float roundingRadius,
                     float roundingNumSegments, const QVector3D& color);

    ~RoundedRectangle() = default;

protected:
    void userInputCheck();
    void setupSceneObjects();

    float _roundingRadius;
    float _roundingNumSegments;
};


#endif // ROUNDEDLINE_H
