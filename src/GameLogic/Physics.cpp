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
    calculateControlledObjectsWallsCollisions(_controlledObjects);
    calculateFreeObjectsWallsCollisions(_freeObjects);
    calculateObjectsCollisions();

    speedControl();
    frictionForce();
}

void Physics::calculateFreeObjectsWallsCollisions(QVector<GameObject*> objects) const
{
    for (auto&& object : objects)
    {
        bool positionFlag = object->getX() - object->getRadius() >= - GATE_WIDTH / 2.0f &&
                object->getX() + object->getRadius() <= GATE_WIDTH / 2.0f;

        bool positionFlag2 = object->getX() - object->getRadius() + object->getSpeed().x() < - GATE_WIDTH / 2.0f &&
                object->getX() + object->getRadius() + object->getSpeed().x() > GATE_WIDTH / 2.0f;

        if (positionFlag && std::abs( object->getY() ) + object->getRadius() + object->getSpeed().y()
            > MAX_Y - WALL_OFFSET - WALL_WIDTH)
        {
            bool flag = false;
            QVector2D translate;

            if (object->getX() + object->getRadius() + object->getSpeed().x() >=
                GATE_WIDTH / 2.0f)
            {
                flag = true;
                float difference = object->getX() + object->getRadius() + object->getSpeed().x()
                                   - GATE_WIDTH / 2.0f;

                translate = object->getSpeed().normalized()
                            * (object->getSpeed().length() - difference / getSin(object->getSpeed(), {0.0f, 1.0f}));

                object->setSpeed( getReflectedVector(object->getSpeed(), {1.0f, 0.0f}) );
            }

            if (object->getX() - object->getRadius() + object->getSpeed().x() <=
                - GATE_WIDTH / 2.0f)
            {
                flag = true;
                float difference = object->getX() - object->getRadius() + object->getSpeed().x()
                                   + GATE_WIDTH / 2.0f;

                translate = object->getSpeed().normalized()
                             * (object->getSpeed().length() + difference / getSin(object->getSpeed(), {0.0f, 1.0f}));

                object->setSpeed( getReflectedVector(object->getSpeed(), {-1.0f, 0.0f}) );
            }

            if (flag)
            {
                object->changeCenter(translate);
            }
        }
        else if ( std::abs(object->getY() - object->getSpeed().y() ) <= MAX_Y - WALL_OFFSET - WALL_WIDTH &&
                  !positionFlag)
        {
            bool flagX = false;
            bool flagY = false;

            QVector2D translateX;
            QVector2D translateY;

            if (object->getX() + object->getRadius() + object->getSpeed().x() > MAX_X - (WALL_OFFSET + WALL_WIDTH))
            {
                flagX = true;
                float difference = object->getX() + object->getRadius() + object->getSpeed().x()
                                   - (MAX_X - (WALL_OFFSET + WALL_WIDTH));

                translateX = object->getSpeed().normalized()
                             * (object->getSpeed().length() - difference / getSin(object->getSpeed(), {0.0f, 1.0f}));

                object->setSpeed( getReflectedVector(object->getSpeed(), {-1.0f, 0.0f}) );
            }

            if (object->getX() - object->getRadius() + object->getSpeed().x() < MIN_X + (WALL_OFFSET + WALL_WIDTH))
            {
                flagX = true;
                float difference = object->getX() - object->getRadius() + object->getSpeed().x()
                                   - (MIN_X + (WALL_OFFSET + WALL_WIDTH));

                translateX = object->getSpeed().normalized()
                             * (object->getSpeed().length() + difference / getSin(object->getSpeed(), {0.0f, 1.0f}));

                object->setSpeed( getReflectedVector(object->getSpeed(), {1.0f, 0.0f}) );
            }

            if (object->getY() + object->getRadius() + object->getSpeed().y() > MAX_Y - (WALL_OFFSET + WALL_WIDTH))
            {
                flagY = true;
                float difference = object->getY() + object->getRadius() + object->getSpeed().y()
                                   - (MAX_Y - (WALL_OFFSET + WALL_WIDTH));

                translateY = object->getSpeed().normalized()
                             * (object->getSpeed().length() - difference / getSin(object->getSpeed(), {1.0f, 0.0f}));

                object->setSpeed( getReflectedVector(object->getSpeed(), {0.0f, -1.0f}) );
            }

            if (object->getY() - object->getRadius() + object->getSpeed().y() < MIN_Y + (WALL_OFFSET + WALL_WIDTH))
            {
                flagY = true;
                float difference = object->getY() - object->getRadius() + object->getSpeed().y()
                                   - (MIN_Y + (WALL_OFFSET + WALL_WIDTH));

                translateY = object->getSpeed().normalized()
                             * (object->getSpeed().length() + difference / getSin(object->getSpeed(), {1.0f, 0.0f}));

                object->setSpeed( getReflectedVector(object->getSpeed(), {0.0f, -1.0f}) );
            }

            if (flagX && flagY)
            {
                object->changeCenter((translateX + translateY) / 2.0f);
            }
            else if (flagX)
            {
                object->changeCenter(translateX);
            }
            else if (flagY)
            {
                object->changeCenter(translateY);
            }
        }
    }
}

