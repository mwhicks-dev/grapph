#include <sstream>

#include "FeatureGraph.h"

namespace grapph {

    template <class V, class E>
    void FeatureGraph<V, E>::validate(edge_t edge) {
        if ( Graph::getEdges().count(edge) == 0
               || edge_state.count(edge) == 0 ) {
            std::stringstream ss;
            ss << "Edge (" << edge.first << ", " << edge.second
                << ") not in graph";
            throw std::invalid_argument(ss.str());
        }
    }

    template <class V, class E>
    FeatureGraph<V, E>::FeatureGraph(std::vector<std::pair<vertex_t, V>> vertices, std::vector<std::pair<edge_t, E>> edges)
    : Graph() {
        // Add each vertex
        for ( std::pair<vertex_t, V> pair : vertices ) {
            addVertex(pair.first, pair.second);
        }

        // Add each edge
        for ( std::pair<edge_t, E> pair : edges ) {
            addEdge(pair.first, pair.second);
        }

    }

    template <class V, class E>
    vertex_t FeatureGraph<V, E>::addVertex() {
        V state = vertex_auto_state(next_vertex);
        return addVertex(next_vertex, state);
    }

    template <class V, class E>
    vertex_t FeatureGraph<V, E>::addVertex(vertex_t u) {
        V state = vertex_auto_state(u);
        return addVertex(u, state);
    }

    template <class V, class E>
    vertex_t FeatureGraph<V, E>::addVertex(V t) {
        vertex_t recent = Graph::addVertex();
        vertex_state[recent] = t;
        return recent;
    }

    template <class V, class E>
    vertex_t FeatureGraph<V, E>::addVertex(grapph::vertex_t u, V t) {
        vertex_t recent = Graph::addVertex(u);
        vertex_state[recent] = t;
        return recent;
    }

    template <class V, class E>
    void FeatureGraph<V, E>::updateVertex(vertex_t u, V t) {
        Graph::validate(u);
        vertex_state[u] = t;
    }

    template <class V, class E>
    void FeatureGraph<V, E>::removeVertex(grapph::vertex_t u) {
        // Remove edge weights for edges u is incident to
        for ( vertex_t neighbor : Graph::getNeighbors(u) ) {
            // Get edge
            edge_t incident = { u, neighbor };
            if ( neighbor < u ) { incident = { neighbor, u }; }

            // Remove edge
            removeEdge(incident);
        }

        // Remove vertex u
        Graph::removeVertex(u);
        vertex_state.erase(u);
    }

    template <class V, class E>
    edge_t FeatureGraph<V, E>::addEdge(vertex_t u, vertex_t w) {
        edge_t recent = Graph::addEdge(u, w);
        try {
            edge_state[recent] = edge_auto_state(recent);
        } catch ( std::logic_error & e ) {
            Graph::removeEdge(recent);
            throw e;  // We need to remove the constructed edge before throwing the error, so we catch and throw again
        }
        
        return recent;
    }

    template <class V, class E>
    edge_t FeatureGraph<V, E>::addEdge(edge_t edge) {
        edge_state[edge] = edge_auto_state(edge);
        return Graph::addEdge(edge);
    }

    template <class V, class E>
    edge_t FeatureGraph<V, E>::addEdge(vertex_t u, vertex_t w, E state) {
        edge_t recent = Graph::addEdge(u, w);
        edge_state[recent] = state;
        return recent;
    }

    template <class V, class E>
    edge_t FeatureGraph<V, E>::addEdge(edge_t edge, E state) {
        edge_t recent = Graph::addEdge(edge);
        edge_state[recent] = state;
        return recent;
    }

    template <class V, class E>
    void FeatureGraph<V, E>::updateEdge(edge_t edge, E state) {
        validate(edge);
        edge_state[edge] = state;
    }

    template <class V, class E>
    void FeatureGraph<V, E>::removeEdge(edge_t edge) {
        validate(edge);
        edge_state.erase(edge);
        Graph::removeEdge(edge);
    }

}