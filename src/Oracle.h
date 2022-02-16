//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//

#ifndef Q_OPT_ORACLE_H
#define Q_OPT_ORACLE_H

#include "Circuit.h"

class Oracle : public Circuit {
public:
    explicit Oracle(const std::vector<std::vector<int>> &operations);

    explicit Oracle(const std::string &filename);

    std::vector<std::vector<int>> line_matches(std::vector<int>::iterator match_start,
                                               std::vector<int>::iterator match_end);
};

#endif //Q_OPT_ORACLE_H
