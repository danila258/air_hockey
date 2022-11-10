#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "GameLogic/Configuration.h"
#include "../GameLogic/ShaderProgram.h"

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QVector>
#include <QVector2D>
#include <QMatrix4x4>
#include <QColor>


class RenderObject
{
public:
    RenderObject() = default;

    virtual ~RenderObject();

    void create();
    void render();
    void destroy();

    const QMatrix4x4& getTransform();

    const void translate(float x, float y);
    const void translate(const QVector2D& center);
    const void resetTranslate();

protected:
    QVector<QVector2D> _vertexArray;
    int _vertexArrayByteSize = 0;
    QColor _color;

private:
    QOpenGLVertexArrayObject _vao;
    QOpenGLBuffer* _vbo;
    ShaderProgram _program;

    QMatrix4x4 _transform = {1.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 1.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 0.0f, 1.0f};

    bool _createdFlag = false;
};


#endif // RENDEROBJECT_H
