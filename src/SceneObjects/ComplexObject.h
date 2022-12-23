#ifndef COMPLEXOBJECT_H
#define COMPLEXOBJECT_H

#include "SceneObject.h"

#include <QVector>


class ComplexObject : public SceneObject
{
public:
    ComplexObject();
    ComplexObject(float x, float y, float width, float height, float radius = ZERO,
                  const QVector3D& color = {1.0f, 1.0f, 1.0f});
    ComplexObject(const QVector2D& center, const QVector2D& dimension, float radius = ZERO,
                  const QVector3D& color = {1.0f, 1.0f, 1.0f});

    ~ComplexObject();

    void render() override;
    void create() override;
    void destroy() override;

    void translate(const QVector2D& center) override;

protected:
    QVector<SceneObject*> _sceneObjects;
};


#endif // COMPLEXOBJECT_H
