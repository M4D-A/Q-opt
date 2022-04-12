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

bool Circuit::validate_operation(std::vector<long> operation) {
    bool size_ok = !operation.empty() && operation.size() <= 3;
    ///check for line index duplicates
    std::sort(operation.begin(), operation.end());
    auto it = std::unique(operation.begin(), operation.end());
    bool unique = (it == operation.end());
    return size_ok && unique;
}

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

Circuit::Circuit() {
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
    insert_operation(new_operation, get_length());
}

void Circuit::insert_operation(const std::vector<long> &new_operation, long index) {
    long type = (long)(new_operation.size());

    if(index < 0 || index > get_length()){
        throw std::invalid_argument( "Index value must be between 0 and length of circuit" );
    }

    if (!validate_operation(new_operation)){
        throw std::invalid_argument( "Operation does not exist" );
    }

    operations.insert(operations.begin() + index, new_operation);
    gate_line.insert(gate_line.begin()+ index, type);

    ulong current_line_length = get_length();
    ulong max_line = *std::max_element(new_operation.begin(), new_operation.end());

    while(block_lines.size() <= max_line){
        block_lines.emplace_back(current_line_length, EMPTY);
    }

    for (auto &line: block_lines) {
        line.insert(line.begin() + index, EMPTY);
    }

    switch (type - 1) {
        case NOT: {
            block_lines[new_operation[0]][index] = NOT_X;
            break;
        }
        case CNOT: {
            block_lines[new_operation[0]][index] = CNOT_X;
            block_lines[new_operation[1]][index] = CNOT_C;
            break;
        }
        case TOFF: {
            block_lines[new_operation[0]][index] = TOFF_X;
            block_lines[new_operation[1]][index] = TOFF_C;
            block_lines[new_operation[2]][index] = TOFF_C;
            break;
        }
    }
}

void Circuit::replace_operation(const std::vector<long> &new_operation, long index) {
    long type = (long)(new_operation.size());
    if(index < 0 || index >= get_length()){
        throw std::invalid_argument( "Index value must be between 0 and length of circuit - 1" );
    }

    if (!validate_operation(new_operation)){
        throw std::invalid_argument( "Operation does not exist" );
    }

    operations[index] = new_operation;
    gate_line[index] = type;

    for(auto &line : block_lines){
        line[index] = EMPTY;
    }

    ulong current_line_length = get_length();
    ulong max_line = *std::max_element(new_operation.begin(), new_operation.end());

    while(block_lines.size() <= max_line){
        block_lines.emplace_back(current_line_length, EMPTY);
    }

    switch (type - 1) {
        case NOT: {
            block_lines[new_operation[0]][index] = NOT_X;
            break;
        }
        case CNOT: {
            block_lines[new_operation[0]][index] = CNOT_X;
            block_lines[new_operation[1]][index] = CNOT_C;
            break;
        }
        case TOFF: {
            block_lines[new_operation[0]][index] = TOFF_X;
            block_lines[new_operation[1]][index] = TOFF_C;
            block_lines[new_operation[2]][index] = TOFF_C;
            break;
        }
    }
}

long Circuit::get_width() {
    return (long)block_lines.size();
}

long Circuit::get_length() {
    return (long)gate_line.size();
}

std::vector<long> Circuit::get_operation_ids() {
    return gate_line;
}

std::vector<std::vector<long>> Circuit::get_block_lines() {
    return block_lines;
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
    for (int i = 0; i < get_length(); ++i) {
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







