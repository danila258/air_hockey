#ifndef CIRCLEOBJECT_H
#define CIRCLEOBJECT_H

#include "GameObject.h"


class CircleObject : public GameObject
{
public:
    CircleObject();
    CircleObject(float x, float y, float dx, float dy, float radius, float numSegments, const QVector3D& color,
        bool controlledFlag);
    CircleObject(const QVector2D& center, const QVector2D& speed, float radius, float numSegments, const QVector3D& color,
        bool controlledFlag);

    ~CircleObject() = default;

    void create() override;
    void render() override;

private:
    virtual void setupSceneObjects() = 0;
};


#endif // CIRCLEOBJECT_H
