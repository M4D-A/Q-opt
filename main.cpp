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
    long delta_threshold = 1; //max acceptable loss

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

    std::vector<ulong> assignment;
    ulong final_template_match_start;
    ulong final_oracle_match_start;
    ulong final_match_length;

    ulong cut = 0;
    long delta = initial_delta;
    bool full_match = false;
    while(delta <= delta_threshold && (initial_match_length - cut) > 0 && !full_match){ //// cut
        for(ulong cut_shift = 0; cut_shift <= cut; cut_shift++){ //// cut_shift

            ulong template_slice_begin_index = initial_template_match_start + cut_shift;
            ulong template_slice_end_index = template_slice_begin_index + initial_match_length - cut;
            ulong oracle_slice_begin_index = initial_oracle_match_start + cut_shift;
            ulong oracle_slice_end_index = oracle_slice_begin_index + initial_match_length - cut;

            std::vector<ulong> current_assignment(template_lines.size(), -1);

            ///matching start
            bool line_matched = false;
            for(ulong i = 0; i < template_lines.size(); ++i) { //// t_line
                line_matched = false;
                auto template_line_begin = template_lines[i].begin();
                auto template_line_slice_begin = template_line_begin + template_slice_begin_index;
                auto template_line_slice_end = template_line_begin + template_slice_end_index;
                for (ulong j = 0; j < oracle_lines.size(); ++j) { //// o_line
                    auto oracle_line_begin = oracle_lines[j].begin();
                    auto oracle_line_slice_begin = oracle_line_begin + oracle_slice_begin_index;
                    auto oracle_line_slice_end = oracle_line_begin + oracle_slice_end_index;

                    bool found = std::equal(template_line_slice_begin, template_line_slice_end, oracle_line_slice_begin, oracle_line_slice_end);
                    bool unused = std::find(current_assignment.begin(), current_assignment.end(), j) == current_assignment.end();

                    line_matched = found && unused;
                    if(line_matched){ ///current t_line matched
                        current_assignment[i] = j;
                        break;
                    }
                }
                if(!line_matched){ ///t_line unmatchable
                    break;
                }
            }
            if(line_matched){
                full_match = true;
                assignment = current_assignment;
                final_template_match_start = initial_template_match_start + cut_shift;
                final_oracle_match_start = initial_oracle_match_start + cut_shift;
                final_match_length = initial_match_length - cut;
                break;
            }
        }
        cut += 1;
        delta += 2;
    }

    if(full_match) {
        std::cout << "Final Oracle match start:   " << final_oracle_match_start << std::endl;
        std::cout << "Final Template match start: " << final_template_match_start << std::endl;
        std::cout << "Final Match length:         " << final_match_length << std::endl;
        std::cout << std::endl;
        for (int i = 0; i < assignment.size(); i++) {
            auto test_template_start = template_lines[i].begin() + final_template_match_start;
            auto test_template_end = test_template_start + final_match_length;

            auto oracle_index = assignment[i];
            auto test_oracle_start = oracle_lines[oracle_index].begin() + final_oracle_match_start;
            auto test_oracle_end = test_oracle_start + final_match_length;

            std::cout << i << ": " << oracle_index << std::endl;
            Auxiliary::print_vec(test_template_start, test_template_end);
            Auxiliary::print_vec(test_oracle_start, test_oracle_end);
            std::cout << std::endl;
        }
    }
    else{
        std::cout << "Matching Failed" << std::endl;
    }
}