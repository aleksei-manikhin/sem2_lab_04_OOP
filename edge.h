#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"

class Edge {
private:
    Vertex& begin;
    Vertex& end;

public:
    Edge(Vertex& begin, Vertex& end);

    const Vertex& GetBegin() const;
    const Vertex& GetEnd() const;
};

#endif // EDGE_H
