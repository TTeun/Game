//
// Created by pc on 4/26/20.
//

#ifndef TEUN_GAME_UNIFORM_H
#define TEUN_GAME_UNIFORM_H

#include <cstddef>

namespace Aux {

    class Uniform {

    public:
        Uniform(size_t min, size_t range);

        size_t get() const;

    private:
        size_t m_min = 0ul;

        size_t m_range;
    };
} // namespace Aux
#endif // TEUN_GAME_UNIFORM_H
