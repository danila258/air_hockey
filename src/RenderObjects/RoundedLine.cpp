#include "RoundedLine.h"

RoundedLine::RoundedLine() : _center(ZERO, ZERO), _width(0.5f), _height(0.25f), _roundingRadius(0.1f), _roundingNumSegments(3)
{}

RoundedLine::RoundedLine(const QVector2D& center, float width, float height, float roundingRadius, float roundingNumSegments)
    : _center(center), _width(width), _height(height), _roundingRadius(roundingRadius), _roundingNumSegments(roundingNumSegments)
{}

void RoundedLine::create()
{
    int vertexArrayByteSize = getCircleVertexArrayByteSize();

    // first circle
    QOpenGLVertexArrayObject* vao = new QOpenGLVertexArrayObject();
    QOpenGLBuffer* vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    _vao.push_back(vao);
    _vbo.push_back(vbo);

    vbo->create();
    vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo->bind();

    vbo->allocate(getCircleVertexArray(), vertexArrayByteSize);

    vao->create();
    vao->bind();

    _program.setShaderPath(":/Shaders/pass_through.vert", ":/Shaders/simple.frag");
    _program.create();
    _program.getShaderProgram()->enableAttributeArray(0);
    _program.getShaderProgram()->setAttributeBuffer(0, GL_FLOAT, 0, 2);

    vao->release();
    vbo->release();

    _transform.translate(_width / 2.0f - _roundingRadius, _height / 2.0f - _roundingRadius, ZERO);
    _transform.rotate(180.0f, {ZERO, 1.0f, ZERO});
    _transform.rotate(180.0f, {1.0f, ZERO, ZERO});
    _transform.rotate(180.0f, {ZERO, 1.0f, ZERO});
    _transform.rotate(180.0f, {1.0f, ZERO, ZERO});


    qDebug() << QVector2D(_width / 2.0f - _roundingRadius, _height / 2.0f - _roundingRadius);
}

void RoundedLine::render()
{
    _program.getShaderProgram()->bind();

    // right top corner
    _program.getShaderProgram()->setUniformValue("transform", getTransform());

    _vao[0]->bind();

    glDrawArrays(GL_TRIANGLE_FAN, 0, getCircleVertexArrayByteSize());

    _vao[0]->release();

    // left top corner
//    _transform.rotate(180.0f, {ZERO, 1.0f, ZERO});
//    _transform.translate(-_width + 2.0f * _roundingRadius, ZERO, ZERO);
//    _program.getShaderProgram()->setUniformValue("transform", getTransform());

//    _vao[0]->bind();

//    glDrawArrays(GL_TRIANGLE_FAN, 0, getCircleVertexArrayByteSize());

//    _vao[0]->release();

    // left bottom corner
//    _transform.rotate(180.0f, {1.0f, ZERO, ZERO});
//    _transform.translate(ZERO, -_height + 2.0f * _roundingRadius, ZERO);
//    _program.getShaderProgram()->setUniformValue("transform", getTransform());

//    _vao[0]->bind();

//    glDrawArrays(GL_TRIANGLE_FAN, 0, getCircleVertexArrayByteSize());

//    _vao[0]->release();

    // right bottom corner
//    _transform.rotate(180.0f, {ZERO, 1.0f, ZERO});
//    _transform.translate(_width - 2.0f * _roundingRadius, ZERO, ZERO);
//    _program.getShaderProgram()->setUniformValue("transform", getTransform());

//    _vao[0]->bind();

//    glDrawArrays(GL_TRIANGLE_FAN, 0, getCircleVertexArrayByteSize());

//    _vao[0]->release();

    // set start position
//    _transform.rotate(180.0f, {1.0f, ZERO, ZERO});
//    _transform.translate({ZERO, _height - 2.0f * _roundingRadius, ZERO});
}

QVector2D* const RoundedLine::getCircleVertexArray(float rotationAngle, float fractionOfCircle)
{
    for(int i = 0; i < _roundingNumSegments; ++i)
    {
        float theta = (angle / 180.0f) * PI + shareCircle * PI * float(i) / float(_roundingNumSegments);
        float x = _roundingRadius * cos(theta);
        float y = _roundingRadius * sin(theta);

        _vertexes.emplace_back(x, y);
    }

    return _vertexes.data();
}

const QMatrix4x4& RoundedLine::getTransform()
{
    return _transform;
}

int RoundedLine::getCircleVertexArrayByteSize() const
{
    return _roundingNumSegments * 2 * sizeof(float);
}
