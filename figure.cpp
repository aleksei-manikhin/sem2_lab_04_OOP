#include "figure.h"

#include <stdexcept>
#include <utility>

Figure::Figure(std::vector<Vertex> vertices, std::size_t rowCount, std::size_t columnCount)
    : vertices(std::move(vertices)) {
    ValidateGridSize(rowCount, columnCount);
    CreateEdges(rowCount, columnCount);
}

Figure::Figure(std::vector<Vertex> vertices,
               const std::vector<std::pair<std::size_t, std::size_t>>& edgeIndexes)
    : vertices(std::move(vertices)) {
    if (this->vertices.empty()) {
        throw std::invalid_argument("Figure must contain at least one vertex");
    }

    CreateEdges(edgeIndexes);
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

void Figure::CreateEdges(std::size_t rowCount, std::size_t columnCount) {
    const std::size_t horizontalEdgeCount = rowCount * (columnCount - 1);
    const std::size_t verticalEdgeCount = (rowCount - 1) * columnCount;
    edges.reserve(horizontalEdgeCount + verticalEdgeCount);

    for (std::size_t row = 0; row < rowCount; row++) {
        for (std::size_t column = 0; column < columnCount; column++) {
            const std::size_t currentIndex = row * columnCount + column;

            if (column + 1 < columnCount) {
                edges.emplace_back(vertices[currentIndex], vertices[currentIndex + 1]);
            }

            if (row + 1 < rowCount) {
                edges.emplace_back(vertices[currentIndex], vertices[currentIndex + columnCount]);
            }
        }
    }
}

void Figure::CreateEdges(const std::vector<std::pair<std::size_t, std::size_t>>& edgeIndexes) {
    edges.reserve(edgeIndexes.size());

    for (const std::pair<std::size_t, std::size_t>& edgeIndex : edgeIndexes) {
        ValidateEdgeIndex(edgeIndex.first);
        ValidateEdgeIndex(edgeIndex.second);

        edges.emplace_back(vertices[edgeIndex.first], vertices[edgeIndex.second]);
    }
}

void Figure::ValidateGridSize(std::size_t rowCount, std::size_t columnCount) const {
    if (rowCount == 0 || columnCount == 0) {
        throw std::invalid_argument("Figure grid size must be positive");
    }

    if (vertices.size() != rowCount * columnCount) {
        throw std::invalid_argument("Figure vertex count does not match grid size");
    }
}

void Figure::ValidateEdgeIndex(std::size_t index) const {
    if (index >= vertices.size()) {
        throw std::out_of_range("Edge vertex index is out of range");
    }
}