void Physics::calculateControlledObjectsWallsCollisions(QVector<GameObject*> objects) const
{
    for (auto&& object : objects)
    {
        QVector2D newCenter = object->getCenter();

        if (object->getX() + object->getRadius() > MAX_X - (WALL_OFFSET + WALL_WIDTH))
        {
            newCenter[0] = MAX_X - (WALL_OFFSET + WALL_WIDTH) - object->getRadius();
        }

        if (object->getX() - object->getRadius() < MIN_X + (WALL_OFFSET + WALL_WIDTH))
        {
            newCenter[0] = MIN_X + (WALL_OFFSET + WALL_WIDTH) + object->getRadius();
        }

        if (object->getY() + object->getRadius() > MAX_Y - (WALL_OFFSET + WALL_WIDTH))
        {
            newCenter[1] = MAX_Y - (WALL_OFFSET + WALL_WIDTH) - object->getRadius();
        }

        if (object->getY() - object->getRadius() < MIN_Y + (WALL_OFFSET + WALL_WIDTH))
        {
            newCenter[1] = MIN_Y + (WALL_OFFSET + WALL_WIDTH) + object->getRadius();
        }

        if (newCenter != object->getCenter())
        {
            object->resetDifVector();
            object->setCenter(newCenter);
        }
    }
}

void Physics::calculateObjectsCollisions() const
{
    for (auto&& freeObject : _freeObjects)
    {
        for (auto&& controlledObject : _controlledObjects)
        {
            QVector2D connectedVector(freeObject->getCenter() - controlledObject->getCenter());

            if (connectedVector.length() <= freeObject->getRadius() + controlledObject->getRadius())
            {
                //removeIntersections(*freeObject, *controlledObject);
                connectedVector = freeObject->getCenter() - controlledObject->getCenter();

                QVector2D projectionOne;
                QVector2D projectionSecond = {ZERO, ZERO};

                if (getCos(connectedVector, freeObject->getSpeed()) > 0)
                {
                    projectionOne = getProjection(connectedVector, freeObject->getSpeed());
                }
                else
                {
                    projectionOne = getProjection(connectedVector, -freeObject->getSpeed());
                }

                if (getCos(connectedVector, controlledObject->getSpeed()) > 0)
                {
                    projectionSecond = getProjection(connectedVector, controlledObject->getSpeed());
                }

                freeObject->setSpeed(projectionOne + projectionSecond);
            }
        }
    }
}

void Physics::frictionForce() const
{
    for (auto&& object : _freeObjects)
    {
        float speedX = object->getSpeed().x();
        float speedY = object->getSpeed().y();

        float cosX = std::abs(speedX / float(object->getSpeed().length()));
        float cosY = std::abs(speedY / float(object->getSpeed().length()));

        float forceX = cosX * FRICTION_FORCE;
        float forceY = cosY * FRICTION_FORCE;

        if (std::abs(speedX) > forceX)
        {
            (speedX > ZERO) ? object->setSpeedX(speedX - forceX) : object->setSpeedX(speedX + forceX);
        }
        else
        {
            object->setSpeedX(ZERO);
        }

        if (std::abs(speedY) > forceY)
        {
            (speedY > ZERO) ? object->setSpeedY(speedY - forceY) : object->setSpeedY(speedY + forceY);
        }
        else
        {
            object->setSpeedY(ZERO);
        }
    }
}

void Physics::speedControl() const
{
    for (auto&& object : _freeObjects)
    {
        float speedX = object->getSpeed().x();
        float speedY = object->getSpeed().y();

        if (std::abs(speedX) > MAX_SPEED)
        {
            speedX = (speedX > ZERO) ? MAX_SPEED : -MAX_SPEED;
        }

        if (speedY > MAX_SPEED)
        {
            speedY = (speedY > ZERO) ? MAX_SPEED : -MAX_SPEED;
        }

        object->setSpeed(speedX, speedY);
    }
}

void Physics::removeIntersections(GameObject& freeObject, const GameObject& controlledObject) const
{
    QVector2D connectedVector = freeObject.getCenter() - controlledObject.getCenter();
    QVector2D motionVector = freeObject.getSpeed();

    if (connectedVector.length() / (freeObject.getRadius() + controlledObject.getRadius()) >= MAX_INTERSECTION_PERCENT)
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

QVector2D getReflectedVector(const QVector2D& vector, const QVector2D& normal)
{
    float dot = QVector2D::dotProduct(normal, vector);

    if (dot == ZERO)
    {
        return -vector;
    }

    return vector - 2.0f * normal * dot;
}

float getCos(const QVector2D v1, const QVector2D v2)
{
    if (v1.length() == 0 || v2.length() == 0)
    {
        return ZERO;
    }

    return QVector2D::dotProduct(v1, v2) / (v1.length() * v2.length());
}

float getSin(const QVector2D v1, const QVector2D v2)
{
    float cos = getCos(v1, v2);
    return std::sqrt(1.0f - cos * cos);
}

QVector2D getProjection(const QVector2D& axis, const QVector2D& vector)
{
    return axis * (QVector2D::dotProduct(axis, vector) / axis.lengthSquared());
}

QVector2D solveQuadraticEquation(float a, float b, float c)
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
