//
// Created by M4DA - Adam Jagielski, jagielski.adamm@gmail.com
//

#ifndef Q_OPT_AUXILIARY_H
#define Q_OPT_AUXILIARY_H

#include <vector>

class Auxiliary {
public:
    static std::vector<int> xor_vectors(std::vector<int>::iterator a_start,
                                        std::vector<int>::iterator a_stop,
                                        std::vector<int>::iterator b_start,
                                        std::vector<int>::iterator b_stop
    );

    static void longest_zero_subsequence(std::vector<int> vec);
};

#endif //Q_OPT_AUXILIARY_H
