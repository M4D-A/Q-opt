//
// Created by adam on 16.02.2022.
//

#include <iostream>
#include "../headers/Auxiliary.h"
typedef unsigned long ulong;

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

void Auxiliary::longest_zero_subsequence(std::vector<int> vec){
    ulong left_sequence = 0;
    ulong right_sequence = 0;
    ulong max_start = 0;
    ulong max_length = 0;
    ulong current_start = 0;
    ulong current_length = 0;
    for(std::size_t k = 0u; k<vec.size(); ++k){
        if(vec[k] == 0){
            if(current_length == 0){
                current_start = k;
                current_length = 1;
            }
            else {
                ++current_length;
            }
        }

        else{
            if(current_start == 0){
                left_sequence = current_length;
            }

            if(current_length == 0){
                continue;
            }
            else {
                if(current_length > max_length){
                    max_length = current_length;
                    max_start = current_start;
                }
                current_length = 0;
            }



        }
    }
    right_sequence = current_length;
    if(current_length > max_length) {
        max_length = current_length;
        max_start = current_start;
    }
    std::cout<<max_start<<" "<<max_length<<std::endl;
    std::cout<<left_sequence<<" "<<right_sequence<<std::endl;
}

