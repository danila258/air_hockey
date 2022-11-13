#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "SceneObject.h"
#include "ShaderProgram.h"

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QVector>
#include <QMatrix4x4>
#include <QColor>


class RenderObject : public SceneObject
{
public:
    RenderObject() = default;
    RenderObject(float x, float y, float width, float height, float radius = ZERO);
    RenderObject(const QVector2D& center, const QVector2D& dimension, float radius = ZERO);

    ~RenderObject() override;

    void create() override;
    void render() override;
    void destroy() override;

    void translate(const QVector2D& center) override;

protected:
    void setupRenderObject();

    virtual void setVertexArray() = 0;
    virtual void setVertexArrayByteSize() = 0;

    QVector<QVector2D> _vertexArray;
    int _vertexArrayByteSize;

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
