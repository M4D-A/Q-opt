//
// Created by adam on 17.02.2022.
//

#include "../headers/LineMatch.h"

LineMatch::LineMatch(Oracle *oracle, Template *template_,
                     ulong oracle_line, ulong template_line,
                     ulong oracle_start, ulong oracle_end,
                     ulong template_start, ulong template_end,
                     bool template_direction) :
        oracle(oracle), template_(template_),
        oracle_line(oracle_line), template_line(template_line),
        oracle_start(oracle_start), oracle_end(oracle_end),
        template_start(template_start), template_end(template_end), template_direction(template_direction) {}



