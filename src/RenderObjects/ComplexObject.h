#ifndef COMPLEXOBJECT_H
#define COMPLEXOBJECT_H

#include "SceneObject.h"

#include <QVector>


class ComplexObject : public SceneObject
{
public:
    ComplexObject();
    ComplexObject(float x, float y, float width, float height, float radius = ZERO);
    ComplexObject(const QVector2D& center, const QVector2D& dimension, float radius = ZERO);

    ~ComplexObject() override;

    void render() override;
    void create() override;
    void destroy() override;

    void translate(const QVector2D& center) override;

protected:
    QVector<SceneObject*> _sceneObjects;
};


#endif // COMPLEXOBJECT_H
