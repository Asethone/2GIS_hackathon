#include "model.h"

namespace gis {

EntryData::EntryData(int length, std::size_t h_offset, int n_offset)
    : _length(length), _h_offset(h_offset), _n_offset(n_offset) {}

// Simple algorithm
SearchResult Search_1::search(const char *haystack, const char *needle, int threshold) {
    SearchResult result;
    const char *hp = haystack;
    while (*hp) {
        const char *np = needle;
        while (np) {
            np = strchr(np, *hp);
            if (np) {
                int cnt = 0;
                for (; np && *np == *hp; np++, hp++) {
                    if (!*np || !*hp) break;
                    cnt++;
                }
                if (cnt >= threshold) {
                    result.push_back(EntryData(cnt, hp - haystack - cnt, np - needle - cnt));
                    break;
                } else {
                    hp -= cnt;
                }
            } else {
                hp++;
            }
        }
    }
    return result;
}

// Inline function for finding first occurence of "symbol" in string "str" before position "last"
inline int findFirst(const char *str, char symbol, int last) {
    for (int i = 0; i < last; i++) {
        if (str[i] == symbol) return i;
    }
    return -1;
}

// Inline function for checking equality of string "str" and "patterns" from str position "begin" to "end"
inline bool restEqual(const char *str, const char *pattern, int begin, int end) {
    for (int i = begin; i < end; i++) {
        if (str[i] != pattern[i - begin + 1]) return false;
    }
    return true;
}

// Raita algorithm
SearchResult Search_2::search(const char *haystack, const char *needle, int threshold) {
    SearchResult result;
    const char *hp = haystack;
    int n = strlen(needle);  // it's definitely finite number (max 1e6)
    if (!n) return result;
    int m = threshold;
    // If threshold = 1, do first algorithm
    if (m == 1) {
        return Search_1().search(haystack, needle, threshold);
    }
    // else do Raita algorithm:
    while (findFirst(hp, 0, m) == -1) {
        // Preprocessing
        int bmBc[128];
        for (int i = 0; i < 128; i++) {
            bmBc[i] = m;
        }
        for (int i = 0; i < m - 1; i++) {
            bmBc[static_cast<std::size_t>(hp[i])] = m - i - 1;
        }
        // first, last and middle chars
        const char first = hp[0];
        const char mid = hp[m / 2];
        const char last = hp[m - 1];
        int j = 0;
        // Compare needle and current substring in search window
        while (j <= n - m) {
            char c = needle[j + m - 1];
            if (last == c && mid == needle[j + m / 2] && first == needle[j]) {
                if (restEqual(needle, hp, j + 1, j + m - 1)) {
                    int cnt = m;
                    while (hp[cnt] && needle[cnt + j] == hp[cnt]) {
                        cnt++;
                    }
                    result.push_back(EntryData(cnt, hp - haystack, j));
                    hp += cnt - 1;
                    break;
                }
            }
            j += bmBc[static_cast<std::size_t>(c)];
        }
        hp++;
    }
    return result;
}

Model::Model() : _search_strat(nullptr) {}

void Model::setSearch(SearchInterface *search) { _search_strat = search; }

SearchResult Model::search(const char *haystack, const char *needle, int threshold) {
    if (_search_strat == nullptr) {
        throw std::out_of_range("No search strategy have been setted");
    }
    if (threshold <= 0) {
        throw std::invalid_argument("Threshold must be non-zero positive integer number");
    }
    return _search_strat->search(haystack, needle, threshold);
}

}  // namespace gis
