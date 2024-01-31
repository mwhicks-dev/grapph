#include "gtest/gtest.h"

#include "FeatureGraph.h"

TEST(FeatureGraphTest, TestConstructor1_1) {
    // Construct empty graph
    grapph::FeatureGraph<std::string> graph;

    // Assertions
    ASSERT_EQ(0, graph.getVertices().size());
    ASSERT_EQ(0, graph.getEdges().size());
}

TEST(FeatureGraphTest, TestConstructor2_1) {
    // Construct trail of len 1
    grapph::FeatureGraph<std::string> graph({{0, "start"}, {1, "end"}}, {{0, 1}});

    // Assertions
    ASSERT_EQ(2, graph.getVertices().size());
    ASSERT_EQ("start", graph.getVertexState(0));
    ASSERT_EQ("end", graph.getVertexState(1));
    ASSERT_EQ(1, graph.getEdges().size());
    ASSERT_EQ(1, graph.getEdgeWeight({0, 1}));
}

TEST(FeatureGraphTest, TestConstructor2_2) {
    // Assertions
    ASSERT_THROW(grapph::FeatureGraph<std::string> graph({{0, "start"}, {1, "end"}}, {{1, 2}}), std::invalid_argument);
}

TEST(FeatureGraphTest, TestConstructor3_1) {
    // Construct pentagon with tails
    grapph::FeatureGraph<std::string> graph(
            {{0, "pentagon"}, {1, "pentagon"}, {2, "pentagon"}, {3, "pentagon"},
                    {4, "pentagon"}, {5, "tail"}, {6, "tail"}},
            {{{0, 1}, 1}, {{1, 2}, 1}, {{2, 3}, 1}, {{3, 4}, 1},
                    {{4, 0}, 1}, {{3, 5}, 2}, {{4, 6}, 2}}
            );

    // Assertions
    ASSERT_EQ(7, graph.getVertices().size());
    ASSERT_EQ(7, graph.getEdges().size());
    for ( size_t i = 0; i < 5; i++ ) {
        ASSERT_EQ("pentagon", graph.getVertexState(i));
    }
    for ( size_t i = 5; i < 7; i++ ) {
        ASSERT_EQ("tail", graph.getVertexState(i));
    }
    for ( grapph::edge_t edge : graph.getEdges() ) {
        if ( "tail" == graph.getVertexState(edge.first)
                || "tail" == graph.getVertexState(edge.second) ) {
            ASSERT_EQ(2, graph.getEdgeWeight(edge));
        } else {
            ASSERT_EQ(1, graph.getEdgeWeight(edge));
        }
    }
}

std::string func(grapph::vertex_t u) {
    std::stringstream ss;
    ss << "n" << u;
    return ss.str();
}

TEST(FeatureGraphTest, TestCosntructor4_1) {
    // Construct pentagon with tails
    std::set<grapph::vertex_t> vertices = { 0, 1, 2, 3, 4, 5, 6 };
    std::set<grapph::edge_t> edges = { {0, 1}, {1, 2}, {2, 3},
                                       {3, 4}, {4, 0}, {3, 5}, {4, 6} };
    grapph::FeatureGraph<std::string> graph(vertices, edges, func, 7);

    // Assertions
    ASSERT_EQ(7, graph.getVertices().size());
    ASSERT_EQ(7, graph.getEdges().size());
    for ( grapph::vertex_t u : graph.getVertices() ) {
        ASSERT_EQ(func(u), graph.getVertexState(u));
    }
    for ( grapph::edge_t uw : graph.getEdges() ) {
        ASSERT_EQ(7, graph.getEdgeWeight(uw));
    }
}

