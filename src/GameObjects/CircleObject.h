#ifndef CIRCLEOBJECT_H
#define CIRCLEOBJECT_H

#include "GameObject.h"
#include "../RenderObjects/Circle.h"


class CircleObject : public GameObject
{
public:
    CircleObject();
    CircleObject(float x, float y, float dx, float dy, float radius, float numSegments, bool controlledFlag);
    CircleObject(const QVector2D& center, const QVector2D& speed, float radius, float numSegments, bool controlledFlag);

    void create() override;
    void render() override;
};


#endif // CIRCLEOBJECT_H
