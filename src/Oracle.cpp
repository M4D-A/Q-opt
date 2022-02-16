//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//

#include <algorithm>
#include "Oracle.h"
#include "Auxiliary.h"

Oracle::Oracle(const std::string &filename) : Circuit(filename) {}

Oracle::Oracle(const std::vector<std::vector<int>> &operations) : Circuit(operations) {}

std::vector<std::vector<int>> Oracle::line_matches(std::vector<int>::iterator template_start,
                                                   std::vector<int>::iterator template_end) {
    auto template_size = template_end - template_start;
    std::vector<std::vector<int>> matches;
    int line_num = 0;
    for (std::vector<int> line: lines) {
        auto line_start = line.begin();
        auto line_end = line.end();

        auto line_slice_start = line_start;
        auto line_slice_end = line_slice_start + template_size;

        for (; line_slice_end <= line_end; ++line_slice_start, ++line_slice_end) {
            auto xor_values = Auxiliary::xor_vectors(line_slice_start, line_slice_end,
                                                     template_start, template_end);

            bool zeros = std::all_of(xor_values.begin(), xor_values.end(), [](int i) { return i == 0; });

            if (zeros) {
                auto match_start_index = line_slice_start - line_start;
                auto match_end_index = line_slice_end - line_start;

                auto match = std::vector<int>(3);
                match[0] = line_num;
                match[1] = match_start_index;
                match[2] = match_end_index;
                matches.push_back(match);
            }
        }
        line_num++;
    }
    return matches;
}


