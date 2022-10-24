#include "Physics.h"

Physics::Physics(QVector<GameObject*>& controlledObjects, QVector<GameObject*>& freeObjects)
    : _controlledObjects(controlledObjects), _freeObjects(freeObjects)
{}

void Physics::setControlledObjects(QVector<GameObject*>& controlledObjects)
{
    _controlledObjects = controlledObjects;
}

void Physics::setFreeObjects(QVector<GameObject*>& freeObjects)
{
    _freeObjects = freeObjects;
}

void Physics::calulatePhysics()
{
    calculateObjectsCollisions();
    calculateWallsCollisions(_freeObjects, true);
    calculateWallsCollisions(_controlledObjects, false);
    frictionForce();
}

void Physics::calculateWallsCollisions(QVector<GameObject*> objects, bool freeObjectsFlag)
{
    for (auto&& object : objects)
    {
        QVector2D newCenter = object->getCenter();

        if (object->getX() + object->getRadius() > MAX_X)
        {
            newCenter[0] = MAX_X - object->getRadius();

            if (freeObjectsFlag)
            {
                object->setSpeed(getReflectedVector(object->getSpeed(), {-1.0f, 0.0f}));
            }
        }

        if (object->getX() - object->getRadius() < MIN_X)
        {
            newCenter[0] = MIN_X + object->getRadius();

            if (freeObjectsFlag)
            {
                qDebug() << "reflection 2";
                object->setSpeed(getReflectedVector(object->getSpeed(), {1.0f, 0.0f}));
            }
        }

        if (object->getY() + object->getRadius() > MAX_Y)
        {
            newCenter[1] = MAX_Y - object->getRadius();

            if (freeObjectsFlag)
            {
                qDebug() << "reflection 3";
                object->setSpeed(getReflectedVector(object->getSpeed(), {0.0f, -1.0f}));
            }
        }

        if (object->getY() - object->getRadius() < MIN_Y)
        {
            newCenter[1] = MIN_Y + object->getRadius();

            if (freeObjectsFlag)
            {
                qDebug() << "reflection 4";
                object->setSpeed(getReflectedVector(object->getSpeed(), {0.0f, 1.0f}));
            }
        }

        if (newCenter != object->getCenter())
        {
            object->resetDifVector();
            object->setCenter(newCenter);
        }
    }
}

void Physics::calculateObjectsCollisions()
{
    for (auto&& freeObject : _freeObjects)
    {
        for (auto&& controlledObject : _controlledObjects)
        {
            QVector2D newVector(freeObject->getCenter() - controlledObject->getCenter());

            if (newVector.length() <= freeObject->getRadius() + controlledObject->getRadius())
            {
                float cosControlled = getCos(controlledObject->getSpeed(), newVector);
                float cosFree = getCos(freeObject->getSpeed(), newVector);

                if (cosControlled != ZERO)
                {
                    freeObject->setSpeed(controlledObject->getSpeed() / cosControlled +
                                         freeObject->getSpeed() * cosFree);
                }
                else
                {
                    freeObject->setSpeed(freeObject->getSpeed() * cosFree);
                }

                qDebug() << "bat and puck collision";
            }
        }
    }
}

void Physics::frictionForce()
{
    for (auto&& object : _freeObjects)
    {
        float speedX = object->getSpeed().x();
        float speedY = object->getSpeed().y();

        if (std::abs(speedX) > FRICTION_FORCE)
        {
            if (speedX > ZERO)
            {
                object->setSpeedX(speedX - FRICTION_FORCE);
            }
            else
            {
                object->setSpeedX(speedX + FRICTION_FORCE);
            }
        }
        else
        {
            object->setSpeedX(ZERO);
        }

        if (std::abs(speedY) > FRICTION_FORCE)
        {
            if (speedY > ZERO)
            {
                object->setSpeedY(object->getSpeed().y() - FRICTION_FORCE);
            }
            else
            {
                object->setSpeedY(object->getSpeed().y() + FRICTION_FORCE);
            }
        }
        else
        {
            object->setSpeedY(ZERO);
        }
    }
}

float Physics::getCos(const QVector2D& v1, const QVector2D& v2)
{
    if (std::isnan(QVector2D::dotProduct(v1, v2) / (v1.length() * v2.length())))
    {
        //qDebug() << "length " << v1.length() << " " << v2.length();
        //qDebug() << "scalar multiply " << QVector2D::dotProduct(v1, v2);

        return ZERO;
    }

    return QVector2D::dotProduct(v1, v2) / (v1.length() * v2.length());
}

QVector2D Physics::getReflectedVector(const QVector2D& vector, const QVector2D& normal)
{
    qDebug() << "vector = " << vector;
    qDebug() << "dotProduct = " << QVector2D::dotProduct(normal, vector);
    qDebug() << "normal * dotProduct = " << normal * QVector2D::dotProduct(normal, vector);
    qDebug() << "2.0f * normal * dotProduct = " << 2.0f * normal * QVector2D::dotProduct(normal, vector);
    qDebug() << "vector - 2.0f * normal * dotProduct = " << vector - 2.0f * normal * QVector2D::dotProduct(normal, vector);

    float dot = QVector2D::dotProduct(normal, vector);

    if (dot == 0.0)
    {
        return -vector;
    }

    return vector - 2.0f * normal * dot;
}
