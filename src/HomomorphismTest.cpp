#include "gtest/gtest.h"

#include "Graph.h"
#include "Homomorphism.h"

TEST(HomomorphismTest, Homomorphism1) {
    // First, create two graphs
    grapph::Graph pentagon({ 0, 1, 2, 3, 4 }, { { 0, 1 }, { 1, 2 }, { 2, 3 },
                                                { 3, 4 }, { 4, 0 } });
    grapph::Graph triangle({ 0, 1, 2 }, { { 0, 1 }, { 1, 2 }, { 2, 0 } });

    // Create vertex homomorphism from s4 to triangle
    grapph::vfunc_t v_homomorphism = { { 0, 0 }, { 1, 1 }, { 2, 2 }, { 3, 0 }, { 4, 2 } };

    // Construct edge homomorphism
    grapph::efunc_t e_homomorphism;
    for ( grapph::edge_t edge : pentagon.getEdges() ) {
        e_homomorphism[edge] = { v_homomorphism[edge.first], v_homomorphism[edge.second] };
    }

    // Construct homomorphism
    ASSERT_NO_THROW(grapph::Homomorphism hmm(pentagon, triangle, v_homomorphism, e_homomorphism));
}