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
    InputHandler(Bat& userBat, Bat& puck, float width, float height);

    void mouseMoveEvent(QMouseEvent* event, float width, float height);
    void mousePressEvent(QMouseEvent* event, float width, float height);
    void mouseReleaseEvent(QMouseEvent* event, float width, float height);

    void updateUserBatPosition();

private:
    QVector2D getGlCoordinates(const QVector2D& vertex) const;

    Bat& _userBat;
    Bat& _puck;

    QVector2D _lastPosition;
    QVector2D _lastSpeed;

    bool _clickFlag = false;

    float _width;
    float _height;
};


#endif // INPUTHANDLER_H
