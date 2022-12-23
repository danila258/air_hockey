#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "../GameObjects/Bat.h"

#include <QMouseEvent>
#include <QVector>
#include <QList>
#include <QPair>


class InputHandler
{
public:
    InputHandler() = delete;
    InputHandler(GameObject& userBat, GameObject& puck, float width, float height);

    void mouseMoveEvent(QMouseEvent* event, float width, float height);
    void mousePressEvent(QMouseEvent* event, float width, float height);
    void mouseReleaseEvent(QMouseEvent* event, float width, float height);

    void updateUserBatPosition();

private:
    QVector2D getGlCoordinates(const QVector2D& vertex) const;

    GameObject& _userBat;
    GameObject& _puck;

    QVector2D _lastPosition;
    QVector2D _lastSpeed;

    bool _clickFlag = false;
    bool _speedFlag = false;    // set speed 0, when user click but don't move

    float _width;
    float _height;
};


#endif // INPUTHANDLER_H
