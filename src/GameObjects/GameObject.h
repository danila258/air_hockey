#ifndef GameObject_H
#define GameObject_H

#include "../GameLogic/Configuration.h"
#include "../GameLogic/ShaderProgram.h"

#include <QVector>
#include <QVector2D>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>


class GameObject
{
public:
    GameObject();
    GameObject(float x, float y, float dx, float dy, float radius, float numSegments, bool controlledFlag);
    GameObject(const QVector2D& center, const QVector2D& speed, float radius,  float numSegments, bool controlledFlag);

    virtual ~GameObject();

    virtual void create() = 0;
    virtual void render() = 0;
    void destroy();

    const QVector2D& getCenter() const;
    float getX() const;
    float getY() const;

    float getRadius() const;
    int getNumSegments() const;
    const QVector2D& getSpeed() const;

    void resetDifVector();

    void translate(const QVector2D& center);
    void translate(float x, float y);

    void setCenter(const QVector2D& center);
    void setCenter(float x, float y);

    void setSpeed(const QVector2D& speed);
    void setSpeed(float x, float y);
    void setSpeedX(float x);
    void setSpeedY(float y);

    void changeCenter(const QVector2D& center);
    void changeCenter(float x, float y);

    void changeSpeed(const QVector2D& speed);
    void changeSpeed(float x, float y);

protected:
    virtual QVector2D* const getVertexArray() = 0;
    virtual const int getVertexArrayByteSize() const = 0;
    const QMatrix4x4& getTransform();

    QOpenGLVertexArrayObject _vao;
    QOpenGLBuffer _vbo;
    ShaderProgram _program;
    int _vertexArrayByteSize;

    QVector<QVector2D> _vertexes;

    QMatrix4x4 _transform = {1.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 1.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 0.0f, 1.0f};

    QVector2D _center;
    QVector2D _speed;

    float _radius;
    float _numSegments;
    bool _controlledFlag;

    QVector2D _difVector;         // = newCenter - oldCenter
    bool _translateFlag = true;
};


#endif // GameObject_H
