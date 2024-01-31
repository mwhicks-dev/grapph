#include "FeatureGraph.h"

namespace grapph {

    template <class T>
    FeatureGraph<T>::FeatureGraph(std::vector<std::pair<vertex_t, T>> vertices, std::set<edge_t> edges)
    : Graph() {
        // Add each vertex
        for ( std::pair<vertex_t, T> pair : vertices ) {
            addVertex(pair.first, pair.second);
        }

        // Add each edge
        for ( edge_t edge : edges ) {
            addEdge(edge);
        }
    }

    template <class T>
    FeatureGraph<T>::FeatureGraph(std::vector<std::pair<vertex_t, T>> vertices,
                                  std::vector<std::pair<edge_t, long int>> edges) {
        // Add each vertex
        for ( std::pair<vertex_t, T> pair : vertices ) {
            addVertex(pair.first, pair.second);
        }

        // Add each edge
        for ( std::pair<edge_t, long int> pair : edges ) {
            addEdge(pair.first, pair.second);
        }
    }

    template <class T>
    FeatureGraph<T>::FeatureGraph(std::set<vertex_t> vertices, std::set<edge_t> edges,
                                  T (*state_constructor)(vertex_t), long int default_weight) {
        // Set defaults
        setStateConstructor(state_constructor);
        setDefaultWeight(default_weight);

        // Add each vertex
        for ( vertex_t vertex : vertices ) {
            addVertex(vertex);
        }

        // Add each edge
        for ( edge_t edge : edges ) {
            addEdge(edge);
        }
    }

    template <class T>
    FeatureGraph<T>::FeatureGraph(std::set<vertex_t> vertices, std::vector<std::pair<edge_t, long int>> edges,
                                  T (*state_constructor)(vertex_t)) {
        // Set default
        setStateConstructor(state_constructor);

        // Add each vertex
        for ( vertex_t vertex : vertices ) {
            addVertex(vertex);
        }

        // Add each edge
        for ( std::pair<edge_t, long> pair : edges ) {
            addEdge(pair.first, pair.second);
        }
    }

    template <class T>
    FeatureGraph<T>::FeatureGraph(std::vector<std::pair<vertex_t, T>> vertices, std::set<edge_t> edges,
                                  long int default_weight) {
        // Set default
        setDefaultWeight(default_weight);

        // Add each vertex
        for ( std::pair<vertex_t, T> pair : vertices ) {
            addVertex(pair.first, pair.second);
        }

        // Add each edge
        for ( edge_t edge : edges ) {
            addEdge(edge);
        }
    }

    template <class T>
    vertex_t FeatureGraph<T>::addVertex() {
        T state = defaultStateConstructor(next_vertex);
        return addVertex(next_vertex, state);
    }

    template <class T>
    vertex_t FeatureGraph<T>::addVertex(vertex_t u) {
        T state = defaultStateConstructor(u);
        return addVertex(u, state);
    }

    template <class T>
    vertex_t FeatureGraph<T>::addVertex(T t) {
        vertex_t recent = Graph::addVertex();
        vertex_state[recent] = t;
        return recent;
    }

    template <class T>
    vertex_t FeatureGraph<T>::addVertex(grapph::vertex_t u, T t) {
        vertex_t recent = Graph::addVertex(u);
        vertex_state[recent] = t;
        return recent;
    }

    template <class T>
    void FeatureGraph<T>::updateVertex(vertex_t u, T t) {
        Graph::validate(u);
        vertex_state[u] = t;
    }

    template <class T>
    void FeatureGraph<T>::removeVertex(grapph::vertex_t u) {
        // Remove edge weights for edges u is incident to
        for ( vertex_t neighbor : Graph::getNeighbors(u) ) {
            // Get edge
            edge_t incident = { u, neighbor };
            if ( neighbor < u ) { incident = { neighbor, u }; }

            // Remove edge
            edge_weight.erase(incident);
        }

        // Remove vertex u
        Graph::removeVertex(u);
        vertex_state.erase(u);
    }

}