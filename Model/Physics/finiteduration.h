//
// Created by pc on 4/27/20.
//

#ifndef TEUN_GAME_FINITEDURATION_H
#define TEUN_GAME_FINITEDURATION_H

namespace Model {

    namespace Physics {

        class FiniteDuration {

        public:
            virtual bool shouldClean() const = 0;
        };
    } // namespace Physics
} // namespace Model
#endif // TEUN_GAME_FINITEDURATION_H
