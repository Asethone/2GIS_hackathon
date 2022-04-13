#include <ctime>
#include <iostream>

#include "datasearch.h"

int main() {
    const char haystack[] = "vnk2435kvabco8awkh125kjneytbcd12qjhb4acd123xmnbqwnw4t";
    const char needle[] = "abcd1234";
    int threshold = 3;
    gis::DataSearch ds(haystack, needle, threshold);
    gis::Search_1 s1;
    ds.setSearch(&s1);

    // unsigned int start_time = std::clock();
    // for (int i = 0; i < 100000; i++) {

    gis::SearchResult res = ds.search();

    for (int i = 0; i < res.size(); i++) {
        std::cout << "sequence of length = " << res[i]._length << " found at haystack offset "
                  << res[i]._h_offset << ", needle offset " << res[i]._n_offset << std::endl;
    }

    // }
    // unsigned int end_time = clock();
    // unsigned int search_time = end_time - start_time;
    // std::cout << search_time;

    return 0;
}
