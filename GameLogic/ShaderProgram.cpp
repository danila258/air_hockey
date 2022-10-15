#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const QString& vertexShaderFilePath, const QString& fragmentShaderFilePath) :
    _vertexShaderFilePath(vertexShaderFilePath),
    _fragmentShaderFilePath(fragmentShaderFilePath),
    _program(nullptr)
{}

void ShaderProgram::create()
{
    Q_ASSERT(_program == nullptr);

    _program = new QOpenGLShaderProgram();

    if (!_program->addShaderFromSourceFile(QOpenGLShader::Vertex, _vertexShaderFilePath))
    {
        qDebug() << "Vertex shader errors:\n" << _program->log();
    }

    if (!_program->addShaderFromSourceFile(QOpenGLShader::Fragment, _fragmentShaderFilePath))
    {
        qDebug() << "Fragment shader errors:\n" << _program->log();
    }

    if (!_program->link())
    {
        qDebug() << "Shader linker errors:\n" << _program->log();
    }
}

void ShaderProgram::bind()
{
    Q_ASSERT(_program == nullptr);

    _program->bind();
}

void ShaderProgram::destroy()
{
    delete _program;
    _program = nullptr;
}

QOpenGLShaderProgram* ShaderProgram::getShaderProgram()
{
    return _program;
}

