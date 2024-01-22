#include "gtest/gtest.h"

#include "Graph.h"

TEST(GraphTest, TestK3BasicSetup) {

    // Initialize graph
    grapph::Graph k3;

    // Add vertices
    grapph::vertex_t v0 = k3.addVertex();
    grapph::vertex_t v1 = k3.addVertex();
    grapph::vertex_t v2 = k3.addVertex();

    // Add edges
    grapph::edge_t e_0_1 = k3.addEdge(0, 1);
    grapph::edge_t e_0_2 = k3.addEdge(0, 2);
    grapph::edge_t e_1_2 = k3.addEdge(1, 2);

    // Assertions
    ASSERT_EQ(0, v0);
    ASSERT_EQ(1, v1);
    ASSERT_EQ(2, v2);

    ASSERT_EQ(0, e_0_1.first);
    ASSERT_EQ(1, e_0_1.second);
    ASSERT_EQ(0, e_0_2.first);
    ASSERT_EQ(2, e_0_2.second);
    ASSERT_EQ(1, e_1_2.first);
    ASSERT_EQ(2, e_1_2.second);

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
