#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../GameLogic/Configuration.h"

#include <QVector2D>


class GameObject
{
public:
    GameObject();
    GameObject(float x, float y, float dx, float dy, float radius, float numSegments, bool controlledFlag);
    GameObject(const QVector2D& center, const QVector2D& speed, float radius,  float numSegments, bool controlledFlag);

    virtual ~GameObject();

    virtual void create() = 0;
    virtual void render() = 0;

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
    QVector2D _center;
    QVector2D _speed;

    float _width;
    float _height;
    float _radius;
    float _numSegments;

    bool _userControllFlag;

    QVector2D _difVector;         // = newCenter - oldCenter
    bool _translateFlag = true;
};


#endif // GAMEOBJECT_H
