#ifndef Physics_H
#define Physics_H

#include "Configuration.h"
#include "../GameObjects/CircleObject.h"

#include <cmath>


class Physics
{
public:
    Physics(QVector<GameObject*>& controlledObjects, QVector<GameObject*>& freeObjects);

    void setControlledObjects(QVector<GameObject*>& controlledObjects);
    void setFreeObjects(QVector<GameObject*>& freeObjects);

    void calulatePhysics();

private:
    QVector<GameObject*>& _controlledObjects;
    QVector<GameObject*>& _freeObjects;

    void calculateObjectsCollisions() const;
    void calculateWallsCollisions(QVector<GameObject*> objects, bool freeObjectsFlag) const;
    void frictionForce() const;

    void removeIntersections(GameObject& freeObject, const GameObject& controlledObject) const;

    QVector2D getReflectedVector(const QVector2D& vector, const QVector2D& normal) const;
    QVector2D getProjection(const QVector2D& axis, const QVector2D& vector) const;

    float getCos(const QVector2D v1, const QVector2D v2) const;
    QVector2D solveQuadraticEquation(float a, float b, float c) const;
};


#endif // Physics_H
