//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//

#ifndef Q_OPT_ORACLE_H
#define Q_OPT_ORACLE_H

#include "Circuit.h"
#include "Template.h"
#include "Match.h"
#include <algorithm>
#include <tuple>

class Match;
class Template;

class Oracle : public Circuit {

private:
    static std::tuple<long, long> match_line(std::vector<long>::iterator a_start,
                                          std::vector<long>::iterator a_stop,
                                          std::vector<long>::iterator b_start,
                                          std::vector<long>::iterator b_stop
    );

public:
    explicit Oracle(const std::vector<std::vector<long>> &operations);

    explicit Oracle(const std::string &filename);

    Match match_template(Template* template_, long initial_shift, long delta_threshold);

};

#endif //Q_OPT_ORACLE_H
