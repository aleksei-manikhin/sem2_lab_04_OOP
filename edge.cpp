#include "edge.h"

#include <stdexcept>

Edge::Edge(Vertex& begin, Vertex& end): begin(begin), end(end) {
    if (&begin == &end) {
        throw std::invalid_argument("Edge vertices must be different");
    }
}

const Vertex& Edge::GetBegin() const {
    return begin;
}

const Vertex& Edge::GetEnd() const {
    return end;
}
