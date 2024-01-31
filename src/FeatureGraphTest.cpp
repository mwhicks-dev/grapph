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

TEST(FeatureGraphTest, TestConstructor5_1) {
    // Construct pentagon with tails
    std::set<grapph::vertex_t> vertices = {0, 1, 2, 3, 4, 5, 6};
    grapph::FeatureGraph<std::string> graph(
            vertices,
            {{{0, 1}, 1}, {{1, 2}, 1}, {{2, 3}, 1}, {{3, 4}, 1},
             {{4, 0}, 1}, {{3, 5}, 2}, {{4, 6}, 2}},
            func
    );

    // Assertions
    ASSERT_EQ(7, graph.getVertices().size());
    ASSERT_EQ(7, graph.getEdges().size());
    for ( grapph::vertex_t u : graph.getVertices() ) {
        ASSERT_EQ(func(u), graph.getVertexState(u));
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

TEST(FeatureGraphTest, TestConstructor6_1) {
    // Construct pentagon with tails
    grapph::FeatureGraph<std::string> graph(
            {{0, "pentagon"}, {1, "pentagon"}, {2, "pentagon"}, {3, "pentagon"},
             {4, "pentagon"}, {5, "tail"}, {6, "tail"}},
            { {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}, {3, 5}, {4, 6} },
            7
    );

    // Assertions
    for ( size_t i = 0; i < 5; i++ ) {
        ASSERT_EQ("pentagon", graph.getVertexState(i));
    }
    for ( size_t i = 5; i < 7; i++ ) {
        ASSERT_EQ("tail", graph.getVertexState(i));
    }
    for ( grapph::edge_t uw : graph.getEdges() ) {
        ASSERT_EQ(7, graph.getEdgeWeight(uw));
    }
}

TEST(FeatureGraphTest, TestAddVertex1_1) {
    // Construct empty feature graph
    grapph::FeatureGraph<std::string> graph;
    graph.setStateConstructor(func);

    // Add three vertices
    grapph::vertex_t v0 = graph.addVertex();
    grapph::vertex_t v1 = graph.addVertex();
    grapph::vertex_t v2 = graph.addVertex();

    // Assertions
    ASSERT_EQ(0, v0);
    ASSERT_EQ(1, v1);
    ASSERT_EQ(2, v2);
    ASSERT_EQ("n0", graph.getVertexState(v0));
    ASSERT_EQ("n1", graph.getVertexState(v1));
    ASSERT_EQ("n2", graph.getVertexState(v2));
}

TEST(FeatureGraphTest, TestAddVertex1_2) {
    // Construct empty feature graph
    grapph::FeatureGraph<std::string> graph;

    // Assertions
    ASSERT_THROW(graph.addVertex(), std::logic_error);
}

TEST(FeatureGraphTest, TestAddVertex2_1) {
    // Construct empty feature graph
    grapph::FeatureGraph<std::string> graph;
    graph.setStateConstructor(func);

    // Add three vertices
    grapph::vertex_t v0 = graph.addVertex(10);
    grapph::vertex_t v1 = graph.addVertex(15);
    grapph::vertex_t v2 = graph.addVertex(20);

    // Assertions
    ASSERT_EQ(10, v0);
    ASSERT_EQ(15, v1);
    ASSERT_EQ(20, v2);
    ASSERT_EQ("n10", graph.getVertexState(v0));
    ASSERT_EQ("n15", graph.getVertexState(v1));
    ASSERT_EQ("n20", graph.getVertexState(v2));
    ASSERT_THROW(graph.addVertex(10), std::invalid_argument);
}

TEST(FeatureGraphTest, TestAddVertex2_2) {
    // Construct empty feature graph
    grapph::FeatureGraph<std::string> graph;

    // Assertions
    ASSERT_THROW(graph.addVertex(10), std::logic_error);
}

TEST(FeatureGraphTest, TestAddVertex3_1) {
    // Construct empty feature graph
    grapph::FeatureGraph<std::string> graph;

    // Add three vertices
    grapph::vertex_t v0 = graph.addVertex(func(0));
    grapph::vertex_t v1 = graph.addVertex(func(1));
    grapph::vertex_t v2 = graph.addVertex(func(0));

    // Assertions
    ASSERT_EQ(0, v0);
    ASSERT_EQ(1, v1);
    ASSERT_EQ(2, v2);
    ASSERT_EQ("n0", graph.getVertexState(v0));
    ASSERT_EQ("n1", graph.getVertexState(v1));
    ASSERT_EQ("n0", graph.getVertexState(v2));
}

TEST(FeatureGraphTest, TestAddVertex4_1) {
    // Construct empty feature graph
    grapph::FeatureGraph<std::string> graph;
    graph.setStateConstructor(func);

    // Add three vertices
    grapph::vertex_t v0 = graph.addVertex(10, func(10));
    grapph::vertex_t v1 = graph.addVertex(15, func(15));
    grapph::vertex_t v2 = graph.addVertex(20, func(10));

    // Assertions
    ASSERT_EQ(10, v0);
    ASSERT_EQ(15, v1);
    ASSERT_EQ(20, v2);
    ASSERT_EQ("n10", graph.getVertexState(v0));
    ASSERT_EQ("n15", graph.getVertexState(v1));
    ASSERT_EQ("n10", graph.getVertexState(v2));
}

TEST(FeatureGraphTest, TestUpdateVertex_1) {
    // Create feature graph with one labeled vertex
    grapph::FeatureGraph<std::string> graph;
    grapph::vertex_t u0 = graph.addVertex(func(0));

    // Assertions
    ASSERT_EQ(1, graph.getVertices().size());
    ASSERT_EQ(0, u0);
    ASSERT_EQ(func(u0), graph.getVertexState(u0));

    // Update vertex
    graph.updateVertex(u0, "vertex 0");

    // Assertions
    ASSERT_EQ(1, graph.getVertices().size());
    ASSERT_EQ(0, u0);
    ASSERT_EQ("vertex 0", graph.getVertexState(u0));
    ASSERT_NE(func(u0), graph.getVertexState(u0));
}

TEST(FeatureGraphTest, TestRemoveVertex_1) {
    // Construct pentagon with tails
    grapph::FeatureGraph<std::string> graph(
            {{0, "pentagon"}, {1, "pentagon"}, {2, "pentagon"}, {3, "pentagon"},
             {4, "pentagon"}, {5, "tail"}, {6, "tail"}},
            {{{0, 1}, 1}, {{1, 2}, 1}, {{2, 3}, 1}, {{3, 4}, 1},
             {{4, 0}, 1}, {{3, 5}, 2}, {{4, 6}, 2}}
    );

    // Remove arbitrary vertex
    graph.removeVertex(3);

    // Assertions
    ASSERT_EQ(6, graph.getVertices().size());
    ASSERT_EQ(4, graph.getEdges().size());
    for ( size_t i = 0; i < 3; i++ ) {
        ASSERT_EQ("pentagon", graph.getVertexState(i));
    }
    ASSERT_THROW(graph.getVertexState(3), std::invalid_argument);
    ASSERT_EQ("pentagon", graph.getVertexState(4));
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
