#ifndef GameObject_H
#define GameObject_H

#include "../GameLogic/Configuration.h"
#include "RenderObject.h"


class GameObject : public RenderObject
{
public:
    GameObject();
    GameObject(float x, float y, float dx, float dy, float radius, float numSegments, bool controlledFlag);
    GameObject(const QVector2D& center, const QVector2D& speed, float radius,  float numSegments, bool controlledFlag);

    virtual ~GameObject();

    void create() override = 0;
    void render() override = 0;

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
    virtual QVector2D* const getVertexArray() override = 0;
    virtual int getVertexArrayByteSize() const override = 0;
    const QMatrix4x4& getTransform() override;

    QVector2D _center;
    QVector2D _speed;

    float _radius;
    bool _controlledFlag;

    QVector2D _difVector;         // = newCenter - oldCenter
    bool _translateFlag = true;
};


#endif // GameObject_H
