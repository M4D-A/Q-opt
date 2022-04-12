//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//

#ifndef Q_OPT_TEMPLATE_H
#define Q_OPT_TEMPLATE_H

#include "Circuit.h"

class Template : public Circuit {
public:
    explicit Template(const std::vector<std::vector<long>> &operations);

    explicit Template(const std::string &filename);
};

#endif //Q_OPT_TEMPLATE_H
