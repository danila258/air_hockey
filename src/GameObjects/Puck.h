#ifndef Puck_H
#define Puck_H

#include "GameObject.h"


class Puck : public GameObject
{
public:
    Puck();
    Puck(float x, float y, float dx, float dy, float radius, float numSegments);
    Puck(const QVector2D& center, const QVector2D& speed, float radius,  float numSegments);

    QVector2D* const getVertexArray() override;
    int getVertexArrayByteSize() override;
};

#endif // Puck_H
