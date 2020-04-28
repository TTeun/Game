//
// Created by pc on 4/26/20.
//

#ifndef SFML_UNIFORM_H
#define SFML_UNIFORM_H

#include <cstddef>

class Uniform {

public:
    Uniform(size_t min, size_t range);

    size_t get() const;

private:
    size_t m_min = 0ul;

    size_t m_range;
};

#endif // SFML_UNIFORM_H
