#ifndef GRAPPH_FEATUREGRAPH_H
#define GRAPPH_FEATUREGRAPH_H

#include <vector>

#include "Graph.h"

namespace grapph {

    template <typename T>
    class FeatureGraph : Graph {

    private:

        std::map<vertex_t, T> vertex_state;
        std::map<edge_t, long int> edge_weight;

        long int default_weight = 1;
        T (*state_constructor_function)(vertex_t) = defaultStateConstructor;

        static T defaultStateConstructor(vertex_t) {
            throw std::invalid_argument("No state constructor defined");
        }

    protected:

        void validate();
        void validate(edge_t);

    public:

        FeatureGraph() = default;
        FeatureGraph(std::vector<std::pair<vertex_t, T>>, std::set<edge_t>);
        FeatureGraph(std::vector<std::pair<vertex_t, T>>, std::vector<std::pair<edge_t, long int>>);
        FeatureGraph(std::set<vertex_t>, std::set<edge_t>, T (*)(vertex_t), long int);
        FeatureGraph(std::set<vertex_t>, std::vector<std::pair<edge_t, long int>>, T (*)(vertex_t));
        FeatureGraph(std::vector<std::pair<vertex_t, T>>, std::set<edge_t>, long int);

        vertex_t addVertex() override;
        vertex_t addVertex(vertex_t) override;
        vertex_t addVertex(T);
        vertex_t addVertex(vertex_t, T);

        void updateVertex(vertex_t, T);

        void removeVertex(vertex_t) override;

        edge_t addEdge(vertex_t, vertex_t) override;
        edge_t addEdge(edge_t) override;
        edge_t addEdge(vertex_t, vertex_t, long int);
        edge_t addEdge(edge_t, long int);

        void updateEdge(edge_t, long int);

        void removeEdge(edge_t) override;

        T getVertexState(vertex_t vertex) { Graph::validate(vertex); return vertex_state[vertex]; }
        std::map<vertex_t, T> getVertexStates() { return vertex_state; }

        long int getEdgeWeight(edge_t edge) { validate(edge); return edge_weight[edge]; }
        std::map<edge_t, long int> getEdgeWeights() { return edge_weight; }

        void setStateConstructor(T(*func)(vertex_t)) { state_constructor_function = func; }
        void setDefaultWeight(long int new_default_weight) { this->default_weight = new_default_weight; }

    };

}

#endif //GRAPPH_FEATUREGRAPH_H
