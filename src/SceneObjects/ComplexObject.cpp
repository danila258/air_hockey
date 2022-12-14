#include "ComplexObject.h"

ComplexObject::ComplexObject() : SceneObject()
{}

ComplexObject::ComplexObject(float x, float y, float width, float height, float radius, const QVector3D& color)
    : SceneObject(x, y, width, height, radius, color)

{}

ComplexObject::ComplexObject(const QVector2D& center, const QVector2D& dimension, float radius, const QVector3D& color)
    : SceneObject(center, dimension, radius, color)
{}

ComplexObject::~ComplexObject()
{
    for (auto&& item : _sceneObjects)
    {
        delete item;
    }
}

void ComplexObject::render()
{
    for (auto&& item : _sceneObjects)
    {
        item->render();
    }
}

void ComplexObject::create()
{
    for (auto& item : _sceneObjects)
    {
        item->create();
    }
}

void ComplexObject::destroy()
{
    for (auto& item : _sceneObjects)
    {
        item->destroy();
    }
}

void ComplexObject::translate(const QVector2D& center)
{
    _center += _center;

    for (auto& item : _sceneObjects)
    {
        item->translate(center);
    }
}
