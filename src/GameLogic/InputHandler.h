#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "../GameObjects/CircleObject.h"

#include <QMouseEvent>
#include <QVector>
#include <QList>
#include <QPair>


class InputHandler
{
public:
    InputHandler(CircleObject& userBat, CircleObject& puck, float width, float height);

    void mouseMoveEvent(QMouseEvent* event, float width, float height);
    void mousePressEvent(QMouseEvent* event, float width, float height);
    void mouseReleaseEvent(QMouseEvent* event);

    void updateUserBatPosition();

private:
    bool detectPuckOnTrajectory(const QVector2D& motionVector);
    QVector2D getGlCoordinates(const QVector2D& vertex) const;

    CircleObject& _userBat;
    CircleObject& _puck;

    QList<QPair<QVector2D, bool>> _touchVertexes;
    bool _clickFlag = false;

    float _width;
    float _height;
};


#endif // INPUTHANDLER_H
