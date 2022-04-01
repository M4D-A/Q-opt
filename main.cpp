//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//

#include "headers/Oracle.h"
#include "headers/Template.h"

int main() {
    Oracle o("oracle.qc");
    Template t("template.qc");
    Match m = o.match_template(&t, 6,5);
    m.print();

}