#include "Ai.h"

Ai::Ai(const GameObject& userBat, GameObject& aiBat, const GameObject& puck)
    : _userBat(userBat), _aiBat(aiBat), _puck(puck)
{}

void Ai::play()
{
    if (_completeHitFlag && _puck.getY() - _puck.getRadius() >= 0 && _puck.getSpeed().isNull())
    {
        _completeHitFlag = false;
        basicHit();
        return;
    }
    else if (_completeHitFlag)
    {
        defense();

        if (_puck.getY() - _puck.getRadius() < 0)
        {
            _completeHitFlag = false;
        }

        return;
    }

    if ( !(_basicHitFlag || _smartHitFlag) )
    {
        smartHit();
        return;
    }

    if (getCos(_puck.getSpeed(), _calculationPuckSpeed) < 0.99f && !_puck.getSpeed().isNull() ||
        std::abs( _calculationPuckSpeed.x() ) < std::abs( _puck.getSpeed().x() ) ||
        std::abs( _calculationPuckSpeed.y() ) < std::abs( _puck.getSpeed().y() ))
    {
        qDebug() << "puck speed change" << _puck.getCenter();

        if (_smartHitFlag)
        {
            smartHit();
        }
        else
        {
            basicHit();
        }
    }
    if (_curTime < _aiTime)
    {
        ++_curTime;
        _aiBat.changeCenter(_aiDirection * AI_BAT_SPEED);
    }
    else
    {
        qDebug() << "end hit";

        if (_smartHitFlag)
        {
            _smartHitFlag = false;
            basicHit();
        }
        else
        {
            _basicHitFlag = false;
            _completeHitFlag = true;
        }
    }
}

void Ai::defense()
{
    _basicHitFlag = false;
    _smartHitFlag = false;

    float translateX = _puck.getX() - _aiBat.getX();
    float translateY = AI_BAT_CENTER_Y - _aiBat.getY();

    if (std::abs( _aiBat.getX() ) > GATE_WIDTH / 2.0f)
    {
        translateX = (_puck.getX() > 0)? -AI_BAT_SPEED : AI_BAT_SPEED;
        _aiBat.changeCenter(translateX, ZERO);
    }
    else if (std::abs(translateX) > AI_BAT_SPEED)
    {
        translateX = (translateX > 0)? AI_BAT_SPEED : -AI_BAT_SPEED;

        if (_aiBat.getX() + translateX > - GATE_WIDTH / 2.0f && _aiBat.getX() + translateX < GATE_WIDTH / 2.0f)
        {
            _aiBat.changeCenter(translateX, ZERO);
        }
    }

    if (std::abs(translateY) > AI_BAT_SPEED)
    {
        translateY = (translateY > 0)? AI_BAT_SPEED : -AI_BAT_SPEED;
    }

    _aiBat.changeCenter(ZERO, translateY);
}

