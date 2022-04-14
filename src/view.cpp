#include "view.h"

namespace gis {

View::View(Controller *controller) : _controller(controller) {}

void View::setSearch(SearchInterface *search) { _controller->setSearch(search); }

void View::search(const char *haystack, const char *needle, int threshold) {
    SearchResult res = _controller->search(haystack, needle, threshold);
    for (std::size_t i = 0; i < res.size(); i++) {
        std::cout << "sequence of length = " << res[i]._length << " found at haystack offset "
                  << res[i]._h_offset << ", needle offset " << res[i]._n_offset << std::endl;
    }
}

}  // namespace gis
