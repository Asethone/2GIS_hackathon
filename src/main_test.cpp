#include <gtest/gtest.h>

#include <iostream>

#include "datasearch.h"

TEST(normal_cases, 1) {
    const char haystack[] = "vnk2435kvabco8awkh125kjneytbcd12qjhb4acd123xmnbqwnw4t";
    const char needle[] = "abcd1234";
    int threshold = 3;
    gis::DataSearch ds(haystack, needle, threshold);
    gis::Search_1 s1;
    ds.setSearch(&s1);
    std::vector<gis::SearchResult> res = ds.search();
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

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
