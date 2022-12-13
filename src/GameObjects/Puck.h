#ifndef PUCK_H
#define PUCK_H

#include "CircleObject.h"
#include "../RenderObjects/Circle.h"


class Puck : public CircleObject
{
public:
    Puck();
    Puck(float x, float y, float dx, float dy, float radius, float numSegments, const QVector3D& color,
        bool controlledFlag);
    Puck(const QVector2D& center, const QVector2D& speed, float radius, float numSegments, const QVector3D& color,
        bool controlledFlag);

    ~Puck() = default;

private:
    void setupSceneObjects() override;
};


#endif // PUCK_H
