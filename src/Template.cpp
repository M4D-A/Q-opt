//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//

#include "../headers/Template.h"

Template::Template(const std::vector<std::vector<long>> &operations) : Circuit(operations) {}

Template::Template(const std::string &filename) : Circuit(filename) {}