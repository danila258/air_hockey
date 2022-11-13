#include "GameWindow.h"

GameWindow::GameWindow()
{
    Bat* userBat = new Bat(USER_BAT_CENTER_X, USER_BAT_CENTER_Y, ZERO, ZERO, USER_BAT_RADIUS, USER_BAT_NUM_SEGMENTS,
                           true);

    Bat* aiBat = new Bat(AI_BAT_CENTER_X, AI_BAT_CENTER_Y, ZERO, ZERO, AI_BAT_RADIUS, AI_BAT_NUM_SEGMENTS, true);

    Bat* puck = new Bat(PUCK_CENTER_X, PUCK_CENTER_Y, ZERO, ZERO, PUCK_RADIUS, PUCK_NUM_SEGMENTS, false);

    //RoundedLine* line = new RoundedLine({ZERO, ZERO}, 0.3f, 0.3f, 0.1f, 150);

    _controlledObjects.push_back(userBat);
    _controlledObjects.push_back(aiBat);
    _freeObjects.push_back(puck);
    //_decorations.push_back(line);

    _inputHandler = new InputHandler(*userBat, *puck, width(), height());
}

GameWindow::~GameWindow()
{
	makeCurrent();

    for (auto&& object : _controlledObjects)
    {
        delete object;
    }

    for (auto&& object : _freeObjects)
    {
        delete object;
    }
}

void GameWindow::initializeGL()
{    
    for (auto&& object : _controlledObjects)
    {
        object->create();
    }

    for (auto&& object : _freeObjects)
    {
        object->create();
    }
}


void GameWindow::paintGL()
{
    _inputHandler->updateUserBatPosition();
    _physics.calulatePhysics();

    glClearColor(0.4f, 0.3f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

    const qreal retinaScale = devicePixelRatio();                       // needed for Macs with retina display
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    for (auto&& object : _controlledObjects)
    {
        object->render();
    }

    for (auto&& object : _freeObjects)
    {
        object->render();
    }

    gameCycle();
}

void GameWindow::gameCycle()
{
    update();
}

void GameWindow::mouseMoveEvent(QMouseEvent* event)
{
    _inputHandler->mouseMoveEvent(event, width(), height());
}

void GameWindow::mousePressEvent(QMouseEvent* event)
{
    _inputHandler->mousePressEvent(event, width(), height());
}

void GameWindow::mouseReleaseEvent(QMouseEvent* event)
{
    _inputHandler->mouseReleaseEvent(event, width(), height());
}
