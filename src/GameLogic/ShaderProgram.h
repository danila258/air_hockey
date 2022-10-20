#ifndef ShaderProgram_H
#define ShaderProgram_H

#include <QOpenGLShaderProgram>
#include <QString>
#include <QDebug>


class ShaderProgram
{
public:
	ShaderProgram();
    ShaderProgram(const QString& vertexShaderFilePath, const QString& fragmentShaderFilePath);

	void create();
    void bind();
	void destroy();

    QOpenGLShaderProgram* getShaderProgram();

private:
    QOpenGLShaderProgram* _program;

    QString _vertexShaderFilePath;
    QString _fragmentShaderFilePath;
};


#endif // ShaderProgram_H
