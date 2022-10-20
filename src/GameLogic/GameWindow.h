#ifndef RectangleWindow_H
#define RectangleWindow_H

#include "../GameObjects/Puck.h"
#include "ShaderProgram.h"

#include <QOpenGLWindow>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMouseEvent>
#include <QDebug>
#include <QWidget>


class GameWindow : public QOpenGLWindow {
public:
    GameWindow();
    ~GameWindow() override;

private:
    void initializeGL() override;
    void paintGL() override;

    void calculatePhysics();

    QOpenGLVertexArrayObject _vao;
    QOpenGLBuffer _vbo;
    ShaderProgram _program;

    Puck _userPuck;

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
};


#endif // RectangleWindow_H
