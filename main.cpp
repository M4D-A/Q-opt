//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//

#include <iostream>
#include <algorithm>
#include "headers/Oracle.h"
#include "headers/Template.h"
#include "headers/Auxiliary.h"

int main() {
    Oracle o("oracle.qc");
    Template t("template.qc");


    //"++++++++++++++++++++++++++++++++   LOG   +++++++++++++++++++++++++++++++++++"//
    o.print_lines(true);
    o.print_operation_ids();
    std::cout<<std::endl;

    t.print_lines(true);
    t.print_operation_ids();
    std::cout<<std::endl;
    //"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"//

    auto og = o.get_operation_ids();
    auto tg = t.get_operation_ids();
    auto o_lines = o.get_lines();
    auto t_lines = t.get_lines();

    ulong shift = 0;
    long delta_threshold = 2; //max acceptable loss

    auto tg_len = tg.size();
    auto xor_vec = Auxiliary::xor_vectors(og.begin()+shift, og.begin()+shift+tg_len, tg.begin(), tg.end());
    auto longest_match = Auxiliary::longest_zero_subsequence(xor_vec);

    ulong oracle_match_start = shift + longest_match[0];
    ulong template_match_start = longest_match[0];
    ulong match_length = longest_match[1];
    ulong substitution_length = tg_len - match_length;
    long delta = substitution_length - match_length; // delta > 0 = bad, delta < 0 = good


    //"++++++++++++++++++++++++++++++++   LOG   +++++++++++++++++++++++++++++++++++"//
    std::cout << "Oracle match start:   " << oracle_match_start << std::endl;
    std::cout << "Template match start: " << template_match_start << std::endl;
    std::cout << "Match length:         " << match_length << std::endl;
    std::cout << "Substitution length:  " << substitution_length << std::endl;
    std::cout << "Delta:                " << delta << std::endl;

    std::cout << std::endl;

    if(delta > delta_threshold){
        std::cout<<"Bad match"<<std::endl;
        return 0;
    }
    for(auto & t_line : o_lines){
        auto t_slice_begin = t_line.begin() + oracle_match_start;
        auto t_slice_end = t_slice_begin + match_length;
        Auxiliary::print_vec(t_slice_begin, t_slice_end);
    }
    std::cout<<std::endl;

    for(auto & t_line : t_lines){
        auto t_slice_begin = t_line.begin() + template_match_start;
        auto t_slice_end = t_slice_begin + match_length;
        Auxiliary::print_vec(t_slice_begin, t_slice_end);
    }
    std::cout<<std::endl;
    //"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"//



    std::vector<ulong> assignment(t_lines.size(), -1);
    for(ulong i = 0; i < t_lines.size(); ++i) {
        bool matched = false;
        auto t_slice_begin = t_lines[i].begin() + template_match_start;
        auto t_slice_end = t_slice_begin + match_length;
        for (ulong j = 0; j < o_lines.size(); ++j) {
            auto o_slice_begin = o_lines[j].begin() + oracle_match_start;
            auto o_slice_end = o_slice_begin + match_length;
            bool found = std::equal(t_slice_begin, t_slice_end, o_slice_begin, o_slice_end);
            bool unused = std::find(assignment.begin(), assignment.end(), j) == assignment.end();
            matched = found && unused;
            if(matched){
                assignment[i] = j;
                break;
            }
        }
    }

    for(ulong i = 0; i<assignment.size(); ++i){
        std::cout<<i<<": "<<assignment[i]<<std::endl;
    }

    std::cout<<std::endl;


}