//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//

#ifndef Q_OPT_ORACLE_H
#define Q_OPT_ORACLE_H

#include <algorithm>
#include <iostream>
#include "Circuit.h"
#include "LineMatch.h"
#include "Template.h"
#include "../headers/Auxiliary.h"

class LineMatch;

class Template;

class Oracle : public Circuit {
public:
    explicit Oracle(const std::vector<std::vector<int>> &operations);

    explicit Oracle(const std::string &filename);

    std::vector<LineMatch> line_matches(Template template_, ulong line_index, ulong threshold);
};

#endif //Q_OPT_ORACLE_H
