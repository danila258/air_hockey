#include "GameWindow.h"

GameWindow::GameWindow()
{
    Bat* userBat = new Bat(USER_BAT_CENTER_X, USER_BAT_CENTER_Y, ZERO, ZERO, BAT_RADIUS, BAT_NUM_SEGMENTS, WALL_COLOR_2,
                           true);
    Bat* aiBat = new Bat(AI_BAT_CENTER_X, AI_BAT_CENTER_Y, ZERO, ZERO, BAT_RADIUS, BAT_NUM_SEGMENTS, WALL_COLOR_1,
                         true);
    Puck* puck = new Puck(PUCK_CENTER_X, PUCK_CENTER_Y, ZERO, ZERO, PUCK_RADIUS, PUCK_NUM_SEGMENTS, PUCK_COLOR,
                        false);

    _controlledObjects.push_back(userBat);
    _controlledObjects.push_back(aiBat);
    _freeObjects.push_back(puck);

    _inputHandler = new InputHandler(*userBat, *puck, width(), height());
    _gameRules = new GameRules(*userBat, *aiBat, *puck);

    Ring* topRightRounding = new Ring(MAX_X - WALL_OFFSET - WALL_WIDTH - WALL_ROUNDING_RADIUS,
                                      MAX_Y - WALL_OFFSET - WALL_WIDTH - WALL_ROUNDING_RADIUS,
                                      WALL_ROUNDING_RADIUS + WALL_WIDTH,
                                      WALL_ROUNDING_RADIUS,
                                      ZERO,
                                      0.25f,
                                      WALL_ROUNDING_NUM_SEGMENTS,
                                      WALL_COLOR_1);

    Ring* topLeftRounding = new Ring(MIN_X + WALL_OFFSET + WALL_WIDTH + WALL_ROUNDING_RADIUS,
                                     MAX_Y - WALL_OFFSET - WALL_WIDTH - WALL_ROUNDING_RADIUS,
                                     WALL_ROUNDING_RADIUS + WALL_WIDTH,
                                     WALL_ROUNDING_RADIUS,
                                     90.0f,
                                     0.25f,
                                     WALL_ROUNDING_NUM_SEGMENTS,
                                     WALL_COLOR_1);

    Ring* bottomLeftRounding = new Ring(MIN_X + WALL_OFFSET + WALL_WIDTH + WALL_ROUNDING_RADIUS,
                                        MIN_Y + WALL_OFFSET + WALL_WIDTH + WALL_ROUNDING_RADIUS,
                                        WALL_ROUNDING_RADIUS + WALL_WIDTH,
                                        WALL_ROUNDING_RADIUS,
                                        180.0f,
                                        0.25f,
                                        WALL_ROUNDING_NUM_SEGMENTS,
                                        WALL_COLOR_2);

    Ring* bottomRightRounding = new Ring(MAX_X - WALL_OFFSET - WALL_WIDTH - WALL_ROUNDING_RADIUS,
                                         MIN_Y + WALL_OFFSET + WALL_WIDTH + WALL_ROUNDING_RADIUS,
                                         WALL_ROUNDING_RADIUS + WALL_WIDTH,
                                         WALL_ROUNDING_RADIUS,
                                         270.f,
                                         0.25f,
                                         WALL_ROUNDING_NUM_SEGMENTS,
                                         WALL_COLOR_2);

    _decorations.push_back(topRightRounding);
    _decorations.push_back(topLeftRounding);
    _decorations.push_back(bottomLeftRounding);
    _decorations.push_back(bottomRightRounding);

    RoundedRectangle* topRightRectagle = new RoundedRectangle(MAX_X - WALL_OFFSET - WALL_WIDTH / 2.0f,
                                                              (MAX_Y - WALL_OFFSET - WALL_WIDTH - WALL_ROUNDING_RADIUS)
                                                              / 2.0f,
                                                              WALL_WIDTH,
                                                              MAX_Y - WALL_OFFSET - WALL_WIDTH - WALL_ROUNDING_RADIUS,
                                                              WALL_RECTANGLE_RADIUS,
                                                              WALL_RECTANGLE_ROUNDING_NUM_SEGMENTS,
                                                              WALL_COLOR_1);

    RoundedRectangle* bottomRightRectagle = new RoundedRectangle(MAX_X - WALL_OFFSET - WALL_WIDTH / 2.0f,
                                                                 (MIN_Y + WALL_OFFSET + WALL_WIDTH
                                                                 + WALL_ROUNDING_RADIUS) / 2.0f,
                                                                 WALL_WIDTH,
                                                                 MAX_Y - WALL_OFFSET - WALL_WIDTH
                                                                 - WALL_ROUNDING_RADIUS,
                                                                 WALL_RECTANGLE_RADIUS,
                                                                 WALL_RECTANGLE_ROUNDING_NUM_SEGMENTS,
                                                                 WALL_COLOR_2);

    RoundedRectangle* topLeftRectagle = new RoundedRectangle(MIN_X + WALL_OFFSET + WALL_WIDTH / 2.0f,
                                                             (MAX_Y - WALL_OFFSET - WALL_WIDTH - WALL_ROUNDING_RADIUS)
                                                             / 2.0f,
                                                             WALL_WIDTH,
                                                             MAX_Y - WALL_OFFSET - WALL_WIDTH - WALL_ROUNDING_RADIUS,
                                                             WALL_RECTANGLE_RADIUS,
                                                             WALL_RECTANGLE_ROUNDING_NUM_SEGMENTS,
                                                             WALL_COLOR_1);

    RoundedRectangle* bottomLeftRectagle = new RoundedRectangle(MIN_X + WALL_OFFSET + WALL_WIDTH / 2.0f,
                                                                (MIN_Y + WALL_OFFSET + WALL_WIDTH
                                                                + WALL_ROUNDING_RADIUS) / 2.0f,
                                                                WALL_WIDTH,
                                                                MAX_Y - WALL_OFFSET - WALL_WIDTH - WALL_ROUNDING_RADIUS,
                                                                WALL_RECTANGLE_RADIUS,
                                                                WALL_RECTANGLE_ROUNDING_NUM_SEGMENTS,
                                                                WALL_COLOR_2);

    _decorations.push_back(topRightRectagle);
    _decorations.push_back(bottomRightRectagle);
    _decorations.push_back(topLeftRectagle);
    _decorations.push_back(bottomLeftRectagle);

    RoundedRectangle* topRightRod = new RoundedRectangle((MAX_X + GATE_WIDTH / 2.0f - WALL_WIDTH - WALL_OFFSET
                                                          - WALL_ROUNDING_RADIUS) / 2.0f,
                                                         MAX_Y - WALL_OFFSET - WALL_WIDTH / 2.0f,
                                                         MAX_X - GATE_WIDTH / 2.0f - WALL_WIDTH - WALL_OFFSET
                                                         - WALL_ROUNDING_RADIUS,
                                                         WALL_WIDTH,
                                                         WALL_RECTANGLE_RADIUS,
                                                         WALL_RECTANGLE_ROUNDING_NUM_SEGMENTS,
                                                         WALL_COLOR_1);

    RoundedRectangle* topLeftRod = new RoundedRectangle((MIN_X - GATE_WIDTH / 2.0f + WALL_WIDTH + WALL_OFFSET
                                                        + WALL_ROUNDING_RADIUS) / 2.0f,
                                                        MAX_Y - WALL_OFFSET - WALL_WIDTH / 2.0f,
                                                        MAX_X - GATE_WIDTH / 2.0f - WALL_WIDTH - WALL_OFFSET
                                                        - WALL_ROUNDING_RADIUS,
                                                        WALL_WIDTH,
                                                        WALL_RECTANGLE_RADIUS,
                                                        WALL_RECTANGLE_ROUNDING_NUM_SEGMENTS,
                                                        WALL_COLOR_1);

    RoundedRectangle* bottomLeftRod = new RoundedRectangle((MIN_X - GATE_WIDTH / 2.0f + WALL_WIDTH + WALL_OFFSET
                                                           + WALL_ROUNDING_RADIUS) / 2.0f,
                                                           MIN_Y + WALL_OFFSET + WALL_WIDTH / 2.0f,
                                                           MAX_X - GATE_WIDTH / 2.0f - WALL_WIDTH - WALL_OFFSET
                                                           - WALL_ROUNDING_RADIUS,
                                                           WALL_WIDTH,
                                                           WALL_RECTANGLE_RADIUS,
                                                           WALL_RECTANGLE_ROUNDING_NUM_SEGMENTS,
                                                           WALL_COLOR_2);

    RoundedRectangle* bottomRightRod = new RoundedRectangle((MAX_X + GATE_WIDTH / 2.0f - WALL_WIDTH - WALL_OFFSET
                                                            - WALL_ROUNDING_RADIUS) / 2.0f,
                                                            MIN_Y + WALL_OFFSET + WALL_WIDTH / 2.0f,
                                                            MAX_X - GATE_WIDTH / 2.0f - WALL_WIDTH - WALL_OFFSET
                                                            - WALL_ROUNDING_RADIUS,
                                                            WALL_WIDTH,
                                                            WALL_RECTANGLE_RADIUS,
                                                            WALL_RECTANGLE_ROUNDING_NUM_SEGMENTS,
                                                            WALL_COLOR_2);

    _decorations.push_back(topRightRod);
    _decorations.push_back(topLeftRod);
    _decorations.push_back(bottomLeftRod);
    _decorations.push_back(bottomRightRod);

    Ring* BottomMarkingCircle = new Ring(ZERO,
                                         MIN_Y + WALL_OFFSET + WALL_WIDTH,
                                         GATE_WIDTH / 2.0f + MARKING_WIDTH + WALL_RECTANGLE_RADIUS,
                                         GATE_WIDTH / 2.0f + WALL_RECTANGLE_RADIUS,
                                         ZERO,
                                         0.5f,
                                         MARKING_CIRCLE_RADIUS_NUM_SEGMENTS,
                                         MARKING_COLOR);

    Ring* MiddleMarkingCircle = new Ring(ZERO,
                                         ZERO,
                                         GATE_WIDTH / 2.0f + MARKING_WIDTH + WALL_RECTANGLE_RADIUS,
                                         GATE_WIDTH / 2.0f + WALL_RECTANGLE_RADIUS,
                                         ZERO,
                                         1.0f,
                                         MARKING_CIRCLE_RADIUS_NUM_SEGMENTS,
                                         MARKING_COLOR);

    Ring* TopMarkingCircle = new Ring(ZERO,
                                      MAX_Y - WALL_OFFSET - WALL_WIDTH,
                                      GATE_WIDTH / 2.0f + MARKING_WIDTH + WALL_RECTANGLE_RADIUS,
                                      GATE_WIDTH / 2.0f + WALL_RECTANGLE_RADIUS,
                                      180.0f,
                                      0.5f,
                                      MARKING_CIRCLE_RADIUS_NUM_SEGMENTS,
                                      MARKING_COLOR);

    _decorations.push_back(BottomMarkingCircle);
    _decorations.push_back(MiddleMarkingCircle);
    _decorations.push_back(TopMarkingCircle);

    float offset = (MAX_X - WALL_OFFSET - WALL_WIDTH - (GATE_WIDTH / 2.0f + MARKING_WIDTH + WALL_RECTANGLE_RADIUS))
                   / 2.0f + MARKING_WIDTH / 2.0f;

    RoundedRectangle* LeftMarkingRectangle = new RoundedRectangle(MIN_X + WALL_OFFSET + WALL_WIDTH + offset,
                                                                  ZERO,
                                                                  MAX_X - WALL_OFFSET - WALL_WIDTH + MARKING_WIDTH
                                                                  - (GATE_WIDTH / 2.0f + MARKING_WIDTH
                                                                  + WALL_RECTANGLE_RADIUS),
                                                                  MARKING_WIDTH,
                                                                  0.01f,
                                                                  5,
                                                                  MARKING_COLOR);

    RoundedRectangle* RightMarkingRectangle = new RoundedRectangle(MAX_X - WALL_OFFSET - WALL_WIDTH - offset,
                                                                  ZERO,
                                                                  MAX_X - WALL_OFFSET - WALL_WIDTH + MARKING_WIDTH
                                                                  - (GATE_WIDTH / 2.0f + MARKING_WIDTH
                                                                  + WALL_RECTANGLE_RADIUS),
                                                                  MARKING_WIDTH,
                                                                  0.01f,
                                                                  5,
                                                                  MARKING_COLOR);

    _decorations.push_back(LeftMarkingRectangle);
    _decorations.push_back(RightMarkingRectangle);
}

GameWindow::~GameWindow()
{
	makeCurrent();

    for (auto&& object : _decorations)
    {
        delete object;
    }

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

    for (auto&& object : _decorations)
    {
        object->create();
    }
}


void GameWindow::paintGL()
{
    _inputHandler->updateUserBatPosition();
    _gameRules->applyGameRules();
    _physics.calulatePhysics();

    glClearColor(FIELD_COLOR);
    glClear(GL_COLOR_BUFFER_BIT);

    const qreal retinaScale = devicePixelRatio();                       // needed for Macs with retina display
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    for (auto&& object : _decorations)
    {
        object->render();
    }

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
