#ifndef GRAPPH_FEATUREGRAPH_H
#define GRAPPH_FEATUREGRAPH_H

#include <vector>

#include "Graph.h"

namespace grapph {

    template <typename V, typename E>
    class FeatureGraph : public Graph {

    private:

        std::map<vertex_t, V> vertex_state;
        std::map<edge_t, E> edge_state;

        V (*vertex_auto_state)(vertex_t) = defaultVertexState;
        E (*edge_auto_state)(edge_t) = defaultEdgeState;

        static V defaultVertexState(vertex_t u) {
            throw std::logic_error("No vertex auto state defined");
        }

        static E defaultEdgeState(edge_t uw) {
            throw std::logic_error("No edge auto state defined");
        }

    protected:

        void validate(edge_t edge) {
            if ( Graph::getEdges().count(edge) == 0
                || edge_state.count(edge) == 0 ) {
                std::stringstream ss;
                ss << "Edge (" << edge.first << ", " << edge.second
                    << ") not in graph";
                throw std::invalid_argument(ss.str());
            }
        }

    public:

        FeatureGraph() = default;

        FeatureGraph(std::vector<std::pair<vertex_t, V>> vertices, std::vector<std::pair<edge_t, E>> edges)
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

        vertex_t addVertex() override {
            V state = vertex_auto_state(next_vertex);
            return addVertex(next_vertex, state);
        }

        vertex_t addVertex(vertex_t u) override {
            V state = vertex_auto_state(u);
            return addVertex(u, state);
        }

        vertex_t addVertex(V t) {
            return addVertex(next_vertex, t);
        }

        vertex_t addVertex(vertex_t u, V t) {
            vertex_t recent = Graph::addVertex(u);
            vertex_state[recent] = t;
            return recent;
        }

        void updateVertex(vertex_t u, V t) {
            Graph::validate(u);
            vertex_state[u] = t;
        }

        void removeVertex(vertex_t u) override {
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

        edge_t addEdge(vertex_t u, vertex_t w) override {
            edge_t recent = Graph::addEdge(u, w);
            try {
                edge_state[recent] = edge_auto_state(recent);
            } catch ( std::logic_error & e ) {
                Graph::removeEdge(recent);
                throw e;  // We need to remove the constructed edge before throwing the error, so we catch and throw again
            }
            
            return recent;
        }

        edge_t addEdge(edge_t edge) override {
            edge_state[edge] = edge_auto_state(edge);
            return Graph::addEdge(edge);
        }

        edge_t addEdge(vertex_t u, vertex_t w, E state) {
            return addEdge({u, w}, state);
        }

        edge_t addEdge(edge_t edge, E state) {
            edge_t recent = Graph::addEdge(edge);
            edge_state[recent] = state;
            return recent;
        }

        void updateEdge(edge_t edge, E state) {
            validate(edge);
            edge_state[edge] = state;
        }

        void removeEdge(edge_t edge) override {
            validate(edge);
            edge_state.erase(edge);
            Graph::removeEdge(edge);
        }

        V getVertexState(vertex_t vertex) { Graph::validate(vertex); return vertex_state[vertex]; }
        std::map<vertex_t, V> getVertexStates() { return vertex_state; }

        E getEdgeState(edge_t edge) { validate(edge); return edge_state[edge]; }
        std::map<edge_t, E> getEdgeWeights() { return edge_state; }

        void setVertexAutoState(V(*func)(vertex_t)) { vertex_auto_state = func; }
        void setEdgeAutoState(E(*func)(edge_t)) { edge_auto_state = func; }

    };

}

#endif //GRAPPH_FEATUREGRAPH_H
