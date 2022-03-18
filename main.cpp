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
    ulong initial_shift = 0;
    long delta_threshold = 6; //max acceptable loss

    {
    //"++++++++++++++++++++++++++++++++   LOG   +++++++++++++++++++++++++++++++++++"//
    o.print_lines(true);
    o.print_operation_ids();
    std::cout << std::endl;

    t.print_lines(true);
    t.print_operation_ids();
    std::cout << std::endl;
    //"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"//
    }

    auto oracle_gates = o.get_operation_ids();
    auto template_gates = t.get_operation_ids();

    auto template_gates_length = template_gates.size();

    auto oracle_gates_begin = oracle_gates.begin() + initial_shift;
    auto oracle_gates_end   = oracle_gates_begin + template_gates_length;
    auto template_gates_begin = template_gates.begin() + initial_shift;
    auto template_gates_end   = template_gates.end();

    auto oracle_lines = o.get_lines();
    auto template_lines = t.get_lines();

    auto xor_vec = Auxiliary::xor_vectors(oracle_gates_begin, oracle_gates_end,
                                          template_gates.begin(), template_gates.end());
    auto initial_gate_match = Auxiliary::longest_zero_subsequence(xor_vec);

    ulong initial_oracle_match_start = initial_shift + initial_gate_match[0];
    ulong initial_template_match_start = initial_gate_match[0];
    ulong initial_match_length = initial_gate_match[1];
    ulong initial_substitution_length = template_gates_length - initial_match_length;
    long initial_delta = initial_substitution_length - initial_match_length; // delta > 0 = bad, delta < 0 = good

//"++++++++++++++++++++++++++++++++   LOG   +++++++++++++++++++++++++++++++++++"//
    {
        std::cout << "Initial Oracle match start:   " << initial_oracle_match_start << std::endl;
        std::cout << "Initial Template match start: " << initial_template_match_start << std::endl;
        std::cout << "Initial Match length:         " << initial_match_length << std::endl;
        std::cout << "Initial Substitution length:  " << initial_substitution_length << std::endl;
        std::cout << "Initial Delta:                " << initial_delta << std::endl;

        std::cout << std::endl;

        if (initial_delta > delta_threshold) {
            std::cout << "Bad match at gate" << std::endl;
            return 0;
        }
        for (auto &t_line: oracle_lines) {
            auto t_slice_begin = t_line.begin() + initial_oracle_match_start;
            auto t_slice_end = t_slice_begin + initial_match_length;
            Auxiliary::print_vec(t_slice_begin, t_slice_end);
        }
        std::cout << std::endl;

        for (auto &t_line: template_lines) {
            auto t_slice_begin = t_line.begin() + initial_template_match_start;
            auto t_slice_end = t_slice_begin + initial_match_length;
            Auxiliary::print_vec(t_slice_begin, t_slice_end);
        }
        std::cout << std::endl;
    }
//"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"//

    std::vector<ulong> assignment;
    ulong final_template_match_begin;
    ulong final_template_match_end;
    ulong final_oracle_match_begin;
    ulong final_oracle_match_end;

    ulong cut = 0;
    long delta = initial_delta;
    while(delta < delta_threshold && (initial_match_length - cut) > 0){ //// cut
        for(ulong cut_shift = 0; cut_shift <= cut; cut_shift++){ //// cut_shift

            ulong template_slice_begin_index = initial_template_match_start + cut_shift;
            ulong template_slice_end_index = template_slice_begin_index + initial_match_length - cut;
            ulong oracle_slice_begin_index = initial_oracle_match_start + cut_shift;
            ulong oracle_slice_end_index = oracle_slice_begin_index + initial_match_length - cut;

            std::vector<ulong> current_assignment(template_lines.size(), -1);

            ///matching start
            for(ulong i = 0; i < template_lines.size(); ++i) { //// t_line
                bool line_matched = false;
                auto template_line_begin = template_lines[i].begin();
                auto template_line_slice_begin = template_line_begin + template_slice_begin_index;
                auto template_line_slice_end = template_line_begin + template_slice_end_index;
                std::cout<<"____"<<std::endl;
                Auxiliary::print_vec(template_line_slice_begin, template_line_slice_end);
                std::cout<<"____"<<std::endl;
                for (ulong j = 0; j < oracle_lines.size(); ++j) { //// o_line
                    auto oracle_line_begin = oracle_lines[j].begin();
                    auto oracle_line_slice_begin = oracle_line_begin + oracle_slice_begin_index;
                    auto oracle_line_slice_end = oracle_line_begin + oracle_slice_end_index;

                    Auxiliary::print_vec(oracle_line_slice_begin, oracle_line_slice_end);

                    bool found = std::equal(template_line_slice_begin, template_line_slice_end, oracle_line_slice_begin, oracle_line_slice_end);
                    bool unused = std::find(current_assignment.begin(), current_assignment.end(), j) == current_assignment.end();

                    line_matched = found && unused;
                    if(line_matched){ ///current t_line matched
                        current_assignment[i] = j;
                        break;
                    }

                }
                std::cout<<std::endl;
                if(!line_matched){ ///t_line unmatchable
                    break;
                }
            }
            ///matching end

            for(ulong i = 0; i<current_assignment.size(); ++i) {
                std::cout << i << ": " << current_assignment[i] << std::endl;
            }
            //// CHECK FULL MATCH


        }
        cut += 1;
        delta += 2;
    }


    std::cout<<std::endl;
    ////asd////


    std::cout<<std::endl;


}