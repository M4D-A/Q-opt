//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//

#include "../headers/Template.h"

Template::Template(const std::vector<std::vector<int>> &operations) : Circuit(operations) {}

Template::Template(const std::string &filename) : Circuit(filename) {}

std::vector<int> Template::get_line(ulong line_index) {
    return lines[line_index];
}