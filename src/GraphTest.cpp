#include "gtest/gtest.h"

#include "Graph.h"
#include "SetFunctions.h"

TEST(GraphTest, TestK3BasicSetup) {

    // Initialize graph
    grapph::Graph k3;

    // Add vertices
    grapph::vertex_t v0 = k3.addVertex();
    grapph::vertex_t v1 = k3.addVertex(2);
    grapph::vertex_t v2 = k3.addVertex();
    std::set<grapph::vertex_t> vertices = { v0, v1, v2 };
    std::set<grapph::vertex_t> vertex_set = k3.getVertices();

    // Add edges
    grapph::edge_t e_0_1 = k3.addEdge(0, 2);
    grapph::edge_t e_0_2 = k3.addEdge(0, 3);
    grapph::edge_t e_1_2 = k3.addEdge({2, 3});
    std::set<grapph::edge_t> edges = { e_0_1, e_0_2, e_1_2 };
    std::set<grapph::edge_t> edge_set = k3.getEdges();

    // Assertions
    ASSERT_EQ(0, v0);
    ASSERT_EQ(2, v1);
    ASSERT_EQ(3, v2);

    ASSERT_EQ(0, e_0_1.first);
    ASSERT_EQ(2, e_0_1.second);
    ASSERT_EQ(0, e_0_2.first);
    ASSERT_EQ(3, e_0_2.second);
    ASSERT_EQ(2, e_1_2.first);
    ASSERT_EQ(3, e_1_2.second);

    ASSERT_TRUE(grapph::setEquals(vertices, vertex_set));
    EXPECT_TRUE(grapph::setContains(edges, edge_set));
    EXPECT_TRUE(grapph::setContains(edge_set, edges));
    EXPECT_EQ(3, edge_set.size());
    ASSERT_TRUE(grapph::setEquals(edges, edge_set));

    ASSERT_EQ(2, k3.getDegree(v0));
    ASSERT_EQ(2, k3.getDegree(v1));
    ASSERT_EQ(2, k3.getDegree(v2));

    ASSERT_TRUE(k3.adjacent(v0, v1));
    ASSERT_TRUE(k3.adjacent(v0, v2));
    ASSERT_TRUE(k3.adjacent(v1, v2));

    ASSERT_TRUE(k3.incident(v0, e_0_1));
    ASSERT_TRUE(k3.incident(v1, e_0_1));
    ASSERT_TRUE(k3.incident(v0, e_0_2));
    ASSERT_TRUE(k3.incident(v2, e_0_2));
    ASSERT_TRUE(k3.incident(v1, e_1_2));
    ASSERT_TRUE(k3.incident(v2, e_1_2));

    ASSERT_EQ(0, k3.getNeighbors(v0).count(v0));
    ASSERT_EQ(1, k3.getNeighbors(v0).count(v1));
    ASSERT_EQ(1, k3.getNeighbors(v0).count(v2));
    ASSERT_EQ(1, k3.getNeighbors(v1).count(v0));
    ASSERT_EQ(0, k3.getNeighbors(v1).count(v1));
    ASSERT_EQ(1, k3.getNeighbors(v1).count(v2));
    ASSERT_EQ(1, k3.getNeighbors(v2).count(v0));
    ASSERT_EQ(1, k3.getNeighbors(v2).count(v1));
    ASSERT_EQ(0, k3.getNeighbors(v2).count(v2));

    ASSERT_THROW(k3.addEdge(v0, 4), std::invalid_argument);
    ASSERT_THROW(k3.adjacent(v0, 4), std::invalid_argument);
    ASSERT_THROW(k3.getDegree(4), std::invalid_argument);
    ASSERT_THROW(k3.getNeighbors(4), std::invalid_argument);

}

