//
// Created by adam on 16.02.2022.
//

#include "Auxiliary.h"

std::vector<int> Auxiliary::xor_vectors(std::vector<int>::iterator a_start, std::vector<int>::iterator a_stop,
                                        std::vector<int>::iterator b_start, std::vector<int>::iterator b_stop) {
    size_t x_size = std::min(a_stop - a_start, b_stop - b_start);
    auto xor_value = std::vector<int>(x_size);
    for (auto x_iter = xor_value.begin();
         a_start != a_stop && b_start != b_stop;
         ++a_start, ++b_start, ++x_iter) {
        *x_iter = *a_start ^ *b_start;
    }
    return xor_value;
}

