//
// Created by pc on 4/27/20.
//

#include "uniform.h"

#include <cstdlib>

Uniform::Uniform(size_t min, size_t range) : m_min(min), m_range(range)
{
}

size_t Uniform::get() const
{
    if (m_range == 0) {
        return m_min;
    }
    return m_min + rand() % m_range;
}
