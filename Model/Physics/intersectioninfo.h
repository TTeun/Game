//
// Created by pc on 4/26/20.
//

#ifndef SFML_INTERSECTIONINFO_H
#define SFML_INTERSECTIONINFO_H

#include <tuple>

class IntersectionInfo {

public:
    enum class Type { TopToBottom, BottomToTop, LeftToRight, RightToLeft, DoubleHorizonTal, DoubleVertical, None };

    void setLeftToRight(float s);

    void setTopToBottom(float s);

    void setRightToLeft(float s);

    void setBottomToTop(float s);

    float min() const;

    void update(const IntersectionInfo & other);

    std::pair<float, Type> horizontalIntersection() const;

    std::pair<float, Type> verticalIntersection() const;

    Type type() const;

    float m_topToBottom = 1.0f;
    float m_leftToRight = 1.0f;
    float m_bottomToTop = 1.0f;
    float m_rightToLeft = 1.0f;
};

#endif // SFML_INTERSECTIONINFO_H
