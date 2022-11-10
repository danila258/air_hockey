#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "../GameLogic/Configuration.h"
#include "RenderObject.h"


class SceneObject : public RenderObject
{
public:
    SceneObject();
    SceneObject(float x, float y, float width, float height, float radius, float numSegments);
    SceneObject(const QVector2D& center, const QVector2D& dimension, float radius,  float numSegments);

protected:
    void setupRenderObject();

    virtual void setVertexArray() = 0;
    virtual void setVertexArrayByteSize() = 0;

    QVector2D _center;

    float _width;
    float _height;
    float _radius;
    float _numSegments;
};


#endif // SCENEOBJECT_H
