#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "Configuration.h"
#include "InputHandler.h"
#include "Physics.h"
#include "GameRules.h"
#include "../GameObjects/Ai.h"
#include "../GameObjects/Bat.h"
#include "../GameObjects/Puck.h"
#include "../SceneObjects/RoundedRectangle.h"
#include "../SceneObjects/Ring.h"

#include <QOpenGLWindow>
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

    QVector<GameObject*> _controlledObjects;
    QVector<GameObject*> _freeObjects;
    QVector<SceneObject*> _decorations;

    Physics _physics = {_controlledObjects, _freeObjects};
    InputHandler* _inputHandler;
    GameRules* _gameRules;
    Ai* _ai;

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
};


#endif // GAMEWINDOW_H
