//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//

#ifndef Q_OPT_ORACLE_H
#define Q_OPT_ORACLE_H

#include "Circuit.h"

class Oracle : public Circuit {
public:
    explicit Oracle(const std::vector<std::vector<ulong>> &operations);

    explicit Oracle(const std::string &filename);
};

#endif //Q_OPT_ORACLE_H
