#ifndef СircleObject_H
#define СircleObject_H

#include "GameObject.h"


class CircleObject : public GameObject
{
public:
    CircleObject();
    CircleObject(float x, float y, float dx, float dy, float radius, float numSegments, bool controlledFlag);
    CircleObject(const QVector2D& center, const QVector2D& speed, float radius, float numSegments, bool controlledFlag);

    QVector2D* const getVertexArray() override;
    int getVertexArrayByteSize() const override;

    void create() override;
    void render() override;
};


#endif // СircleObject_H
