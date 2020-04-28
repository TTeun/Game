//
// Created by pc on 4/27/20.
//

#ifndef SFML_FINITEDURATION_H
#define SFML_FINITEDURATION_H

namespace Physics {

    class FiniteDuration {

    public:
        virtual bool shouldClean() const = 0;
    };
} // namespace Physics

#endif // SFML_FINITEDURATION_H
