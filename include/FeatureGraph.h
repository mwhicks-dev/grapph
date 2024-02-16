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

        static V defaultVertexState(vertex_t) {
            throw std::logic_error("No vertex auto state defined");
        }

        static E defaultEdgeState(edge_t) {
            throw std::logic_error("No edge auto state defined");
        }

    protected:

        void validate();
        void validate(edge_t);

    public:

        FeatureGraph() = default;
        FeatureGraph(std::vector<std::pair<vertex_t, V>>, std::vector<std::pair<edge_t, E>>);

        vertex_t addVertex() override;
        vertex_t addVertex(vertex_t) override;
        vertex_t addVertex(V);
        vertex_t addVertex(vertex_t, V);

        void updateVertex(vertex_t, V);

        void removeVertex(vertex_t) override;

        edge_t addEdge(vertex_t, vertex_t) override;
        edge_t addEdge(edge_t) override;
        edge_t addEdge(vertex_t, vertex_t, E);
        edge_t addEdge(edge_t, E);

        void updateEdge(edge_t, E);

        void removeEdge(edge_t) override;

        V getVertexState(vertex_t vertex) { Graph::validate(vertex); return vertex_state[vertex]; }
        std::map<vertex_t, V> getVertexStates() { return vertex_state; }

        E getEdgeState(edge_t edge) { validate(edge); return edge_state[edge]; }
        std::map<edge_t, E> getEdgeWeights() { return edge_state; }

        void setVertexAutoState(V(*func)(vertex_t)) { vertex_auto_state = func; }
        void setEdgeAutoState(E(*func)(edge_t)) { edge_auto_state = func; }

    };

}

#endif //GRAPPH_FEATUREGRAPH_H
