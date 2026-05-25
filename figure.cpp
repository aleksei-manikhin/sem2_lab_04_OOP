#include "figure.h"

#include <stdexcept>
#include <utility>

Figure::Figure(std::vector<Vertex> vertices, int rowCount, int columnCount)
    : vertices(std::move(vertices)) {
    ValidateGridSize(rowCount, columnCount);
    CreateEdges(rowCount, columnCount);
}

const std::vector<Vertex>& Figure::GetVertices() const {
    return vertices;
}

const std::vector<Edge>& Figure::GetEdges() const {
    return edges;
}

void Figure::Transform(const TransformMatrix& matrix) {
    for (Vertex& vertex : vertices) {
        vertex.Transform(matrix);
    }
}

void Figure::CreateEdges(int rowCount, int columnCount) {
    const int horizontalEdgeCount = rowCount * (columnCount - 1);
    const int verticalEdgeCount = (rowCount - 1) * columnCount;
    edges.reserve(horizontalEdgeCount + verticalEdgeCount);

    for (int row = 0; row < rowCount; row++) {
        for (int column = 0; column < columnCount; column++) {
            const int currentIndex = row * columnCount + column;

            if (column + 1 < columnCount) {
                edges.emplace_back(vertices[currentIndex], vertices[currentIndex + 1]);
            }

            if (row + 1 < rowCount) {
                edges.emplace_back(vertices[currentIndex], vertices[currentIndex + columnCount]);
            }
        }
    }
}

void Figure::ValidateGridSize(int rowCount, int columnCount) const {
    if (rowCount <= 0 || columnCount <= 0) {
        throw std::invalid_argument("Figure grid size must be positive");
    }

    if (vertices.size() != static_cast<std::size_t>(rowCount * columnCount)) {
        throw std::invalid_argument("Figure vertex count does not match grid size");
    }
}
