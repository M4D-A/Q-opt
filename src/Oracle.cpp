//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//
#include "../headers/Oracle.h"

Oracle::Oracle(const std::string &filename) : Circuit(filename) {}

Oracle::Oracle(const std::vector<std::vector<ulong>> &operations) : Circuit(operations) {}