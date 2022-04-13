#include <ctime>
#include <iostream>

#include "datasearch.h"

int main() {
    const char haystack[] = "abcd12ab34acb15";
    const char needle[] = "acb";
    int threshold = 3;
    gis::DataSearch ds(haystack, needle, threshold);
    gis::Search_1 s1;
    ds.setSearch(&s1);

    // unsigned int start_time = std::clock();
    // for (int i = 0; i < 100000; i++) {

    std::vector<gis::SearchResult> res = s1.search(haystack, needle, threshold);

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
