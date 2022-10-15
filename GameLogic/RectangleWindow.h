#ifndef RectangleWindow_H
#define RectangleWindow_H

#include "../GameObjects/Puck.h"
#include "ShaderProgram.h"

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLWindow>
#include <QDebug>


class RectangleWindow : public QOpenGLWindow {
public:
	RectangleWindow();
    virtual ~RectangleWindow() override;

    void initializeGL() override;
    void paintGL() override;

private:
	QOpenGLVertexArrayObject	m_vao;
	QOpenGLBuffer				m_vertexBufferObject;
    QOpenGLBuffer				m_indexBufferObject;

    ShaderProgram _program;
};


#endif // RectangleWindow_H
