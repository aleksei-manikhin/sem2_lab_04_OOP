#ifndef FIGURE_H
#define FIGURE_H

#include "edge.h"
#include "sceneObject.h"
#include "vertex.h"

#include <vector>

class Figure : public SceneObject {
private:
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;

    void CreateEdges(int rowCount, int columnCount);
    void ValidateGridSize(int rowCount, int columnCount) const;

public:
    Figure(std::vector<Vertex> vertices, int rowCount, int columnCount);

    Figure(const Figure& figure) = delete;
    Figure& operator=(const Figure& figure) = delete;
    Figure(Figure&& figure) noexcept = default;
    Figure& operator=(Figure&& figure) noexcept = default;

    const std::vector<Vertex>& GetVertices() const;
    const std::vector<Edge>& GetEdges() const;
    void Transform(const TransformMatrix& matrix) override;
};

#endif // FIGURE_H
