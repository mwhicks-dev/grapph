#ifndef GRAPPH_H
#define GRAPPH_H

#include <set>
#include <map>

namespace grapph {

    typedef size_t vertex_t;
    typedef std::pair<vertex_t, vertex_t> edge_t;

    class Graph {

    private:

        std::set<vertex_t> vertices;
        std::set<edge_t> edges;

        std::map<vertex_t, std::set<vertex_t>> vertex_neighbors;

        size_t num_vertices;
        size_t num_edges;

    public:

        Graph();

        vertex_t addVertex();
        edge_t addEdge(vertex_t, vertex_t);

        bool adjacent(vertex_t, vertex_t);
        bool incident(vertex_t, edge_t);

        size_t degree(vertex_t);

    };

}

#endif //GRAPPH_VERTEX_H
