#include "gtest/gtest.h"

#include "Graph.h"
#include "SetFunctions.h"

#include <algorithm>
#include <cstdlib>

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

TEST(GraphTest, TestSpanning1) {
    // Initialize parent graph
    std::set<grapph::vertex_t> vertices = { 0, 1, 2, 3, 4, 5, 6 };
    std::set<grapph::edge_t> edges = { {0, 1}, {1, 2}, {2, 3},
                                       {3, 4}, {4, 0}, {3, 5}, {4, 6} };
    grapph::Graph pentagon_with_tails(vertices, edges);

    // Initialize spanning subgraph
    std::set<grapph::edge_t> subgraph_edges = { {0, 1}, {1, 2}, {2, 3},
                                                {3, 4}, {3, 5}, {4, 6} };
    grapph::Graph subgraph_with_tails(vertices, subgraph_edges);

    // Assertions
    ASSERT_TRUE(pentagon_with_tails.contains(subgraph_with_tails));
    ASSERT_TRUE(pentagon_with_tails.spannedBy(subgraph_with_tails));
    ASSERT_FALSE(pentagon_with_tails.equals(subgraph_with_tails));
}

TEST(GraphTest, TestSpanning2) {
    // Initialize parent graph
    std::set<grapph::vertex_t> vertices = { 0, 1, 2, 3, 4, 5, 6 };
    std::set<grapph::edge_t> edges = { {0, 1}, {1, 2}, {2, 3},
                                       {3, 4}, {4, 0}, {3, 5}, {4, 6} };
    grapph::Graph pentagon_with_tails(vertices, edges);

    // Initialize spanning subgraph
    std::set<grapph::edge_t> subgraph_edges = {};
    grapph::Graph empty_spanning_subgraph(vertices, subgraph_edges);

    // Assertions
    ASSERT_TRUE(pentagon_with_tails.contains(empty_spanning_subgraph));
    ASSERT_TRUE(pentagon_with_tails.spannedBy(empty_spanning_subgraph));
    ASSERT_FALSE(pentagon_with_tails.equals(empty_spanning_subgraph));
}

TEST(GraphTest, TestEquals) {
    // Initialize parent graph
    std::set<grapph::vertex_t> vertices = { 0, 1, 2, 3, 4 };
    std::set<grapph::edge_t> edges = { {0, 1}, {0, 2}, {0, 3}, {0, 4} };
    grapph::Graph s4(vertices, edges);

    // Initialize equal graph
    std::set<grapph::edge_t> equal_edges = { {1, 0}, {2, 0}, {3, 0}, {4, 0} };
    grapph::Graph eq_s4(vertices, equal_edges);

    // Initialize isomorphic, but not equal, graph
    std::set<grapph::edge_t> isomorphic_edges = { {0, 1}, {2, 1}, {3, 1}, {4, 1} };
    grapph::Graph iso_s4(vertices, isomorphic_edges);

    // Assertions
    ASSERT_TRUE(s4.equals(eq_s4));
    ASSERT_TRUE(eq_s4.equals(s4));
    ASSERT_FALSE(s4.equals(iso_s4));
    ASSERT_FALSE(iso_s4.equals(s4));
    ASSERT_FALSE(eq_s4.equals(iso_s4));
    ASSERT_FALSE(iso_s4.equals(eq_s4));
}

TEST(GraphTest, TestEdgeSpace) {
    // Initialize...
    std::set<grapph::vertex_t> vertices = { 0, 1, 2 };
    std::set<grapph::edge_t> edges = grapph::Graph::getEdgeSpace(vertices);

    // Assertions
    ASSERT_EQ(3, edges.size());
    ASSERT_EQ(1, edges.count({ 0, 1 }));
    ASSERT_EQ(1, edges.count({ 0, 2 }));
    ASSERT_EQ(1, edges.count({ 1, 2 }));
}

size_t count_vertices(grapph::Graph & graph) { return graph.getVertices().size(); }

