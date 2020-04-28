//
// Created by pc on 4/28/20.
//

#ifndef SFML_MATHTOOLS_H
#define SFML_MATHTOOLS_H

namespace MathTools {

    float square(float a);

    bool liesIsInterval(float point, float left, float right, float buffer = 0.01f);

} // namespace MathTools

#endif // SFML_MATHTOOLS_H
