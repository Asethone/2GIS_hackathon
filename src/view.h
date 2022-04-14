#pragma once

#include <iostream>

#include "controller.h"

namespace gis {

class View {
 private:
    Controller *_controller;

 public:
    explicit View(Controller *controller);
    void setSearch(SearchInterface *search);
    void search(const char *haystack, const char *needle, int threshold);
};

}  // namespace gis
