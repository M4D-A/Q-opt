//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//

#include "headers/Oracle.h"
#include "headers/Template.h"

int main() {
    Oracle o("oracle.qc");
    o.print(true);
    o.replace_operation({1,3},0);
    o.print(true);
}