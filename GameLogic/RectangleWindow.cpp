#include "RectangleWindow.h"

RectangleWindow::RectangleWindow() :
    _program(QString::fromStdString(":/Shaders/pass_through.vert"),
             QString::fromStdString(":/Shaders/simple.frag"))
{}

RectangleWindow::~RectangleWindow()
{
	makeCurrent();

	m_vao.destroy();
	m_vertexBufferObject.destroy();
	m_indexBufferObject.destroy();
}

void RectangleWindow::initializeGL()
{    
    _program.create();
    Puck userPuck(0, 0, 0, 0, 0.5, 20);

	m_vertexBufferObject = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	m_vertexBufferObject.create();
	m_vertexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);
	m_vertexBufferObject.bind();

    m_vertexBufferObject.allocate(userPuck.getVertexArray(), userPuck.getVertexArrayByteSize());

	m_vao.create();
	m_vao.bind();

    _program.getShaderProgram()->enableAttributeArray(0);
    _program.getShaderProgram()->setAttributeBuffer(0, GL_FLOAT, 0, 2);
}


void RectangleWindow::paintGL() {
    glClearColor(0.4f, 0.3f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

    const qreal retinaScale = devicePixelRatio(); // needed for Macs with retina display
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

	// use our shader program
    _program.getShaderProgram()->bind();
	// bind the vertex array object, which in turn binds the vertex buffer object and
	// sets the attribute buffer in the OpenGL context
	m_vao.bind();
	// For old Intel drivers you may need to explicitely re-bind the index buffer, because
	// these drivers do not remember the binding-state of the index/element-buffer in the VAO
	//	m_indexBufferObject.bind();

	// now draw the two triangles via index drawing
	// - GL_TRIANGLES - draw individual triangles via elements
    glColor3f(0.4f, 0.3f, 0.3f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 100);
    // finally release VAO again (not really necessary, just for completeness)
	m_vao.release();
}
