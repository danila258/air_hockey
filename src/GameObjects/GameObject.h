#ifndef GameObject_H
#define GameObject_H

#include <QVector>
#include <QVector2D>
#include <QMatrix4x4>


class GameObject
{
public:
    GameObject();
    GameObject(float x, float y, float dx, float dy, float radius, float numSegments);
    GameObject(const QVector2D& center, const QVector2D& speed, float radius,  float numSegments);

    virtual ~GameObject() = default;

    virtual QVector2D* const getVertexArray() = 0;
    virtual int getVertexArrayByteSize() = 0;

    const QMatrix4x4& getTransform();

    const QVector2D& getCenter();
    const int getX();
    const int getY();

    int getRadius();
    int getNumSegments();
    const QVector2D& getSpeed();

    void translate(const QVector2D& center);
    void translate(float x, float y);

    void setCenter(const QVector2D& center);
    void setCenter(float x, float y);

    void setSpeed(const QVector2D& speed);
    void setSpeed(float x, float y);

    void changeCenter(const QVector2D& center);
    void changeCenter(float x, float y);

    void changeSpeed(const QVector2D& speed);
    void changeSpeed(float x, float y);

protected:
    QVector<QVector2D> _vertexes;

    QMatrix4x4 _transform = {1.0, 0.0, 0.0, 0.0,
                             0.0, 1.0, 0.0, 0.0,
                             0.0, 0.0, 0.0, 0.0,
                             0.0, 0.0, 0.0, 1.0};

    bool _translateFlag = true;

    QVector2D _center;
    QVector2D _speed;

    QVector2D _difCenter;   // = newCenter - oldCenter

    float _radius;
    float _numSegments;
};


#endif // GameObject_H
