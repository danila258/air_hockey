#include "RenderObject.h"

RenderObject::~RenderObject()
{
    destroy();
};

void RenderObject::create()
{
    _vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);

    _vbo->create();
    _vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    _vbo->bind();

    if (_vertexArrayByteSize != 0)
    {
        _vbo->allocate(_vertexArray.data(), _vertexArrayByteSize);
    }
    else
    {
        throw std::logic_error("_vertexArrayByteSize == 0");
    }

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
    _program.getShaderProgram()->setUniformValue("transform", getTransform());

    _vao.bind();

    glDrawArrays(GL_TRIANGLE_FAN, 0, _vertexArrayByteSize);

    _vao.release();
}

void RenderObject::destroy()
{
    _vao.destroy();
    _vbo->destroy();
    _program.destroy();
}

const QMatrix4x4& RenderObject::getTransform()
{
    return _transform;
}

const void RenderObject::translate(float x, float y)
{
    _transform.translate(x, y);
}

const void RenderObject::translate(const QVector2D& center)
{
    translate(center.x(), center.y());
}

const void RenderObject::resetTranslate()
{
    translate(ZERO, ZERO);
}
