//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//
#include "../headers/Oracle.h"

Oracle::Oracle(const std::string &filename) : Circuit(filename) {}

Oracle::Oracle(const std::vector<std::vector<long>> &operations) : Circuit(operations) {}

Match Oracle::match_template(Template* template_, long initial_shift, long delta_threshold){
    auto template_gate_line = template_->get_operation_ids();
    long template_length = (long)template_gate_line.size(); ///L
    long oracle_length = (long)gate_line.size(); ///N

    /// <Slicing>
    long template_begin_index, template_end_index;
    long oracle_begin_index, oracle_end_index;
    if(initial_shift < 0){
        template_begin_index = -initial_shift;
        oracle_begin_index = 0;
    }
    else{
        template_begin_index = 0;
        oracle_begin_index = initial_shift;
    }

    if(initial_shift + template_length > oracle_length){
        template_end_index = oracle_length - initial_shift;
        oracle_end_index = oracle_length;
    }
    else{
        template_end_index = template_length;
        oracle_end_index = template_length + initial_shift;
    }
    /// </Slicing>

    /// <Gate Line Matching>
    auto initial_gate_match =  match_line(
            gate_line.begin() + oracle_begin_index,
            gate_line.begin() + oracle_end_index,
            template_gate_line.begin() + template_begin_index,
            template_gate_line.begin() + template_end_index
    );
    long gate_match_shift = std::get<0>(initial_gate_match);
    long oracle_gate_match_begin_index = oracle_begin_index + gate_match_shift;
    long template_gate_match_begin_index = template_begin_index + gate_match_shift;
    long gate_match_length = std::get<1>(initial_gate_match);
    /// </Gate Line Matching>

    Match found_match(this, template_);

    /// <Block Lines Matching>
    auto template_block_lines = template_->get_block_lines();

    long substitution_length = template_length - gate_match_length;
    long delta = substitution_length - gate_match_length; // delta > 0 = bad, delta < 0 = good

    long cut_length = 0;
    long slice_length = gate_match_length - cut_length;
    bool full_match = false;
    while(delta <= delta_threshold && slice_length > 0 && !full_match){ //// cut_length
        slice_length = gate_match_length - cut_length;

        for(long slice_shift = 0; slice_shift <= cut_length; slice_shift++){ //// slice_shift
            long template_slice_begin_index = template_gate_match_begin_index + slice_shift;
            long template_slice_end_index = template_slice_begin_index + slice_length;
            long oracle_slice_begin_index = oracle_gate_match_begin_index + slice_shift;
            long oracle_slice_end_index = oracle_slice_begin_index + slice_length;

            ///<Current slice matching>
            std::vector<long> assignment(template_block_lines.size(), -1);
            for(long i = 0; i < template_block_lines.size(); ++i) { //// t_line
                bool line_matched = false;
                auto template_line_begin = template_block_lines[i].begin();
                auto template_line_slice_begin = template_line_begin + template_slice_begin_index;
                auto template_line_slice_end = template_line_begin + template_slice_end_index;
                for (long j = 0; j < block_lines.size(); ++j) { //// o_line
                    auto oracle_line_begin = block_lines[j].begin();
                    auto oracle_line_slice_begin = oracle_line_begin + oracle_slice_begin_index;
                    auto oracle_line_slice_end = oracle_line_begin + oracle_slice_end_index;

                    bool line_matching = std::equal(template_line_slice_begin,
                                                    template_line_slice_end,
                                                    oracle_line_slice_begin,
                                                    oracle_line_slice_end);

                    bool line_unused = std::find(assignment.begin(),
                                                 assignment.end(),
                                                 j
                                                 ) == assignment.end();

                    line_matched = line_matching && line_unused;
                    if(line_matched){ ///current t_line matched
                        assignment[i] = j;
                        break;
                    }
                }
                if(!line_matched){ ///t_line unmatchable
                    break;
                }
            }
            ///</Current slice matching>

            full_match = std::all_of(assignment.begin(),
                                     assignment.end(),
                                     [](int i){return i > -1;}
                                     ); ///verify match

            if(full_match){
                found_match.setFound(true);
                found_match.setAssignment(assignment);
                found_match.setOracleMatchStart(oracle_gate_match_begin_index + slice_shift);
                found_match.setTemplateMatchStart(template_gate_match_begin_index + slice_shift);
                found_match.setDelta(delta);
                found_match.setMatchLength(gate_match_length - cut_length);
                break;
            }
            ///Shift slice
        }
        ///Shorten slice
        cut_length += 1;
        delta += 2;
    }
    /// </Block Lines Matching>

    return found_match;
}

std::tuple<long,long> Oracle::match_line(std::vector<long>::iterator a_start,
                                           std::vector<long>::iterator a_stop,
                                           std::vector<long>::iterator b_start,
                                           std::vector<long>::iterator b_stop) {

    size_t x_size = std::min(a_stop - a_start, b_stop - b_start);
    auto xor_value = std::vector<long>(x_size);
    for (auto x_iter = xor_value.begin();
         a_start != a_stop && b_start != b_stop;
         ++a_start, ++b_start, ++x_iter) {
        *x_iter = *a_start ^ *b_start;
    }

    long max_start = 0;
    long max_length = 0;
    long current_start = 0;
    long current_length = 0;

    for (long k = 0; k < (long)xor_value.size(); ++k) {
        if (xor_value[k] == 0) {
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
    return {max_start, max_length};
}

