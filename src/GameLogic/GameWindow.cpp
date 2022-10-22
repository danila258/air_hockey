#include "GameWindow.h"

GameWindow::GameWindow() :
    _program(QString::fromStdString(":/Shaders/pass_through.vert"), QString::fromStdString(":/Shaders/simple.frag")),
    _userBat(USER_BAT_CENTER_X, USER_BAT_CENTER_Y, ZERO, ZERO, USER_BAT_RADIUS, USER_BAT_NUM_SEGMENTS)
{}

GameWindow::~GameWindow()
{
	makeCurrent();

    _vao.destroy();
    _vbo.destroy();
}

void GameWindow::initializeGL()
{    
    _program.create();

    _vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    _vbo.create();
    _vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    _vbo.bind();

    _vbo.allocate(_userBat.getVertexArray(), _userBat.getVertexArrayByteSize());

    _vao.create();
    _vao.bind();

    _program.getShaderProgram()->enableAttributeArray(0);
    _program.getShaderProgram()->setAttributeBuffer(0, GL_FLOAT, 0, 2);
}


void GameWindow::paintGL()
{
    _physics.calulatePhysics();

    glClearColor(0.4f, 0.3f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

    const qreal retinaScale = devicePixelRatio(); // needed for Macs with retina display
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

	// use our shader program
    _program.getShaderProgram()->bind();
    _program.getShaderProgram()->setUniformValue("transform", _userBat.getTransform());

	// bind the vertex array object, which in turn binds the vertex buffer object and
	// sets the attribute buffer in the OpenGL context
    _vao.bind();
	// For old Intel drivers you may need to explicitely re-bind the index buffer, because
	// these drivers do not remember the binding-state of the index/element-buffer in the VAO
	//	m_indexBufferObject.bind();

	// now draw the two triangles via index drawing
	// - GL_TRIANGLES - draw individual triangles via elements
    glDrawArrays(GL_TRIANGLE_FAN, 0, 100);
    // finally release VAO again (not really necessary, just for completeness)
    _vao.release();

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
    qDebug() << "get event";

    _userBat.changeCenter(position - _lastPosition);
    _lastPosition = position;
}

void GameWindow::mousePressEvent(QMouseEvent* event)
{
    QVector2D position( event->position().rx(), event->position().ry() );
    toGlCoordinates(position);

    if (!(_userBat.getX() - _userBat.getRadius() <= position.x() &&
          position.x() <= _userBat.getX() + _userBat.getRadius() &&
          _userBat.getY() - _userBat.getRadius() <= position.y() &&
          position.y() <= _userBat.getY() + _userBat.getRadius()))
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

