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