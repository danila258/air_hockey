#ifndef AI_H
#define AI_H

#include "GameObject.h"
#include "../GameLogic/Physics.h"

#include <QVector2D>


class Ai
{
public:
    Ai() = delete;
    Ai(const GameObject& userBat, GameObject& aiBat, const GameObject& puck);

    void play();

private:
    void defense();
    void smartHit();
    void basicHit();
    void aiFixJam();

    GameObject& _aiBat;
    const GameObject& _userBat;
    const GameObject& _puck;

    QVector2D _aiDirection;
    QVector2D _calculationPuckSpeed;

    int _aiTime;      // time needed to smartHit
    int _curTime;     // time from the beginning of smartHit

    float _lastLength;

    QVector2D _lastPuckCenter;
    int _jamCount = 0;

    bool _smartHitFlag = false;
    bool _basicHitFlag = false;
    bool _completeHitFlag = false;
    bool _jamFlag = false;
};


#endif // AI_H
