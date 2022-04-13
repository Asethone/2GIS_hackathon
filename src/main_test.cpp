#include <gtest/gtest.h>

#include <iostream>

#include "datasearch.h"

#define DATA_SEARCH                                  \
    gis::DataSearch ds(haystack, needle, threshold); \
    gis::Search_1 s1;                                \
    ds.setSearch(&s1);                               \
    auto res = ds.search();

TEST(normal_cases, 1) {
    const char haystack[] = "vnk2435kvabco8awkh125kjneytbcd12qjhb4acd123xmnbqwnw4t";
    const char needle[] = "abcd1234";
    int threshold = 3;
    DATA_SEARCH
    ASSERT_EQ(res.size(), 3);
    ASSERT_EQ(res[0]._length, 3);
    ASSERT_EQ(res[0]._h_offset, 9);
    ASSERT_EQ(res[0]._n_offset, 0);
    ASSERT_EQ(res[1]._length, 5);
    ASSERT_EQ(res[1]._h_offset, 27);
    ASSERT_EQ(res[1]._n_offset, 1);
    ASSERT_EQ(res[2]._length, 5);
    ASSERT_EQ(res[2]._h_offset, 38);
    ASSERT_EQ(res[2]._n_offset, 2);
}

TEST(normal_cases, 2) {
    const char haystack[] = "abcd12ab34acb15";
    const char needle[] = "acb";
    int threshold = 3;
    DATA_SEARCH
    ASSERT_EQ(res.size(), 1);
    ASSERT_EQ(res[0]._length, 3);
    ASSERT_EQ(res[0]._h_offset, 10);
    ASSERT_EQ(res[0]._n_offset, 0);
}

TEST(edge_cases, 1) {
    const char haystack[] = "acb";
    const char needle[] = "abcd12ab34acb15";
    int threshold = 3;
    DATA_SEARCH
    ASSERT_EQ(res.size(), 1);
    ASSERT_EQ(res[0]._length, 3);
    ASSERT_EQ(res[0]._h_offset, 0);
    ASSERT_EQ(res[0]._n_offset, 10);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