size_t count_edges(grapph::Graph & graph) { return graph.getEdges().size(); }

std::vector<size_t> degree_score(grapph::Graph & graph) {
    std::vector<size_t> degree_score;

    for ( grapph::vertex_t v : graph.getVertices() ) {
        degree_score.push_back( graph.getNeighbors(v).size() );
    }

    std::sort(degree_score.begin(), degree_score.end());

    return degree_score;
}

bool contains_triangle(grapph::Graph & graph) {
    std::set<grapph::vertex_t> vertices = graph.getVertices();

    for ( grapph::vertex_t vi : vertices ) {
        for ( grapph::vertex_t vj : vertices ) {
            for ( grapph::vertex_t vk : vertices ) {
                if ( vi != vj && vi != vk && vj != vk ) {
                    std::set<grapph::vertex_t> triangle_vertices = {vi, vj, vk};
                    std::set<grapph::edge_t> triangle_edges = grapph::Graph::getEdgeSpace(triangle_vertices);
                    grapph::Graph triangle(triangle_vertices, triangle_edges);
                    if ( graph.contains(triangle) )  return true;
                }
            }
        }
    }

    return false;
}

TEST(GraphTest, TestInvariants) {
    // Initialize parent graph
    std::set<grapph::vertex_t> vertices = { 0, 1, 2, 3, 4, 5, 6 };
    std::set<grapph::edge_t> edges = { {0, 1}, {1, 2}, {2, 3},
                                       {3, 4}, {4, 0}, {3, 5}, {4, 6} };
    grapph::Graph pentagon_with_tails(vertices, edges);

    // Create a random isomorphism on 7 vertices
    std::set<grapph::vertex_t> range;
    std::map<grapph::vertex_t, grapph::vertex_t> isomorphism;
    for ( grapph::vertex_t v : vertices ) {
        size_t mapping;
        do {
            mapping = std::rand();
        } while ( range.count(mapping) == 1 );
        isomorphism[v] = mapping;
        range.insert(mapping);
    }

    // Initialize isomorphic graph
    std::set<grapph::edge_t> isomorphic_edges;
    for ( grapph::edge_t edge : edges ) {
        isomorphic_edges.insert({isomorphism[edge.first], isomorphism[edge.second]});
    }
    grapph::Graph iso_pwt(range, isomorphic_edges);

    // Initialize non-isomorphic supergraph of graph with chord
    std::set<grapph::edge_t> chord = {{1,4}};
    chord = grapph::setUnion(edges, chord);
    grapph::Graph chord_pwt(vertices, chord);

    // Assertions
    ASSERT_TRUE(grapph::Graph::isInvariant<size_t>(pentagon_with_tails, iso_pwt, count_vertices));
    ASSERT_TRUE(grapph::Graph::isInvariant<size_t>(pentagon_with_tails, iso_pwt, count_edges));
    ASSERT_TRUE(grapph::Graph::isInvariant<bool>(pentagon_with_tails, iso_pwt, contains_triangle));
    ASSERT_TRUE(grapph::Graph::isInvariant<size_t>(pentagon_with_tails, chord_pwt, count_vertices));
    ASSERT_FALSE(grapph::Graph::isInvariant<size_t>(pentagon_with_tails, chord_pwt, count_edges));
    EXPECT_TRUE(contains_triangle(chord_pwt));
    EXPECT_FALSE(contains_triangle(pentagon_with_tails));
    ASSERT_FALSE(grapph::Graph::isInvariant<bool>(pentagon_with_tails, chord_pwt, contains_triangle));
    ASSERT_TRUE(grapph::Graph::isInvariant<size_t>(iso_pwt, chord_pwt, count_vertices));
    ASSERT_FALSE(grapph::Graph::isInvariant<size_t>(iso_pwt, chord_pwt, count_edges));
    ASSERT_FALSE(grapph::Graph::isInvariant<bool>(iso_pwt, chord_pwt, contains_triangle));
}
