#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <QOpenGLShaderProgram>
#include <QString>
#include <QDebug>


class ShaderProgram
{
public:
    ShaderProgram() = default;
    ShaderProgram(const QString& vertexShaderFilePath, const QString& fragmentShaderFilePath);

    ~ShaderProgram();

    void setShaderPath(const QString& vertexShaderFilePath, const QString& fragmentShaderFilePath);

	void create();
    void bind();
	void destroy();

    QOpenGLShaderProgram* getShaderProgram();

private:
    QOpenGLShaderProgram* _program;

    QString _vertexShaderFilePath;
    QString _fragmentShaderFilePath;
};


#endif // SHADERPROGRAM_H
