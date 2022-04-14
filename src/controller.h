#pragma once

#include "model.h"

namespace gis {

class Controller {
 private:
    Model *_model;

 public:
    explicit Controller(Model *model);
    void setSearch(SearchInterface *search);
    SearchResult search(const char *haystack, const char *needle, int threshold);
};

}  // namespace gis
