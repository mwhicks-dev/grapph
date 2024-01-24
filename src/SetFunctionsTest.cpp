#include "gtest/gtest.h"

#include "SetFunctions.h"

TEST(SetFunctionsTest, TestSetEquals1) {

    // Create two equal sets of size_t
    std::set<size_t> s1 = { 0, 1, 2 };
    std::set<size_t> s2 = { 0, 1, 2 };

    // Create two different sets of size_t
    std::set<size_t> d1 = { 0, 1, 2 };
    std::set<size_t> d2 = { 3, 4, 5 };

    // Assertions
    ASSERT_TRUE(grapph::setEquals(s1, s2));
    ASSERT_FALSE(grapph::setEquals(d1, d2));

}

TEST(SetFunctionsTest, TestSetEquals2) {

    // Create two equal bool sets
    std::set<bool> s1 = { true, true };
    std::set<bool> s2 = { true };

    // Create two different bool sets
    std::set<bool> d1 = { true };
    std::set<bool> d2 = { false };

    // Assertions
    ASSERT_TRUE(grapph::setEquals(s1, s2));
    ASSERT_FALSE(grapph::setEquals(d1, d2));

}

TEST(SetFunctionsTest, TestSetEquals3) {

    // Create two different size_t sets
    std::set<size_t> d1 = {};
    std::set<size_t> d2 = { 0 };

    // Assertions
    ASSERT_FALSE(grapph::setEquals(d1, d2));

}

TEST(SetFunctionsTest, TestSetContainment1) {

    // Create two size_t sets with containment relation
    std::set<size_t> sub = { 0, 1 };
    std::set<size_t> sup = { 0, 1, 2, 3 };

    // Assertions
    ASSERT_TRUE(grapph::setContains(sup, sub));
    ASSERT_FALSE(grapph::setContains(sub, sup));

}

TEST(SetFunctionsTest, TestSetContainment2) {

    // Create two bool sets with containment relation
    std::set<bool> sub = { false };
    std::set<bool> sup = { true, false };

    // Assertions
    ASSERT_TRUE(grapph::setContains(sup, sub));
    ASSERT_FALSE(grapph::setContains(sub, sup));

}

TEST(SetFunctionsTest, TestSetContainment3) {

    // Create two bool sets with containment relation
    std::set<bool> sub = {};
    std::set<bool> sup = { true, false };

    // Assertions
    ASSERT_TRUE(grapph::setContains(sup, sub));
    ASSERT_FALSE(grapph::setContains(sub, sup));

}

TEST(SetFunctionsTest, TestSetUnion1) {

    // Create two identical size_t sets
    std::set<size_t> s1 = { 0, 1, 2 };
    std::set<size_t> s2 = { 0, 1, 2 };

    // Create a different size_t set
    std::set<size_t> d1 = { 1, 2, 3 };

    // Union sets
    std::set<size_t> u1 = grapph::setUnion(s1, s2);
    std::set<size_t> u2 = grapph::setUnion(s1, d1);

    // Assertions
    ASSERT_TRUE(grapph::setEquals(s1, u1));
    ASSERT_TRUE(grapph::setEquals(s2, u1));
    ASSERT_TRUE(grapph::setContains(u2, s1));
    ASSERT_TRUE(grapph::setContains(u2, d1));
    ASSERT_NE(s1.size() + d1.size(), u2.size());

}

TEST(SetFunctionsTest, TestSetIntersection1) {

    // Create two identical size_t sets
    std::set<size_t> s1 = { 0, 1, 2 };
    std::set<size_t> s2 = { 0, 1, 2 };

    // Create a different size_t set
    std::set<size_t> d1 = { 1, 2, 3 };

    // Intersect sets
    std::set<size_t> i1 = grapph::setIntersection(s1, s2);
    std::set<size_t> i2 = grapph::setIntersection(s1, d1);

    // Assertions
    ASSERT_TRUE(grapph::setEquals(s1, i1));
    ASSERT_EQ(2, i2.size());
    ASSERT_TRUE(grapph::setContains(s1, i2));
    ASSERT_TRUE(grapph::setContains(d1, i2));

}

TEST(SetFunctionsTest, TestSetDifference1) {

    // Create two size_t sets
    std::set<size_t> a = { 0, 1, 2, 3 };
    std::set<size_t> b = { 1, 2 };

    // Subtract sets
    std::set<size_t> diff = grapph::setDifference(a, b);
    std::set<size_t> backwards = grapph::setDifference(b, a);

    // Assertions
    ASSERT_TRUE(grapph::setContains(a, diff));
    ASSERT_FALSE(grapph::setContains(b, diff));
    ASSERT_TRUE(grapph::setContains(a, b));
    ASSERT_EQ(a.size() - b.size(), diff.size());
    ASSERT_EQ(0, backwards.size());
    ASSERT_TRUE(grapph::setContains(b, backwards));

}

TEST(SetFunctionsTest, TestSetDifference2) {

    // Create two size_t sets
    std::set<size_t> a = { 0, 1, 2, 3 };
    std::set<size_t> b = { 1, 2, 4 };

    // Subtract sets
    std::set<size_t> diff = grapph::setDifference(a, b);
    std::set<size_t> backwards = grapph::setDifference(b, a);

    // Assertions
    ASSERT_TRUE(grapph::setContains(a, diff));
    ASSERT_FALSE(grapph::setContains(b, diff));
    ASSERT_FALSE(grapph::setContains(a, b));
    ASSERT_NE(a.size() - b.size(), diff.size());
    ASSERT_EQ(1, backwards.size());
    ASSERT_TRUE(grapph::setContains(b, backwards));

}
