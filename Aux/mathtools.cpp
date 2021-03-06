//
// Created by pc on 4/28/20.
//

#include "mathtools.h"

#include <cassert>

float Aux::square(float a)
{
    return a * a;
}

float Aux::clamp(float a, float min, float max)
{
    assert(min < max);
    if (a < min) {
        return min;
    } else if (a > max) {
        return max;
    }
    return a;
}
