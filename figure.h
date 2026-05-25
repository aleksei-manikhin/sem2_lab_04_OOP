#ifndef FIGURE_H
#define FIGURE_H

#include "edge.h"
#include "sceneObject.h"
#include "vertex.h"

#include <utility>
#include <vector>

class Figure : public SceneObject {
private:
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;

    void CreateEdges(int rowCount, int columnCount);
    void CreateEdges(const std::vector<std::pair<int, int>>& edgeIndexes);
    void ValidateGridSize(int rowCount, int columnCount) const;
    void ValidateEdgeIndex(int index) const;

public:
    Figure(std::vector<Vertex> vertices, int rowCount, int columnCount);
    Figure(std::vector<Vertex> vertices, const std::vector<std::pair<int, int>>& edgeIndexes);

    Figure(const Figure& figure) = delete;
    Figure& operator=(const Figure& figure) = delete;
    Figure(Figure&& figure) noexcept = default;
    Figure& operator=(Figure&& figure) noexcept = default;

    const std::vector<Vertex>& GetVertices() const;
    const std::vector<Edge>& GetEdges() const;
    void Transform(const TransformMatrix& matrix) override;
};

#endif // FIGURE_H
