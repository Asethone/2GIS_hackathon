#include "controller.h"

namespace gis {

Controller::Controller(Model *model) : _model(model) {}

void Controller::setSearch(SearchInterface *search) { _model->setSearch(search); }

SearchResult Controller::search(const char *haystack, const char *needle, int threshold) {
    return _model->search(haystack, needle, threshold);
}

}  // namespace gis
