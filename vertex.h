#ifndef VERTEX_H
#define VERTEX_H

#include "point3D.h"
#include "sceneObject.h"

class Vertex : public SceneObject {
private:
    Point3D position;

public:
    explicit Vertex(const Point3D& position);
    Vertex(float x, float y, float z);

    Point3D GetPosition() const;
    void Transform(const TransformMatrix& matrix) override;
};

#endif // VERTEX_H
