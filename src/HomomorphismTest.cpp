#include "gtest/gtest.h"

#include "Graph.h"
#include "Homomorphism.h"

TEST(HomomorphismTest, Homomorphism1) {
    // First, create two graphs
    grapph::Graph pentagon({ 0, 1, 2, 3, 4 }, { { 0, 1 }, { 1, 2 }, { 2, 3 },
                                                { 3, 4 }, { 4, 0 } });
    grapph::Graph triangle({ 0, 1, 2 }, { { 0, 1 }, { 1, 2 }, { 2, 0 } });

    // Create vertex map from s4 to triangle
    grapph::vfunc_t v_map = { { 0, 0 }, { 1, 1 }, { 2, 2 }, { 3, 0 }, { 4, 2 } };

    // Construct homomorphism
    ASSERT_NO_THROW(grapph::Homomorphism hmm(pentagon, triangle, v_map));
}

TEST(HomomorphismTest, Homomorphism2) {
    // First, create two graphs
    grapph::Graph pentagon({ 0, 1, 2, 3, 4 }, { { 0, 1 }, { 1, 2 }, { 2, 3 },
                                                { 3, 4 }, { 4, 0 } });
    grapph::Graph triangle({ 0, 1, 2 }, { { 0, 1 }, { 1, 2 }, { 2, 0 } });

    // Next, create vertex map for which no homomorphism may exist
    grapph::vfunc_t v_map = { { 0, 0 }, { 1, 0 }, { 2, 1 }, { 3, 2 }, { 4, 1 } };

    // Construct homomorphism (should fail)
    ASSERT_THROW(grapph::Homomorphism hmm(pentagon, triangle, v_map), std::invalid_argument);
}