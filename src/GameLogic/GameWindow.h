#ifndef RectangleWindow_H
#define RectangleWindow_H

#include "Configuration.h"
#include "ShaderProgram.h"
#include "Physics.h"
#include "../GameObjects/CircleObject.h"

#include <QOpenGLWindow>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMouseEvent>
#include <QDebug>


class GameWindow : public QOpenGLWindow
{
    Q_OBJECT

public:
    GameWindow();
    ~GameWindow() override;

private:
    void initializeGL() override;
    void paintGL() override;

    void gameCycle();
    void toGlCoordinates(QVector2D& vertex);    

    Physics _physics = {_userBat, _aiBat, _puck};

    QOpenGLVertexArrayObject _vao;
    QOpenGLBuffer _vbo;
    ShaderProgram _program;

    CircleObject _userBat;
    CircleObject _aiBat;
    CircleObject _puck;

    QVector2D _lastPosition;
    bool _clickFlag = false;

    float maxX = 0.0;
    float minX = 1.0;

    float maxY = 0.0;
    float minY = 1.0;

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
};


#endif // RectangleWindow_H
