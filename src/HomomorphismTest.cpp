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

TEST(HomomorphismTest, HomomorphismFeatures1) {
    // First, create two graphs
    grapph::Graph pentagon({ 0, 1, 2, 3, 4 }, { { 0, 1 }, { 1, 2 }, { 2, 3 },
                                                { 3, 4 }, { 4, 0 } });
    grapph::Graph triangle({ 0, 1, 2 }, { { 0, 1 }, { 1, 2 }, { 2, 0 } });

    // Create vertex map from s4 to triangle
    grapph::vfunc_t v_map = { { 0, 0 }, { 1, 1 }, { 2, 2 }, { 3, 0 }, { 4, 2 } };

    // Construct homomorphism
    grapph::Homomorphism hmm(pentagon, triangle, v_map);

    // Assertions
    ASSERT_FALSE(hmm.isInjective());
    ASSERT_TRUE(hmm.isSurjective());
    ASSERT_FALSE(hmm.isBijective());
}

TEST(HomomorphismTest, HomomorphismFeatures2) {
    // First, create two graphs
    grapph::Graph pentagon({ 0, 1, 2, 3, 4 }, { { 0, 1 }, { 1, 2 }, { 2, 3 },
                                                { 3, 4 }, { 4, 0 } });
    grapph::Graph p3({ 0, 1, 2, 3 }, { { 0, 1 }, { 1, 2 }, { 2, 3 } });

    // Create a vertex map from p3 to pentagon
    grapph::vfunc_t v_map = { { 0, 3 }, { 1, 4 }, { 2, 0 }, { 3, 1 } };

    // Construct homomorphism
    grapph::Homomorphism hmm(p3, pentagon, v_map);

    // Assertions
    ASSERT_TRUE(hmm.isInjective());
    ASSERT_FALSE(hmm.isSurjective());
    ASSERT_FALSE(hmm.isBijective());
}

TEST(HomomorphismTest, HomomorphismFeatures3) {
    // First, create two graphs
    grapph::Graph s4({ 0, 1, 2, 3, 4 }, { {0, 1}, {0, 2}, {0, 3}, {0, 4} });
    grapph::Graph iso({ 0, 1, 2, 3, 4 }, { {1, 0}, {1, 2}, {1, 3}, {1, 4} });

    // Create a vertex map from s4 to iso
    grapph::vfunc_t v_map = { {0, 1}, {1, 0}, {2, 3}, {3, 4}, {4, 2} };

    // Construct homomorphism
    grapph::Homomorphism hmm(s4, iso, v_map);

    // Assertions
    ASSERT_FALSE(s4.equals(iso));
    ASSERT_TRUE(hmm.isInjective());
    ASSERT_TRUE(hmm.isSurjective());
    ASSERT_TRUE(hmm.isBijective());
}

TEST(HomomorphismTest, HomomorphismComposition1) {
    // First, create three graphs
    grapph::Graph hexagon({ 0, 1, 2, 3, 4, 5 }, { {0, 1}, {1, 2},
                                                  {2, 3}, {3, 4}, {4, 5}, {5, 0} });
    grapph::Graph planar({ 0, 1, 2, 3 }, { {0, 1}, {1, 2}, {2, 3}, {3, 0}, {1, 3} });
    grapph::Graph triangle({ 0, 1, 2 }, { {0, 1}, {1, 2}, {2, 0} });

    // Create vertex map from hexagon to planar
    grapph::vfunc_t v_h2p = { {0, 0}, {1, 3}, {2, 1}, {3, 3}, {4, 1}, {5, 3} };

    // Create vertex map from planar to triangle
    grapph::vfunc_t v_p2t = { {0, 0}, {1, 1}, {2, 0}, {3, 2} };

    // Construct homomorphisms
    grapph::Homomorphism h2p(hexagon, planar, v_h2p);
    grapph::Homomorphism p2t(planar, triangle, v_p2t);

    // Compose homomorphisms
    ASSERT_NO_THROW(grapph::Homomorphism::compose(h2p, p2t));
}

TEST(HomomorphismTest, HomomorphismComposition2) {
    // First, create four graphs
    grapph::Graph hexagon({ 0, 1, 2, 3, 4, 5 }, { {0, 1}, {1, 2},
                                                  {2, 3}, {3, 4}, {4, 5}, {5, 0} });
    grapph::Graph planar({ 0, 1, 2, 3 }, { {0, 1}, {1, 2}, {2, 3}, {3, 0}, {1, 3} });
    grapph::Graph pentagon({ 0, 1, 2, 3, 4 }, { { 0, 1 }, { 1, 2 }, { 2, 3 },
                                                { 3, 4 }, { 4, 0 } });
    grapph::Graph triangle({ 0, 1, 2 }, { { 0, 1 }, { 1, 2 }, { 2, 0 } });

    // Construct vertex map from hexagon to planar
    grapph::vfunc_t v_h2p = { {0, 0}, {1, 3}, {2, 1}, {3, 3}, {4, 1}, {5, 3} };

    // Construct vertex map from pentagon to triangle
    grapph::vfunc_t v_p2t = { {0, 0}, {1, 1}, {2, 2}, {3, 0}, {4, 2} };

    // Construct homomorphisms
    grapph::Homomorphism h2p(hexagon, planar, v_h2p);
    grapph::Homomorphism p2t(pentagon, triangle, v_p2t);

    // Compose homomorphisms
    ASSERT_THROW(grapph::Homomorphism::compose(h2p, p2t), std::invalid_argument);
}