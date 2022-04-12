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

    std::vector<std::vector<long>> operations;

    std::vector<long> gate_line;

    std::vector<std::vector<long>> block_lines;

    void init();


public:
    explicit Circuit(std::vector<std::vector<long>> operations);

    explicit Circuit(const std::string &filename);

    explicit Circuit();

    void add_operation(const std::vector<long> &new_operation);

    void insert_operation(const std::vector<long> &new_operation, long index);

    void replace_operation(const std::vector<long> &new_operation, long index);

    long get_length();

    long get_width();

    std::vector<long> get_operation_ids();

    std::vector<std::vector<long>> get_block_lines();

    void print_operations();

    void print(bool verbose = false);

    static bool validate_operation(std::vector<long> operation);
};

#endif //Q_OPT_CIRCUIT_H
