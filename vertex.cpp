#include "vertex.h"

Vertex::Vertex(const Point3D& position)
    : position(position) {}

Vertex::Vertex(float x, float y, float z)
    : position(x, y, z) {}

Point3D Vertex::GetPosition() const {
    return position;
}

void Vertex::Transform(const TransformMatrix& matrix) {
    position = matrix.TransformPoint(position);
}
