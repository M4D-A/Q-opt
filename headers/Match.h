//
// Created by adam on 29.03.2022.
//

#ifndef Q_OPT_MATCH_H
#define Q_OPT_MATCH_H
#include <cstdlib>
#include <vector>
#include <iostream>
#include "Oracle.h"
#include "Template.h"

class Oracle;
class Template;

class Match {
    Oracle* parent_oracle;
    Template* parent_template;
    bool found = false;

    long template_match_start = -1;
    long oracle_match_start = -1;
    long match_length = -1;
    long delta = -1;
    std::vector<long> assignment;

public:
    Match(Oracle *parent_oracle_in, Template *parent_template_in);

    void setFound(bool found_in);

    void setTemplateMatchStart(long template_match_start_in);

    void setOracleMatchStart(long oracle_match_start_in);

    void setMatchLength(long match_length_in);

    void setDelta(long delta_in);

    void setAssignment(std::vector<long> assignment_in);

    void print();
};

#endif //Q_OPT_MATCH_H
