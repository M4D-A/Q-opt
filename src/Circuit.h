//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//

#ifndef Q_OPT_CIRCUIT_H
#define Q_OPT_CIRCUIT_H

#include <vector>
#include <string>

class Circuit {
protected:
    std::vector<std::vector<int>> operations;
    std::vector<std::vector<int>> lines;

    void init(const std::vector<std::vector<int>> &operations);

public:
    explicit Circuit(const std::vector<std::vector<int>> &operations);

    explicit Circuit(const std::string &filename);

    void add_operation(const std::vector<int> &new_operation);

    void print_operations();

    void print_lines(bool verbose = false);
};

#endif //Q_OPT_CIRCUIT_H
