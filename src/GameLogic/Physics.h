#ifndef PHYSICS_H
#define PHYSICS_H

#include "Configuration.h"
#include "../GameObjects/CircleObject.h"

#include <cmath>
#include <QDebug>


QVector2D getReflectedVector(const QVector2D& vector, const QVector2D& normal);
QVector2D getProjection(const QVector2D& axis, const QVector2D& vector);

float getCos(const QVector2D v1, const QVector2D v2);
float getSin(const QVector2D v1, const QVector2D v2);
QVector2D solveQuadraticEquation(float a, float b, float c);


class Physics
{
public:
    Physics() = delete;
    Physics(QVector<GameObject*>& controlledObjects, QVector<GameObject*>& freeObjects);

    void setControlledObjects(QVector<GameObject*>& controlledObjects);
    void setFreeObjects(QVector<GameObject*>& freeObjects);

    void calulatePhysics();

private:
    QVector<GameObject*>& _controlledObjects;
    QVector<GameObject*>& _freeObjects;

    void calculateObjectsCollisions() const;
    void calculateControlledObjectsWallsCollisions(QVector<GameObject*> objects) const;
    void calculateFreeObjectsWallsCollisions(QVector<GameObject*> objects) const;
    void frictionForce() const;
    void speedControl() const;

    void removeIntersections(GameObject& freeObject, const GameObject& controlledObject) const;
};


#endif // PHYSICS_H