TEST(GraphTest, TestK3SetBasedSetup) {

    // Initialize graph
    std::set<grapph::vertex_t> vertices = { 0, 2, 3 };
    std::set<grapph::edge_t> edges = {{0, 2}, {0, 3}, {2, 3}};
    grapph::Graph k3(vertices, edges);
    std::set<grapph::vertex_t> vertex_set = k3.getVertices();
    std::set<grapph::edge_t> edge_set = k3.getEdges();

    ASSERT_TRUE(grapph::setEquals(vertices, vertex_set));
    ASSERT_TRUE(grapph::setEquals(edges, edge_set));

    ASSERT_EQ(2, k3.getDegree(0));
    ASSERT_EQ(2, k3.getDegree(2));
    ASSERT_EQ(2, k3.getDegree(3));

    ASSERT_TRUE(k3.adjacent(0, 2));
    ASSERT_TRUE(k3.adjacent(0, 3));
    ASSERT_TRUE(k3.adjacent(2, 3));

    ASSERT_TRUE(k3.incident(0, {0, 2}));
    ASSERT_TRUE(k3.incident(2, {0, 2}));
    ASSERT_TRUE(k3.incident(0, {0, 3}));
    ASSERT_TRUE(k3.incident(3, {0, 3}));
    ASSERT_TRUE(k3.incident(2, {2, 3}));
    ASSERT_TRUE(k3.incident(3, {2, 3}));

    ASSERT_EQ(0, k3.getNeighbors(0).count(0));
    ASSERT_EQ(1, k3.getNeighbors(0).count(2));
    ASSERT_EQ(1, k3.getNeighbors(0).count(3));
    ASSERT_EQ(1, k3.getNeighbors(2).count(0));
    ASSERT_EQ(0, k3.getNeighbors(2).count(2));
    ASSERT_EQ(1, k3.getNeighbors(2).count(3));
    ASSERT_EQ(1, k3.getNeighbors(3).count(0));
    ASSERT_EQ(1, k3.getNeighbors(3).count(2));
    ASSERT_EQ(0, k3.getNeighbors(3).count(3));

    ASSERT_THROW(k3.addEdge(0, 4), std::invalid_argument);
    ASSERT_THROW(k3.adjacent(0, 4), std::invalid_argument);
    ASSERT_THROW(k3.getDegree(4), std::invalid_argument);
    ASSERT_THROW(k3.getNeighbors(4), std::invalid_argument);

}

TEST(GraphTest, TestInduce1) {

    // Initialize parent graph
    std::set<grapph::vertex_t> vertices = { 0, 1, 2, 3, 4 };
    std::set<grapph::edge_t> edges = { {0, 1}, {0, 2}, {0, 3}, {0, 4} };
    grapph::Graph s4(vertices, edges);

    // Induce subgraph
    std::set<grapph::vertex_t> induced_vertices = { 0, 1, 2, 3 };
    std::set<grapph::edge_t> induced_edges = { {0, 1}, {0, 2}, {0, 3} };
    grapph::Graph induced = s4.induce(induced_vertices);

    std::set<grapph::vertex_t> actual_vertices = induced.getVertices();
    std::set<grapph::edge_t> actual_edges = induced.getEdges();

    // Assertions
    ASSERT_TRUE(s4.contains(induced));
    ASSERT_TRUE(s4.induces(induced));

    ASSERT_TRUE(grapph::setEquals(induced_vertices, actual_vertices));
    ASSERT_TRUE(grapph::setEquals(induced_edges, actual_edges));

}

TEST(GraphTest, TestInduce2) {

    // Initialize parent graph
    std::set<grapph::vertex_t> vertices = { 0, 1, 2, 3, 4 };
    std::set<grapph::edge_t> edges = { {0, 1}, {0, 2}, {0, 3}, {0, 4} };
    grapph::Graph s4(vertices, edges);

    // Induce subgraph
    std::set<grapph::vertex_t> induced_vertices = { 1, 2, 3, 4 };
    std::set<grapph::edge_t> induced_edges = {};
    grapph::Graph induced = s4.induce(induced_vertices);

    std::set<grapph::vertex_t> actual_vertices = induced.getVertices();
    std::set<grapph::edge_t> actual_edges = induced.getEdges();

    // Assertions
    ASSERT_TRUE(s4.contains(induced));
    ASSERT_TRUE(s4.induces(induced));

    ASSERT_TRUE(grapph::setEquals(induced_vertices, actual_vertices));
    ASSERT_TRUE(grapph::setEquals(induced_edges, actual_edges));

}

TEST(GraphTest, TestInduce3) {
    // Initialize parent graph
    std::set<grapph::vertex_t> vertices = { 0, 1, 2, 3, 4 };
    std::set<grapph::edge_t> edges = { {0, 1}, {0, 2}, {0, 3}, {0, 4} };
    grapph::Graph s4(vertices, edges);

    std::set<grapph::vertex_t> induced_vertices = { 0, 2, 4, 6 };

    // Assertions
    ASSERT_THROW(s4.induce(induced_vertices), std::invalid_argument);
}

TEST(GraphTest, TestInducesEmpty) {
    // Initialize parent graph
    std::set<grapph::vertex_t> vertices = { 0, 1, 2, 3, 4 };
    std::set<grapph::edge_t> edges = { {0, 1}, {0, 2}, {0, 3}, {0, 4} };
    grapph::Graph s4(vertices, edges);

    // Induce blank subgraph
    std::set<grapph::vertex_t> induced_vertices = {};
    std::set<grapph::edge_t> induced_edges = {};
    grapph::Graph induced = s4.induce(induced_vertices);

    std::set<grapph::vertex_t> actual_vertices = induced.getVertices();
    std::set<grapph::edge_t> actual_edges = induced.getEdges();

    // Assertions
    ASSERT_TRUE(s4.contains(induced));
    ASSERT_TRUE(s4.induces(induced));

    ASSERT_TRUE(grapph::setEquals(induced_vertices, actual_vertices));
    ASSERT_TRUE(grapph::setEquals(induced_edges, actual_edges));
}
