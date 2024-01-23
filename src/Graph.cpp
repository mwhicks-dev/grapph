#include "Graph.h"
#include "SetFunctions.h"

#include <iostream>
#include <sstream>

#include <stdexcept>

namespace grapph {

    void Graph::validate(vertex_t vertex) {
        if ( vertices.count(vertex) == 0 ) {
            std::stringstream ss;
            ss  << "Vertex "
                << vertex
                << " not found in graph";
            throw std::invalid_argument(ss.str().c_str());
        }
    }

    std::set<edge_t> Graph::getEdgeSpace(std::set<vertex_t>& vertex_set) {
        std::set<edge_t> edge_space;
        for ( vertex_t i : vertex_set ) {
            for ( vertex_t j : vertex_set ) {
                if ( i <= j ) { edge_space.insert({i, j}); }

            }
        }

        return edge_space;
    }

    Graph::Graph(std::set<vertex_t> vertices, std::set<edge_t> edges) {
        // Add each vertex
        for ( vertex_t vertex : vertices ) {
            addVertex(vertex);
        }

        // Add each edge
        for ( edge_t edge : edges ) {
            addEdge(edge);
        }
    }

    vertex_t Graph::addVertex() {
        addVertex(next_vertex);

        // Return new vertex
        return next_vertex - 1;
    }

    vertex_t Graph::addVertex(grapph::vertex_t vertex) {
        // Ensure vertex not already in vertex set
        bool fail = true;
        try {
            validate(vertex);
        } catch (std::invalid_argument &iae) {
            fail = false;
        }
        if (fail) {
            std::stringstream ss;
            ss  << "Vertex "
                << vertex
                << " already in graph";
            throw std::invalid_argument(ss.str().c_str());
        }

        // Add new vertex to vertex set
        vertices.insert(vertex);
        num_vertices++;

        // Update next vertex
        next_vertex = next_vertex > vertex ? next_vertex + 1 : vertex + 1;

        // Initialize list of neighbors
        vertex_neighbors[vertex] = std::set<vertex_t>();

        // Return new vertex
        return vertex;
    }

    edge_t Graph::addEdge(vertex_t first, vertex_t second) {
        return addEdge({first, second});
    }

    edge_t Graph::addEdge(edge_t edge) {
        // Order edge
        if ( edge.first > edge.second ) {
            edge = { edge.second, edge.first };
        }

        // Ensure vertices both in vertex set
        validate(edge.first);
        validate(edge.second);

        // Ensure edge does not already exist
        if ( vertex_neighbors[edge.first].count(edge.second) != 0
                || vertex_neighbors[edge.second].count(edge.first) != 0 ) {
            throw std::invalid_argument("Edge already added");
        }

        // Add edge to edge set
        edges.insert(edge);
        num_edges++;

        // Add vertices to each others' incidence lists
        vertex_neighbors[edge.first].insert(edge.second);
        vertex_neighbors[edge.second].insert(edge.first);

        return edge;
    }

    bool Graph::adjacent(vertex_t first, vertex_t second) {
        // Validate vertices
        validate(first);
        validate(second);

        // Determine whether each vertex considers the other a neighbor
        bool secondNeighborsFirst = vertex_neighbors[first].count(second) == 1;
        bool firstNeighborsSecond = vertex_neighbors[second].count(first) == 1;

        // Terminate if vertices disagree on neighborship; should be unreachable
        if ( firstNeighborsSecond != secondNeighborsFirst ) {
            std::cerr << "Inconsistency in adjacency data detected; "
                      << "Terminating with exit code 1" << std::endl;
            exit(1);
        }

        // Return result
        return secondNeighborsFirst;
    }

    bool Graph::incident(vertex_t vertex, edge_t edge) {
        // Validate vertex
        validate(vertex);

        return vertex == edge.first || vertex == edge.second;
    }

    std::set<vertex_t> Graph::getNeighbors(vertex_t vertex) {
        // Validate vertex
        validate(vertex);

        return vertex_neighbors[vertex];
    }

    size_t Graph::getDegree(vertex_t vertex) {
        // Validate vertex
        validate(vertex);

        return vertex_neighbors[vertex].size();
    }

    Graph Graph::induce(std::set<vertex_t> &vertex_subset) {
        // Assert vertex subset is proper
        for ( vertex_t vertex : vertex_subset ) {
            if ( vertices.count(vertex) == 0 ) {
                throw std::invalid_argument("Inducing vertex set not subset of graph vertices");
            }
        }

        // If subset, but not proper, return self
        if ( vertex_subset.size() == vertices.size() ) {
            return *this;
        }

        // Else, return new induced subgraph
        std::set<edge_t> edge_space = getEdgeSpace(vertex_subset);
        Graph induced_subgraph(vertex_subset, setIntersection(edges, edge_space));

        return induced_subgraph;
    }

    bool Graph::contains(Graph & subgraph_candidate) {
        return setContains(vertices, subgraph_candidate.vertices)
                && setContains(edges, subgraph_candidate.edges);
    }

    bool Graph::spannedBy(Graph & subgraph_candidate) {
        return setEquals(vertices, subgraph_candidate.vertices)
                && setContains(edges, subgraph_candidate.edges);
    }

    bool Graph::induces(Graph & induced_subgraph_candidate) {
        // Generate edge space and necessary induced subgraph edges
        std::set<edge_t> edge_space = getEdgeSpace(induced_subgraph_candidate.vertices);
        std::set<edge_t> induced_subgraph_edges = setIntersection(edges, edge_space);

        return setContains(vertices, induced_subgraph_candidate.vertices)
                && setEquals(induced_subgraph_edges, induced_subgraph_candidate.edges);
    }

    bool Graph::equals(Graph & candidate) {
        return contains(candidate) && candidate.contains(*this);
    }

    template <typename T>
    bool Graph::isInvariant(Graph& a, Graph& b, T (*func)(Graph&)) {
        T aT = func(a);
        T bT = func(b);

        return aT == bT;
    }

}
