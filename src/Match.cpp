//
// Created by adam on 29.03.2022.
//

#include "../headers/Match.h"

#include <utility>

Match::Match(Oracle *parent_oracle_in, Template *parent_template_in) :
        parent_oracle(parent_oracle_in), parent_template(parent_template_in) {
}

void Match::setFound(bool found_in) {
    found = found_in;
}

void Match::setTemplateMatchStart(long template_match_start_in) {
    template_match_start = template_match_start_in;
}

void Match::setOracleMatchStart(long oracle_match_start_in) {
    oracle_match_start = oracle_match_start_in;
}

void Match::setMatchLength(long match_length_in) {
    match_length = match_length_in;
}

void Match::setDelta(long delta_in) {
    delta = delta_in;
}

void Match::setAssignment(std::vector<long> assignment_in) {
    assignment = std::move(assignment_in);
}

void Match::print() {
    parent_oracle->print(true);
    std::cout<<std::endl;

    parent_template->print(true);
    std::cout<<std::endl;

    if(found){
        std::cout<<"Template match start: "<<template_match_start<<std::endl;
        std::cout<<"Oracle start: "<<oracle_match_start<<std::endl;
        std::cout<<"Match length: "<<match_length<<std::endl;
    }
    else{
        std::cout<<"Match empty: "<<std::endl;
    }
}

