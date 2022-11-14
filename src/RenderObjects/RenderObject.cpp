#include "RenderObject.h"

RenderObject::RenderObject(const QVector2D& center, const QVector2D& dimension, float radius)
    : SceneObject(center, dimension, radius)
{}

RenderObject::RenderObject(float x, float y, float width, float height, float radius)
    : SceneObject(x, y, width, height, radius)
{}

RenderObject::~RenderObject()
{
    destroy();      // that is right

    delete _vbo;
    _vbo = nullptr;
};

void RenderObject::create()
{
    _vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);

    _vbo->create();
    _vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    _vbo->bind();

    if (_vertexArrayByteSize == 0)
    {
        throw std::logic_error("_vertexArrayByteSize == 0 in create method");
    }

    _vbo->allocate(_vertexArray.data(), _vertexArrayByteSize);

    _vao.create();
    _vao.bind();

    _program.setShaderPath(":/Shaders/pass_through.vert", ":/Shaders/simple.frag");
    _program.create();
    _program.getShaderProgram()->enableAttributeArray(0);
    _program.getShaderProgram()->setAttributeBuffer(0, GL_FLOAT, 0, 2);

    _vao.release();
    _vbo->release();

    _createdFlag = true;
}

void RenderObject::render()
{
    if (!_createdFlag)
    {
        throw std::logic_error("not create renderObject");
    }

    _program.getShaderProgram()->bind();
    _program.getShaderProgram()->setUniformValue("transform", _transform);

    _vao.bind();

    glDrawArrays(GL_TRIANGLE_FAN, 0, _vertexArrayByteSize);

    _vao.release();
    _program.getShaderProgram()->release();
}

void RenderObject::destroy()
{
    _vao.destroy();
    _vbo->destroy();
    _program.destroy();
}

void RenderObject::translate(const QVector2D& center)
{
    _center += center;
    _transform.translate(center.x(), center.y());
}

void RenderObject::setupRenderObject()
{
    userInputCheck();
    setVertexArray();
    setVertexArrayByteSize();
}
