//
// Created by pc on 4/26/20.
//

#include "intersectioninfo.h"

void IntersectionInfo::setLeftToRight(float s)
{
    if (s < m_leftToRight && s >= 0.0f) {
        m_leftToRight = s;
    }
}

void IntersectionInfo::setTopToBottom(float s)
{
    if (s < m_topToBottom && s >= 0.0f) {
        m_topToBottom = s;
    }
}

void IntersectionInfo::setRightToLeft(float s)
{
    if (s < m_rightToLeft && s >= 0.0f) {
        m_rightToLeft = s;
    }
}

void IntersectionInfo::setBottomToTop(float s)
{
    if (s < m_bottomToTop && s >= 0.0f) {
        m_bottomToTop = s;
    }
}

float IntersectionInfo::min() const
{
    return std::min(m_topToBottom, std::min(m_bottomToTop, std::min(m_rightToLeft, m_leftToRight)));
}

void IntersectionInfo::update(const IntersectionInfo & other)
{
    setBottomToTop(other.m_bottomToTop);
    setTopToBottom(other.m_topToBottom);
    setLeftToRight(other.m_leftToRight);
    setRightToLeft(other.m_rightToLeft);
}

std::pair<float, IntersectionInfo::Type> IntersectionInfo::horizontalIntersection() const
{
    if (m_leftToRight < m_rightToLeft) {
        return std::make_pair(m_leftToRight, Type::LeftToRight);
    } else if (m_rightToLeft < m_leftToRight) {
        return std::make_pair(m_rightToLeft, Type::RightToLeft);
    } else if (m_leftToRight >= 1.0f) {
        return std::make_pair(1.0f, Type::None);
    }
    return std::make_pair(m_rightToLeft, Type::DoubleHorizonTal);
}

std::pair<float, IntersectionInfo::Type> IntersectionInfo::verticalIntersection() const
{
    if (m_topToBottom < m_bottomToTop) {
        return std::make_pair(m_topToBottom, Type::TopToBottom);
    } else if (m_bottomToTop < m_topToBottom) {
        return std::make_pair(m_bottomToTop, Type::BottomToTop);
    } else if (m_topToBottom >= 1.0f) {
        return std::make_pair(1.0f, Type::None);
    }
    return std::make_pair(m_topToBottom, Type::DoubleVertical);
}

IntersectionInfo::Type IntersectionInfo::type() const
{
    float m = min();
    if (m_bottomToTop == m) {
        return Type::BottomToTop;
    }
    if (m_topToBottom == m) {
        return Type::TopToBottom;
    }
    if (m_leftToRight == m) {
        return Type::LeftToRight;
    }
    if (m_rightToLeft == m) {
        return Type::RightToLeft;
    }
    return Type::None;
}
