#ifndef BAT_H
#define BAT_H

#include "CircleObject.h"
#include "../RenderObjects/Circle.h"
#include "../RenderObjects/Ring.h"


class Bat : public CircleObject
{
public:
    Bat();
    Bat(float x, float y, float dx, float dy, float radius, float numSegments, const QVector3D& color,
        bool controlledFlag);
    Bat(const QVector2D& center, const QVector2D& speed, float radius, float numSegments, const QVector3D& color,
        bool controlledFlag);

    ~Bat() = default;

private:
    void setupSceneObjects() override;
};


#endif // BAT_H
