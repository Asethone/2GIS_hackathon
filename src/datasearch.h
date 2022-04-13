#pragma once

#include <cstring>
#include <stdexcept>
#include <vector>

namespace gis {

// STRUCT FOR STORING OUTPUT DATA
struct SearchResult {
    int _length;
    int _h_offset;  // *** INT may be not enough for haystack with more than 2^31 chars!
    int _n_offset;
    // Constructor
    SearchResult(int length, int h_offset, int n_offset);
};

// STRATEGY PATTERN INTERFACE
class SearchInterface {
 public:
    virtual ~SearchInterface() {}
    virtual std::vector<SearchResult> search(const char *haystack, const char *needle, int threshold) = 0;
    // Function returns vector, which is not really good. Result may be printed to stdout instead.
};

// Simple iterative search algorythm. It's slow, but takes minimum extra memory.
class Search_1 : public SearchInterface {
 public:
    std::vector<SearchResult> search(const char *haystack, const char *needle, int threshold);
};

// CLASS FOR STORING INPUT DATA
class DataSearch {
 private:
    const char *_haystack;
    const char *_needle;
    int _threshold;
    // search strategy
    SearchInterface *_search_strat;

 public:
    DataSearch(const char *haystack, const char *needle, int threshold);
    void setSearch(SearchInterface *search);
    std::vector<SearchResult> search();
};

}  // namespace gis
