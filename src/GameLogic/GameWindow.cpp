#include "GameWindow.h"

GameWindow::GameWindow() :
    _program(QString::fromStdString(":/Shaders/pass_through.vert"), QString::fromStdString(":/Shaders/simple.frag")),
    _userPuck(0, 0, 0, 0, 0.12, 30)
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

    _vbo.allocate(_userPuck.getVertexArray(), _userPuck.getVertexArrayByteSize());

    _vao.create();
    _vao.bind();

    _program.getShaderProgram()->enableAttributeArray(0);
    _program.getShaderProgram()->setAttributeBuffer(0, GL_FLOAT, 0, 2);

    _userPuck.changeCenter(0.2, 0.2);
}


void GameWindow::paintGL()
{
    glClearColor(0.4f, 0.3f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

    const qreal retinaScale = devicePixelRatio(); // needed for Macs with retina display
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

	// use our shader program
    _program.getShaderProgram()->bind();
    _program.getShaderProgram()->setUniformValue("transform", _userPuck.getTransform());

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

    calculatePhysics();
}

void GameWindow::calculatePhysics()
{
    update();
}

void GameWindow::mouseMoveEvent(QMouseEvent* event)
{
    float x = event->position().rx();
    float y = event->position().ry();

    x = (x - width() / 2) / (width() / 2);
    y = - (y - height() / 2) / (height() / 2);

    _userPuck.setCenter(x, y);
}
