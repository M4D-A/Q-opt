//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//

#ifndef Q_OPT_CIRCUIT_H
#define Q_OPT_CIRCUIT_H

#include <vector>
#include <string>

enum operation {
    NOT = 0,
    CNOT = 1,
    TOFF = 2
};

enum block {
    EMPTY = 0,
    NOT_X = 1,
    CNOT_X = 2,
    TOFF_X = 3,
    CNOT_C = 4,
    TOFF_C = 5
};

class Circuit {

protected:
    std::vector<std::vector<ulong>> operations;

    std::vector<ulong> operation_ids;

    std::vector<std::vector<ulong>> lines;

    void init(const std::vector<std::vector<ulong>> &operations);


public:
    explicit Circuit(const std::vector<std::vector<ulong>> &operations);

    explicit Circuit(const std::string &filename);

    void add_operation(const std::vector<ulong> &new_operation);

    void print_operations();

    std::vector<ulong> get_operation_ids();

    std::vector<std::vector<ulong>> get_lines();

    void print_lines(bool verbose = false);

    void print_operation_ids();
};

#endif //Q_OPT_CIRCUIT_H
