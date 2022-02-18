//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//
#include "../headers/Oracle.h"

Oracle::Oracle(const std::string &filename) : Circuit(filename) {}

Oracle::Oracle(const std::vector<std::vector<int>> &operations) : Circuit(operations) {}

std::vector<LineMatch>
Oracle::line_matches(Template template_, ulong line_index, ulong threshold) {
    std::vector<LineMatch> aaa;

    auto template_line = template_.get_line(line_index);
    auto t_line_size = template_line.size();
    auto t_line_start = template_line.begin();
    auto t_line_end = template_line.end();

    for (std::size_t i = 0u; i < lines.size(); ++i) {
        auto oracle_line = lines[i];
        auto o_line_start = oracle_line.begin();
        for (std::size_t j = 0u; j < oracle_line.size() - t_line_size; ++j) {
            auto o_slice_start = o_line_start + j;
            auto o_slice_end = o_slice_start + t_line_size;
            auto xorrr = Auxiliary::xor_vectors(t_line_start, t_line_end, o_slice_start, o_slice_end);

            bool loops = (*xorrr.begin() == 0) && (*(xorrr.end()-1) == 0);
            bool sequence = false;
            ulong max_start = 0;
            ulong max_length = 0;
            ulong current_start = 0;
            ulong current_length = 0;
            for(std::size_t k = 0u; k<xorrr.size(); ++k){
                if(xorrr[k] == 0){
                    if(current_length == 0){
                        current_start = k;
                        current_length = 1;
                    }
                    else {
                        ++current_length;
                    }
                }
                else{
                    if(current_length == 0){
                        continue;
                    }
                    else {
                        if(current_length > max_length){
                            max_length = current_length;
                            max_start = current_start;
                        }
                    }
                }
            }



        }
    }

    return aaa;
}


