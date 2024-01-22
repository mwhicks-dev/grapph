#include "Graph.h"

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

    vertex_t Graph::addVertex() {
        // Add new vertex to vertices list
        vertices.insert(next_vertex);

        // Increase number of vertices by one
        num_vertices += 1;

        // Initialize vertex neighbors
        vertex_neighbors[next_vertex] = std::set<vertex_t>();

        // Return new vertex
        return next_vertex++;
    }

    edge_t Graph::addEdge(vertex_t first, vertex_t second) {
        // Ensure vertices both in vertex set
        validate(first);
        validate(second);

        // Ensure edge does not already exist
        if ( vertex_neighbors[first].count(second) != 0 || vertex_neighbors[second].count(first) != 0 ) {
            throw std::invalid_argument("Edge already added");
        }

        // Create new edge
        edge_t edge(first, second);
        num_edges++;

        // Add vertices to each others' incidence lists
        vertex_neighbors[first].insert(second);
        vertex_neighbors[second].insert(first);

        // Return new edge
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

}
