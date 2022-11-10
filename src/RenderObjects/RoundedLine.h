#ifndef ROUNDEDLINE_H
#define ROUNDEDLINE_H

#include "../GameObjects/RenderObject.h"
#include "../GameLogic/Configuration.h"


class RoundedLine : public RenderObject
{
public:
    RoundedLine();
    RoundedLine(const QVector2D& center, float width, float height, float roundingRadius, float roundingNumSegments);

    void create() override;
    void render() override;

    const QMatrix4x4& getTransform() override;

private:
    QVector2D* const getCircleVertexArray();
    //QVector2D* const getRectangleVertexArray();

    int getCircleVertexArrayByteSize() const;
    //int getRectangleVertexArrayByteSize() const;

    void renderObject(int vaoIndex);

    QVector2D _center;
    float _width;
    float _height;
    float _roundingRadius;
    float _roundingNumSegments;
};


#endif // ROUNDEDLINE_H
