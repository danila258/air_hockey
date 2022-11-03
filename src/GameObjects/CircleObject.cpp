#include "CircleObject.h"

CircleObject::CircleObject() : GameObject()
{}

CircleObject::CircleObject(float x, float y, float dx, float dy, float radius, float numSegments, bool controlledFlag) :
    GameObject(x, y, dx, dy, radius, numSegments, controlledFlag)
{}

CircleObject::CircleObject(const QVector2D& center, const QVector2D& speed, float radius, float numSegments,
                           bool controlledFlag) :
    GameObject(center, speed, radius, numSegments, controlledFlag)
{}

QVector2D* const CircleObject::getVertexArray()
{
    for(int i = 0; i < _numSegments; ++i)
    {
        float theta = 2.0f * PI * float(i) / float(_numSegments);
        float x = _radius * cos(theta);
        float y = _radius * sin(theta);

        _vertexes.emplace_back(x, y);
    }

    return _vertexes.data();
}

int CircleObject::getVertexArrayByteSize() const
{
    return _numSegments * 2 * sizeof(float);
}

void CircleObject::create()
{
    int vertexArrayByteSize = getVertexArrayByteSize();

    _vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    _vbo.create();
    _vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    _vbo.bind();

    _vbo.allocate(getVertexArray(), vertexArrayByteSize);

    _vao.create();
    _vao.bind();

    _program.setShaderPath(":/Shaders/pass_through.vert", ":/Shaders/simple.frag");
    _program.create();
    _program.getShaderProgram()->enableAttributeArray(0);
    _program.getShaderProgram()->setAttributeBuffer(0, GL_FLOAT, 0, 2);

    _vao.release();
    _vbo.release();
}

void CircleObject::render()
{
    _program.getShaderProgram()->bind();
    _program.getShaderProgram()->setUniformValue("transform", getTransform());

    _vao.bind();

    glDrawArrays(GL_TRIANGLE_FAN, 0, getVertexArrayByteSize());

    _vao.release();
}
