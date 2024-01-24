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

        size_t num_vertices = 0;
        size_t num_edges = 0;

        size_t next_vertex = 0;

        void validate(vertex_t);

    public:

        Graph() = default;
        Graph(std::set<vertex_t>, std::set<edge_t>);

        vertex_t addVertex();
        vertex_t addVertex(vertex_t);
        edge_t addEdge(vertex_t, vertex_t);
        edge_t addEdge(edge_t);

        bool adjacent(vertex_t, vertex_t);
        bool incident(vertex_t, edge_t);

        std::set<vertex_t> getNeighbors(vertex_t);
        size_t getDegree(vertex_t);

        std::set<vertex_t> getVertices() { return vertices; }
        std::set<edge_t> getEdges() { return edges; }

        Graph induce(std::set<vertex_t>&);

        bool contains(Graph&);
        bool spannedBy(Graph&);
        bool induces(Graph&);

        bool equals(Graph&);

        static std::set<edge_t> getEdgeSpace(std::set<vertex_t>&);

        template <typename T>
        static bool isInvariant(Graph& a, Graph& b, T (*func)(Graph&)) {
            T aT = func(a);
            T bT = func(b);

            return aT == bT;
        }

    };

}

#endif //GRAPPH_VERTEX_H
