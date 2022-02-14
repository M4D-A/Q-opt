//
// Created by M4DA, jagielski.adamm@gmail.com
//

#ifndef Q_OPT_CIRCUIT_H
#define Q_OPT_CIRCUIT_H


#include <vector>
#include <string>

class Circuit {
    std::vector<std::vector<int>> operations;
    std::vector<std::vector<int>> lines;

public:
    Circuit(const std::vector<std::vector<int>>& operations);
    Circuit(const std::string& filename);
    void add_operation(const std::vector<int>& new_operation);
    void print_operations();
    void print_lines();
};


#endif //Q_OPT_CIRCUIT_H
