//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//

#ifndef Q_OPT_AUXILIARY_H
#define Q_OPT_AUXILIARY_H

#include <vector>

class Auxiliary {
public:
    static std::vector<ulong> xor_vectors(std::vector<ulong>::iterator a_start,
                                        std::vector<ulong>::iterator a_stop,
                                        std::vector<ulong>::iterator b_start,
                                        std::vector<ulong>::iterator b_stop
    );

    static std::vector<ulong> longest_zero_subsequence(std::vector<ulong> vec);

    static void print_vec(std::vector<ulong>::iterator begin, std::vector<ulong>::iterator end);
};

#endif //Q_OPT_AUXILIARY_H
