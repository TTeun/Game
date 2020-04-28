//
// Created by pc on 4/28/20.
//

#include "mathtools.h"
float MathTools::square(float a)
{
    return a * a;
}

bool MathTools::liesIsInterval(float point, float left, float right, float buffer)
{
    return point <= right - buffer && point >= left + buffer;
}
