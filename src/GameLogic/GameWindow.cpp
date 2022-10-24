#include "GameWindow.h"

GameWindow::GameWindow() : _physics(_controlledObjects, _freeObjects)
{
    _userBat = new CircleObject(USER_BAT_CENTER_X, USER_BAT_CENTER_Y, ZERO, ZERO, USER_BAT_RADIUS,
                                              USER_BAT_NUM_SEGMENTS, true);

    CircleObject* aiBat = new CircleObject(AI_BAT_CENTER_X, AI_BAT_CENTER_Y, ZERO, ZERO, AI_BAT_RADIUS,
                                             AI_BAT_NUM_SEGMENTS, true);

    CircleObject* puck = new CircleObject(PUCK_CENTER_X, PUCK_CENTER_Y, ZERO, ZERO, PUCK_RADIUS, PUCK_NUM_SEGMENTS,
                                          false);

    _controlledObjects.push_back(_userBat);
    _controlledObjects.push_back(aiBat);
    _freeObjects.push_back(puck);
}

GameWindow::~GameWindow()
{
	makeCurrent();

    for (auto&& object : _controlledObjects)
    {
        object->destroy();
        delete object;
    }

    for (auto&& object : _freeObjects)
    {
        object->destroy();
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
    _physics.calulatePhysics();

    glClearColor(0.4f, 0.3f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

    const qreal retinaScale = devicePixelRatio(); // needed for Macs with retina display
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

void GameWindow::toGlCoordinates(QVector2D& vertex)
{
    vertex = {(vertex.x() - width() / 2) / (width() / 2), - (vertex.y() - width() / 2) / (width() / 2)};
}

void GameWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (!_clickFlag)
    {
        return;
    }

    QVector2D position( event->position().rx(), event->position().ry() );
    toGlCoordinates(position);

    QVector2D test = position - _lastPosition;
    test[0] = std::abs(test[0]);
    test[1] = std::abs(test[1]);

    if (test[0] > maxX)
    {
        maxX = test[0];
    }
    else if (test[0] < minX && test[0] != 0)
    {
        minX = test[0];
    }

    if (test[1] > maxY)
    {
        maxY = test[1];
    }
    else if (test[1] < minY && test[1] != 0)
    {
        minY = test[1];
    }

    //qDebug() << "maxX = " << maxX << "minX = " << minX;
    //qDebug() << "maxY = " << maxY << "minY = " << minY;

    _userBat->changeCenter(position - _lastPosition);
    _userBat->setSpeed(position - _lastPosition);

    _lastPosition = position;
}

void GameWindow::mousePressEvent(QMouseEvent* event)
{
    QVector2D position( event->position().rx(), event->position().ry() );
    toGlCoordinates(position);

    if (!(_userBat->getX() - _userBat->getRadius() <= position.x() &&
          position.x() <= _userBat->getX() + _userBat->getRadius() &&
          _userBat->getY() - _userBat->getRadius() <= position.y() &&
          position.y() <= _userBat->getY() + _userBat->getRadius()))
    {
        return;
    }

    if (event->button() == Qt::LeftButton)
    {
        _lastPosition = {position.x(), position.y()};
        _clickFlag = true;
    }
}

void GameWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        _clickFlag = false;
    }
}

