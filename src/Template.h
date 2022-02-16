//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//

#ifndef Q_OPT_TEMPLATE_H
#define Q_OPT_TEMPLATE_H


#include "Circuit.h"

class Template : public Circuit {
public:
    explicit Template(const std::vector<std::vector<int>> &operations);

    explicit Template(const std::string &filename);

    std::vector<int> get_line(long line_index);
};


#endif //Q_OPT_TEMPLATE_H
