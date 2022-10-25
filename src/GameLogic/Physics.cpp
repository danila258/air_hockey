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
    calculateWallsCollisions(_controlledObjects, false);
    calculateWallsCollisions(_freeObjects, true);
    calculateObjectsCollisions();
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
                object->setSpeed(getReflectedVector(object->getSpeed(), {1.0f, 0.0f}));
            }
        }

        if (object->getY() + object->getRadius() > MAX_Y)
        {
            newCenter[1] = MAX_Y - object->getRadius();

            if (freeObjectsFlag)
            {
                object->setSpeed(getReflectedVector(object->getSpeed(), {0.0f, -1.0f}));
            }
        }

        if (object->getY() - object->getRadius() < MIN_Y)
        {
            newCenter[1] = MIN_Y + object->getRadius();

            if (freeObjectsFlag)
            {
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
            QVector2D connectedVector(freeObject->getCenter() - controlledObject->getCenter());

            if (connectedVector.length() <= freeObject->getRadius() + controlledObject->getRadius())
            {
                removeIntersections(*freeObject, *controlledObject);
                connectedVector = freeObject->getCenter() - controlledObject->getCenter();

                if (getCos(connectedVector, freeObject->getSpeed()) > 0)
                {
                    freeObject->setSpeed(getProjection(connectedVector, controlledObject->getSpeed()) +
                                         getProjection(connectedVector, freeObject->getSpeed()));
                }
                else
                {
                    freeObject->setSpeed(getProjection(connectedVector, controlledObject->getSpeed()) -
                                         getProjection(connectedVector, freeObject->getSpeed()));
                }

                // add max speed
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
                object->setSpeedY(speedY - FRICTION_FORCE);
            }
            else
            {
                object->setSpeedY(speedY + FRICTION_FORCE);
            }
        }
        else
        {
            object->setSpeedY(ZERO);
        }
    }
}

void Physics::removeIntersections(GameObject& freeObject, const GameObject& controlledObject) const
{
    QVector2D connectedVector = freeObject.getCenter() - controlledObject.getCenter();
    QVector2D motionVector = freeObject.getSpeed();

    if (connectedVector.length() + MAX_INTERSECTION <= freeObject.getRadius() + controlledObject.getRadius())
    {
        return;
    }

    float a = std::pow(motionVector.x(), 2.0f) + std::pow(motionVector.y(), 2.0f);
    float b = - 2.0f * connectedVector.x() * motionVector.x() - 2.0f * connectedVector.y() * motionVector.y();
    float c = std::pow(connectedVector.x(), 2.0f) + std::pow(connectedVector.y(), 2.0f) -
              std::pow(freeObject.getRadius() + controlledObject.getRadius(), 2.0f);

    QVector2D ratio;

    try
    {
         ratio = solveQuadraticEquation(a, b, c);
    }
    catch (...)
    {
        return;
    }

    QVector2D correctVector;

    correctVector = connectedVector - ratio[1] * motionVector;
    QVector2D centerOne = correctVector + controlledObject.getCenter();

    correctVector = connectedVector - ratio[0] * motionVector;
    QVector2D centerTwo = correctVector + controlledObject.getCenter();

    if (freeObject.getCenter().distanceToPoint(centerOne) <= freeObject.getCenter().distanceToPoint(centerTwo))
    {
        freeObject.setCenter(centerOne);
    }
    else
    {
        freeObject.setCenter(centerTwo);
    }
}

QVector2D Physics::getReflectedVector(const QVector2D& vector, const QVector2D& normal) const
{
    float dot = QVector2D::dotProduct(normal, vector);

    if (dot == ZERO)
    {
        return -vector;
    }

    return vector - 2.0f * normal * dot;
}

float Physics::getCos(const QVector2D v1, const QVector2D v2) const
{
    if (v1.length() == 0 || v2.length() == 0)
    {
        return ZERO;
    }

    return QVector2D::dotProduct(v1, v2) / (v1.length() * v2.length());
}

QVector2D Physics::getProjection(const QVector2D& axis, const QVector2D& vector) const
{
    return axis * (QVector2D::dotProduct(axis, vector) / axis.lengthSquared());
}

QVector2D Physics::solveQuadraticEquation(float a, float b, float c) const
{
    QVector2D answer;
    float D;

    D = b * b - 4.0f * a * c;

    if (D == 0)
    {
        throw std::runtime_error("discriminant = 0");
    }

    answer[0] = (- b + std::sqrt(D)) / (2 * a);
    answer[1] = (- b - std::sqrt(D)) / (2 * a);

    return answer;
}