void Ai::smartHit()
{
    QVector2D aiDirection;

    if ( _puck.getSpeed().isNull() )
    {
        basicHit();
        return;
    }
    else
    {
        aiDirection = {-_puck.getSpeed().y(), _puck.getSpeed().x()};
    }

    aiDirection.normalize();

    float aiPathLength = _aiBat.getCenter().distanceToLine(_puck.getCenter(), _puck.getSpeed().normalized());

    _aiTime = aiPathLength / AI_BAT_SPEED;

    QVector2D aiCollisionPoint = _aiBat.getCenter() + aiDirection * AI_BAT_SPEED * _aiTime;

    if (!(aiCollisionPoint.y() - _aiBat.getRadius() > ZERO
          && aiCollisionPoint.y() < MAX_Y - WALL_OFFSET - WALL_WIDTH
          && aiCollisionPoint.x() > MIN_X + WALL_OFFSET + WALL_WIDTH
          && aiCollisionPoint.x() < MAX_X - WALL_OFFSET - WALL_WIDTH))
    {
        defense();
        return;
    }

    float frictionForceX = std::abs(_puck.getSpeed().x() / float(_puck.getSpeed().length())) * FRICTION_FORCE;
    float frictionForceY = std::abs(_puck.getSpeed().y() / float(_puck.getSpeed().length())) * FRICTION_FORCE;

    int maxPuckTime = std::abs( _puck.getSpeed().x() ) / frictionForceX;    // when speed = 0

    QVector2D puckCollisionPoint;

    if (_aiTime > maxPuckTime)
    {
        puckCollisionPoint =
        {_puck.getX() + _puck.getSpeed().x() * maxPuckTime - 0.5f * (frictionForceX * maxPuckTime * maxPuckTime),
         _puck.getY() + _puck.getSpeed().y() * maxPuckTime - 0.5f * (frictionForceY * maxPuckTime * maxPuckTime)};
    }
    else
    {
        puckCollisionPoint =
        {_puck.getX() + _puck.getSpeed().x() * _aiTime - 0.5f * (frictionForceX * _aiTime * _aiTime),
         _puck.getY() + _puck.getSpeed().y() * _aiTime - 0.5f * (frictionForceY * _aiTime * _aiTime)};
    }

    if (puckCollisionPoint.y() <= aiCollisionPoint.y() && puckCollisionPoint.y() - _puck.getRadius() > ZERO)
    {
        _smartHitFlag = true;
        _curTime = 0;
        _aiBat.setSpeed(aiDirection * AI_BAT_SPEED);

        _aiDirection = aiDirection;
        _calculationPuckSpeed = _puck.getSpeed();
    }
    else
    {
        defense();
    }
}

void Ai::basicHit()
{
    if (_puck.getY() - _puck.getRadius() < ZERO)
    {
        return;
    }

    _curTime = 0;

    QVector2D direction = _puck.getCenter() - _aiBat.getCenter();

    float frictionForceX = std::abs(_puck.getSpeed().x() / float(_puck.getSpeed().length())) * FRICTION_FORCE;
    float frictionForceY = std::abs(_puck.getSpeed().y() / float(_puck.getSpeed().length())) * FRICTION_FORCE;

    int maxPuckTime = _puck.getSpeed().x() / frictionForceX;

    QVector2D time = solveQuadraticEquation(0.5f * frictionForceX,
                                            direction.normalized().x() * AI_BAT_SPEED - _puck.getSpeed().x(),
                                            _aiBat.getX() - _puck.getX());

    QVector2D time2 = solveQuadraticEquation(0.5f * frictionForceY,
                                             direction.normalized().y() * AI_BAT_SPEED - _puck.getSpeed().y(),
                                             _aiBat.getY() - _puck.getY());

    if ( _puck.getSpeed().isNull() )
    {
        _aiTime = (direction.length() - _puck.getRadius() - _aiBat.getRadius()) / AI_BAT_SPEED + 1;
        qDebug() << "standart" << _aiTime;
    }
    else if (time[0] > maxPuckTime)
    {
        QVector2D newPuckCenter =
        {_puck.getX() + _puck.getSpeed().x() * maxPuckTime - 0.5f * frictionForceX * maxPuckTime * maxPuckTime,
         _puck.getY() + _puck.getSpeed().y() * maxPuckTime - 0.5f * frictionForceY * maxPuckTime * maxPuckTime};

        _aiTime = ((newPuckCenter - _aiBat.getCenter()).length() - _puck.getRadius() - _aiBat.getRadius()) / AI_BAT_SPEED - 1;
        qDebug() << "newPuckCenter" << _aiTime << frictionForceX;
    }
    else
    {
        _aiTime = time[0];
        qDebug() << "motion collision" << _aiTime;
    }

    _basicHitFlag = true;
    _aiDirection = direction.normalized();
    _calculationPuckSpeed = _puck.getSpeed();

    _aiBat.setSpeed(_aiDirection * AI_BAT_SPEED);
}


