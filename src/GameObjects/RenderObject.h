#ifndef RenderObject_H
#define RenderObject_H

#include "../GameLogic/ShaderProgram.h"

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QVector>
#include <QMatrix4x4>
#include <QVector2D>


class RenderObject
{
public:
    RenderObject() = delete;
    RenderObject(float numSegments) : _numSegments(numSegments) {};

    virtual void create() = 0;
    virtual void render() = 0;

    void destroy()
    {
        _vao.destroy();
        _vbo.destroy();
    }

protected:
    virtual QVector2D* const getVertexArray() = 0;
    virtual const QMatrix4x4& getTransform() = 0;
    virtual int getVertexArrayByteSize() const = 0;

    QOpenGLVertexArrayObject _vao;
    QOpenGLBuffer _vbo;
    ShaderProgram _program;

    QVector<QVector2D> _vertexes;
    float _numSegments;

    QMatrix4x4 _transform = {1.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 1.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 0.0f, 1.0f};
};


#endif // RenderObject_H
