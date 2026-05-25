#ifndef FIGURE_H
#define FIGURE_H

#include "edge.h"
#include "sceneObject.h"
#include "vertex.h"

#include <cstddef>
#include <utility>
#include <vector>

class Figure : public SceneObject {
private:
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;

    void CreateEdges(std::size_t rowCount, std::size_t columnCount);
    void CreateEdges(const std::vector<std::pair<std::size_t, std::size_t>>& edgeIndexes);
    void ValidateGridSize(std::size_t rowCount, std::size_t columnCount) const;
    void ValidateEdgeIndex(std::size_t index) const;

public:
    Figure(std::vector<Vertex> vertices, std::size_t rowCount, std::size_t columnCount);
    Figure(std::vector<Vertex> vertices,
           const std::vector<std::pair<std::size_t, std::size_t>>& edgeIndexes);

    Figure(const Figure& figure) = delete;
    Figure& operator=(const Figure& figure) = delete;
    Figure(Figure&& figure) noexcept = default;
    Figure& operator=(Figure&& figure) noexcept = default;

    const std::vector<Vertex>& GetVertices() const;
    const std::vector<Edge>& GetEdges() const;
    void Transform(const TransformMatrix& matrix) override;
};

#endif // FIGURE_H
