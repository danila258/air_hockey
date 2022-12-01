#ifndef BAT_H
#define BAT_H

#include "GameObject.h"
#include "../RenderObjects/Circle.h"


class Bat : public GameObject
{
public:
    Bat();
    Bat(float x, float y, float dx, float dy, float radius, float numSegments, const QVector3D& color,
        bool controlledFlag);
    Bat(const QVector2D& center, const QVector2D& speed, float radius, float numSegments, const QVector3D& color,
        bool controlledFlag);

    ~Bat() override = default;

    void create() override;
    void render() override;

private:
    void setupSceneObjects();
    void customTransformations();
};


#endif // BAT_H
