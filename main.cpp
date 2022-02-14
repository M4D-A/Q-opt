//
// Created by M4DA, jagielski.adamm@gmail.com
//

#include "Circuit.h"
#include <vector>
int main () {
    std::vector<std::vector<int>> ops = {
            {0},
            {1},
            {1,2},
            {2,3},
            {4,0},
            {1,2,4},
            {2,3,4},
            {4}
    };
    Circuit circ(ops);
    circ.add_operation({3,2,1});
    circ.print_operations();
    circ.print_lines();
}