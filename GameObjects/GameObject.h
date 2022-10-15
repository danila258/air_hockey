#ifndef GameObject_H
#define GameObject_H

#include "../GameLogic/Vertex.h"

#include <vector>
#include <cmath>
#include <QVector2D>


class GameObject
{
public:
    GameObject();
    GameObject(float x, float y, float dx, float dy, float radius, float numSegments);
    GameObject(const Vertex<float>& center, const QVector2D speed, float radius,  float numSegments);

    virtual ~GameObject() = default;

    virtual const Vertex<float>* const getVertexArray() = 0;
    virtual int getVertexArrayByteSize() = 0;

    const int getX();
    const int getY();
    const Vertex<float>& getCentre();

    int getRadius();
    int getNumSegments();
    const QVector2D& getSpeed();

    void setCentre(float x, float y);
    void setCentre(const Vertex<float>& centre);

    void setSpeed(const QVector2D& speed);

    void moveCentreBy(float x, float y);
    void changeSpeedBy(float x, float y);

protected:
    std::vector<Vertex<float>> _vertexes;

    Vertex<float> _centre;
    QVector2D _speed;

    float _radius;
    float _numSegments;
};


#endif // GameObject_H
