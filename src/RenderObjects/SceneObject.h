#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "../GameLogic/Configuration.h"

#include <QVector2D>


class SceneObject
{
public:
    SceneObject();
    SceneObject(float x, float y, float width, float height, float radius = ZERO);
    SceneObject(const QVector2D& center, const QVector2D& dimension, float radius = ZERO);

    virtual ~SceneObject() = default;

    virtual void render() = 0;
    virtual void create() = 0;
    virtual void destroy() = 0;

    virtual void translate(const QVector2D& center) = 0;

    const QVector2D& center() const;
    float x() const;
    float y() const;

    const QVector2D& dimension() const;
    float width() const;
    float height() const;

    float radius() const;

protected:
    QVector2D _center;
    QVector2D _dimension;

    float _radius;
};


#endif // SCENEOBJECT_H
