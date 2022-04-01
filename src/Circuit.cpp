//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//

#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <fstream>
#include <utility>
#include "../headers/Circuit.h"

Circuit::Circuit(std::vector<std::vector<long>> new_operations) : operations(std::move(new_operations)) {
    init();
}

Circuit::Circuit(const std::string &filename) {
    std::ifstream input_file(filename);
    std::string line;
    while (getline(input_file, line)) {
        std::stringstream line_stream{line};
        std::vector<long> uint_vector;
        std::copy(std::istream_iterator<long>(line_stream),
                  std::istream_iterator<long>(),
                  std::back_inserter(uint_vector)
        );
        operations.push_back(uint_vector);
    }
    init();
}

void Circuit::init() {
    gate_line = std::vector<long>(operations.size());

    ulong lines_number = 0;
    for (ulong i = 0; i < operations.size(); ++i) {
        ulong operation_max = *std::max_element(operations[i].begin(), operations[i].end());
        lines_number = std::max(lines_number, operation_max);
        gate_line[i] = (long)operations[i].size();
    }

    lines_number += 1;
    block_lines = std::vector<std::vector<long>>(lines_number);

    for (int i = 0; i < lines_number; i++) {
        block_lines[i] = std::vector<long>(operations.size(), 0);
    }

    int i = 0;
    for (auto operation: operations) {
        switch (operation.size()) {
            case 1: {
                block_lines[operation[0]][i] = NOT_X;
                break;
            }
            case 2: {
                block_lines[operation[0]][i] = CNOT_X;
                block_lines[operation[1]][i] = CNOT_C;
                break;
            }
            case 3: {
                block_lines[operation[0]][i] = TOFF_X;
                block_lines[operation[1]][i] = TOFF_C;
                block_lines[operation[2]][i] = TOFF_C;
                break;
            }
        }
        i++;
    }
}

void Circuit::add_operation(const std::vector<long> &new_operation) {
    if (!new_operation.empty() && new_operation.size() <= 3) {
        operations.push_back(new_operation);
    }
    else{
        return;
    }

    ulong current_line_length = block_lines[0].size();
    ulong max_line = *std::max_element(new_operation.begin(), new_operation.end());

    while(block_lines.size() <= max_line){
        block_lines.emplace_back(current_line_length, EMPTY);
    }

    for (auto &line: block_lines) {
        line.push_back(EMPTY);
    }

    unsigned int last_layer = operations.size() - 1;

    switch (new_operation.size() - 1) {
        case NOT: {
            block_lines[new_operation[0]][last_layer] = NOT_X;
            break;
        }
        case CNOT: {
            block_lines[new_operation[0]][last_layer] = CNOT_X;
            block_lines[new_operation[1]][last_layer] = CNOT_C;
            break;
        }
        case TOFF: {
            block_lines[new_operation[0]][last_layer] = TOFF_X;
            block_lines[new_operation[1]][last_layer] = TOFF_C;
            block_lines[new_operation[2]][last_layer] = TOFF_C;
            break;
        }
    }
}

void Circuit::print_operations() {
    for (const auto &operation: operations) {
        switch (operation.size()) {
            case 1:
                std::cout << "N: " << operation[0];
                break;
            case 2:
                std::cout << "C: " << operation[0] << " | " << operation[1];
                break;
            case 3:
                std::cout << "T: " << operation[0] << " | " << operation[1] << " " << operation[2];
                break;
        }
        std::cout << std::endl;
    }
}

void Circuit::print(bool verbose) {
    std::cout << "---";
    for (auto G: gate_line) {
        std::cout << "--";
    }
    std::cout << std::endl;

    std::cout << "   ";
    for (int i = 0; i < operations.size(); ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    int i = 0;
    for (const auto &line: block_lines) {
        std::cout << i << ": ";
        for (ulong block: line) {
            if (verbose) {
                std::cout << block;
            } else
                switch (block) {
                    case EMPTY:
                        std::cout << "-";
                        break;
                    case NOT_X:
                    case CNOT_X:
                    case TOFF_X:
                        std::cout << "X";
                        break;
                    case CNOT_C:
                    case TOFF_C:
                        std::cout << "C";
                        break;
                    default:
                        std::cout << "?";
                        break;
                }
            std::cout << "-";
        }
        std::cout << std::endl;
        ++i;
    }

    std::cout << "---";
    for (auto G: gate_line) {
        std::cout << "--";
    }
    std::cout << std::endl;

    std::cout << "G: ";
    for (auto G: gate_line) {
        std::cout << G << "-";
    }
    std::cout << std::endl;
}

std::vector<long> Circuit::get_operation_ids() {
    return gate_line;
}

std::vector<std::vector<long>> Circuit::get_block_lines() {
    return block_lines;
}

Circuit::Circuit() {
    init();
}

