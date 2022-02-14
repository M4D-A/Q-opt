//
// Created by M4DA, jagielski.adamm@gmail.com
//

#include <iostream>
#include <algorithm>
#include "Circuit.h"
#define EMPTY 0
#define NOT_X 1
#define CNOT_X 2
#define TOFF_X 3
#define CNOT_C 4
#define TOFF_C 5

Circuit::Circuit(const std::vector<std::vector<int>>& operations) : operations(operations){
    int lines_number = 0;
    for(std::vector<int> operation : operations){
        int operation_max = *std::max_element(operation.begin(), operation.end());
        lines_number = std::max(lines_number, operation_max);
    }
    lines_number+=1;
    lines = std::vector<std::vector<int>>(lines_number);

    for(int i = 0; i<lines_number; i++){
        lines[i] = std::vector<int>(operations.size(),0);
    }

    int i = 0;
    for(std::vector<int> operation : operations){
        switch(operation.size()){
            case 1: {
                lines[operation[0]][i] = NOT_X;
                break;
            }
            case 2: {
                lines[operation[0]][i] = CNOT_X;
                lines[operation[1]][i] = CNOT_C;
                break;
            }
            case 3: {
                lines[operation[0]][i] = TOFF_X;
                lines[operation[1]][i] = TOFF_C;
                lines[operation[2]][i] = TOFF_C;
                break;
            }
        }
        i++;
    }
}

Circuit::Circuit(const std::string& filename){

}

void Circuit::add_operation(const std::vector<int>& new_operation) {
    if(!new_operation.empty() && new_operation.size() <= 3){
        operations.push_back(new_operation);
    }

    for(std::vector<int> &line : lines){
        line.push_back(EMPTY);
    }

    unsigned int last_layer = operations.size() - 1;

    switch(new_operation.size()){
        case 1: {
            lines[new_operation[0]][last_layer] = NOT_X;
            break;
        }
        case 2: {
            lines[new_operation[0]][last_layer] = CNOT_X;
            lines[new_operation[1]][last_layer] = CNOT_C;
            break;
        }
        case 3: {
            lines[new_operation[0]][last_layer] = TOFF_X;
            lines[new_operation[1]][last_layer] = TOFF_C;
            lines[new_operation[2]][last_layer] = TOFF_C;
            break;
        }
    }
}

void Circuit::print_operations() {
    for(const std::vector<int>& operation : operations){
        switch(operation.size()){
            case 1: std::cout<<"N: " << operation[0]; break;
            case 2: std::cout<<"C: " << operation[0] << " | " << operation[1];  break;
            case 3: std::cout<<"T: " << operation[0] << " | " << operation[1] << " " << operation[2]; break;
        }
        std::cout<<std::endl;
    }
}

void Circuit::print_lines() {
    std::cout<<"   ";
    for(int i = 0; i < operations.size(); ++i){
        std::cout<<i<<" ";
    }
    std::cout<<std::endl;

    int i = 0;
    for(const auto& line : lines){
        std::cout<<i<<": ";
        for(auto block : line){
            switch(block){
                case EMPTY:  std::cout<<"-"; break;
                case NOT_X:
                case CNOT_X:
                case TOFF_X: std::cout<<"X"; break;
                case CNOT_C:
                case TOFF_C: std::cout<<"C"; break;
                default: std::cout<<"?"; break;
            }
            std::cout<<"-";
        }
        std::cout<<std::endl;
        ++i;
    }
}

