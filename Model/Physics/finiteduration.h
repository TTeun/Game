//
// Created by pc on 4/27/20.
//

#ifndef TEUN_GAME_FINITEDURATION_H
#define TEUN_GAME_FINITEDURATION_H

#include <ostream>

namespace Model {

    namespace Physics {

        class FiniteDuration {

        public:
            virtual bool shouldClean() const = 0;

            friend std::ostream &operator<<(std::ostream &os, const FiniteDuration &duration) {
                return os;
            }
        };
    } // namespace Physics
} // namespace Model
#endif // TEUN_GAME_FINITEDURATION_H
