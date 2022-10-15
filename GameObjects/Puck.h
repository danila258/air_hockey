#ifndef Puck_H
#define Puck_H

#include "GameObject.h"

class Puck : public GameObject
{
public:
    Puck();
    Puck(float x, float y, float dx, float dy, float radius, float numSegments);
    Puck(const Vertex<float>& center, const QVector2D speed, float radius,  float numSegments);

    const Vertex<float>* const getVertexArray() override;
    int getVertexArrayByteSize() override;
};

#endif // Puck_H
