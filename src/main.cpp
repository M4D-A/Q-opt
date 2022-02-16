//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//

#include "Oracle.h"
#include "Template.h"
#include <iostream>

int main() {
    Oracle o("oracle.qc");
    Template t("template.qc");


    o.print_lines(true);
    t.print_lines(true);

    auto line = t.get_line(2);

    auto matches = o.line_matches(line.begin(), line.begin() + 3);
    for (auto match: matches) {
        for (auto item: match) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
}