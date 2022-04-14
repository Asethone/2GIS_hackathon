#include <ctime>
#include <iostream>

#include "view.h"

#define CLOCK_START                         \
    unsigned int start_time = std::clock(); \
    for (int i = 0; i < 1000; i++) {
#define CLOCK_END                                     \
    }                                                 \
    unsigned int end_time = clock();                  \
    unsigned int search_time = end_time - start_time; \
    std::cout << search_time;

int main() {
    const char haystack[] = "vnk2435kvabco8awkh125kjneytbcd12qjhb4acd123xmnbqwnw4t";
    const char needle[] = "abcd1234";
    int threshold = 3;
    gis::Model model;
    gis::Controller controller(&model);
    gis::View view(&controller);

    // You can change this class to Search_1 or Search_2
    gis::Search_2 s;
    view.setSearch(&s);

    // CLOCK_START

    view.search(haystack, needle, threshold);

    // CLOCK_END

    return 0;
}
