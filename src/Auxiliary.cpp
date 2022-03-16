//
// Created by adam on 16.02.2022.
//

#include <iostream>
#include "../headers/Auxiliary.h"

typedef unsigned long ulong;

std::vector<ulong> Auxiliary::xor_vectors(std::vector<ulong>::iterator a_start, std::vector<ulong>::iterator a_stop,
                                        std::vector<ulong>::iterator b_start, std::vector<ulong>::iterator b_stop) {
    size_t x_size = std::min(a_stop - a_start, b_stop - b_start);
    auto xor_value = std::vector<ulong>(x_size);
    for (auto x_iter = xor_value.begin();
         a_start != a_stop && b_start != b_stop;
         ++a_start, ++b_start, ++x_iter) {
        *x_iter = *a_start ^ *b_start;
    }
    return xor_value;
}

std::vector<ulong> Auxiliary::longest_zero_subsequence(std::vector<ulong> vec) {
    ulong max_start = 0;
    ulong max_length = 0;
    ulong current_start = 0;
    ulong current_length = 0;
    for (std::size_t k = 0u; k < vec.size(); ++k) {
        if (vec[k] == 0) {
            if (current_length == 0) {
                current_start = k;
                current_length = 1;
            } else {
                ++current_length;
            }
        } else {
            if (current_length == 0) continue;
            else {
                if (current_length > max_length) {
                    max_length = current_length;
                    max_start = current_start;
                }
                current_length = 0;
            }
        }
    }
    if (current_length > max_length) {
        max_length = current_length;
        max_start = current_start;
    }
    return std::vector<ulong>({max_start, max_length});
}

void Auxiliary::print_vec(std::vector<ulong>::iterator begin, std::vector<ulong>::iterator end) {
    while(begin != end){
        std::cout<<*begin<<"-";
        begin++;
    }
    std::cout<<std::endl;
}

