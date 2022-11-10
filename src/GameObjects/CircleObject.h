#ifndef CIRCLEOBJECT_H
#define CIRCLEOBJECT_H

#include "GameObject.h"


class CircleObject : public GameObject
{
public:
    CircleObject();
    CircleObject(float x, float y, float dx, float dy, float radius, float numSegments, bool controlledFlag);
    CircleObject(const QVector2D& center, const QVector2D& speed, float radius, float numSegments, bool controlledFlag);

    void create() override;
    void render() override;

private:
    QVector2D* const getVertexArray();
    int getVertexArrayByteSize() const;
};


#endif // CIRCLEOBJECT_H
