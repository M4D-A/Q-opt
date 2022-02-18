//
// Created by adam on 17.02.2022.
//

#ifndef Q_OPT_LINEMATCH_H
#define Q_OPT_LINEMATCH_H

#include "Oracle.h"
#include "Template.h"

class Oracle;

class Template;

class LineMatch {
    static const bool RIGHT = true;
    static const bool LEFT = false;

    Oracle *oracle;
    Template *template_;

    ulong oracle_line;
    ulong template_line;

    ulong oracle_start;
    ulong oracle_end;
    ulong template_start;
    ulong template_end;

    bool template_direction = RIGHT;

public:
    LineMatch(Oracle *oracle, Template *template_, ulong oracle_line, ulong template_line, ulong oracle_start,
              ulong oracle_end, ulong template_start, ulong template_end, bool template_direction);
};


#endif //Q_OPT_LINEMATCH_H
