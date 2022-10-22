#ifndef СircleObject_H
#define СircleObject_H

#include "GameObject.h"


class CircleObject : public GameObject
{
public:
    CircleObject();
    CircleObject(float x, float y, float dx, float dy, float radius, float numSegments);
    CircleObject(const QVector2D& center, const QVector2D& speed, float radius, float numSegments);

    QVector2D* const getVertexArray() override;
    int getVertexArrayByteSize() override;
};


#endif // СircleObject_H
