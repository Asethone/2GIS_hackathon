#pragma once

#include <cstring>
#include <stdexcept>
#include <vector>

namespace gis {

// Struct for storing output data
struct EntryData {
    int _length;
    std::size_t _h_offset;  // *** size_t may be not enough for haystack with more than 2^64 - 2 chars!
    int _n_offset;
    // Constructor
    EntryData(int length, std::size_t h_offset, int n_offset);
};

using SearchResult = std::vector<EntryData>;

// Strategy pattern interface
class SearchInterface {
 public:
    virtual ~SearchInterface() {}
    virtual SearchResult search(const char *haystack, const char *needle, int threshold) = 0;
    // Function returns vector (for tests implementation), which is not really good.
    // Result may be printed directly to stdout instead.
};

// Simple iterative (Brute Force) search algorithm. It's slow, but takes minimum extra memory.
class Search_1 : public SearchInterface {
 public:
    SearchResult search(const char *haystack, const char *needle, int threshold) override;
};

// Raita search algorithm (modification of Boyer–Moore algorithm). It's a fastest algorithm,
// but takes a O(p + 128) amount of memory. (p = needle length)
class Search_2 : public SearchInterface {
 public:
    SearchResult search(const char *haystack, const char *needle, int threshold) override;
};

// Main class for storing input data and call search algorythms
class Model {
 private:
    // search strategy
    SearchInterface *_search_strat;

 public:
    Model();
    void setSearch(SearchInterface *search);
    SearchResult search(const char *haystack, const char *needle, int threshold);
};

}  // namespace gis
