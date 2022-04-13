#include "datasearch.h"

namespace gis {

SearchResult::SearchResult(int length, int h_offset, int n_offset)
    : _length(length), _h_offset(h_offset), _n_offset(n_offset) {}

std::vector<SearchResult> Search_1::search(const char *haystack, const char *needle, int threshold) {
    std::vector<SearchResult> result;
    const char *hp = haystack;
    while (*hp) {
        const char *np = needle;
        while (np && *np) {
            np = strchr(np, *hp);
            int cnt = 0;
            if (np) {
                for (; np && *np == *hp; np++, hp++) {
                    cnt++;
                }
                if (cnt >= threshold) {
                    result.push_back(SearchResult(cnt, hp - haystack - cnt, np - needle - cnt));
                }
            } else {
                hp++;
            }
        }
    }
    return result;
}

DataSearch::DataSearch(const char *haystack, const char *needle, int threshold)
    : _haystack(haystack), _needle(needle), _threshold(threshold), _search_strat(nullptr) {}

void DataSearch::setSearch(SearchInterface *search) { _search_strat = search; }

std::vector<SearchResult> DataSearch::search() {
    if (_search_strat == nullptr) {
        throw std::out_of_range("No search strategy has setted");
    }
    return _search_strat->search(_haystack, _needle, _threshold);
}

}  // namespace gis
