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

    void calculateObjectsCollisions();
    void calculateWallsCollisions(QVector<GameObject*> objects, bool freeObjectsFlag);
    void frictionForce();

    float getCos(const QVector2D& v1, const QVector2D& v2);
    QVector2D getReflectedVector(const QVector2D& vector, const QVector2D& normal);
};


#endif // Physics_H
