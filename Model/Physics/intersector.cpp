#include "intersector.h"

#include "../../Aux/mathtools.h"
#include "intersectableobject.h"

namespace Physics {

    static sf::FloatRect translateRectangle(const sf::FloatRect & rectangle, const sf::Vector2f & translation)
    {
        return sf::FloatRect(
            rectangle.left + translation.x, rectangle.top + translation.y, rectangle.width, rectangle.height);
    }

    static bool intersectsHorizontally(const sf::FloatRect & rect1, const sf::FloatRect & rect2)
    {
        return true;

        return MathTools::liesIsInterval(rect1.left, rect2.left, rect2.left + rect2.width) ||
               MathTools::liesIsInterval(rect1.left + rect1.width, rect2.left, rect2.left + rect2.width) ||
               (rect1.left < rect2.left && rect1.left + rect1.width > rect2.left + rect2.width);
    }

    static bool intersectsVertically(const sf::FloatRect & rect1, const sf::FloatRect & rect2)
    {
        return true;
        return MathTools::liesIsInterval(rect1.top, rect2.top, rect2.top + rect2.height) ||
               MathTools::liesIsInterval(rect1.top + rect1.height, rect2.top, rect2.top + rect2.height) ||
               (rect1.top < rect2.top && rect1.top + rect1.height > rect2.top + rect2.height);
    }

    IntersectionInfo
    intersect(const Rectangle & movingRect, const sf::Vector2f & velocity, const Rectangle & staticRect, float dt)
    {
        IntersectionInfo info;
        if (velocity.y != 0.0f) {
            float topToBottom = (staticRect.top - movingRect.top - movingRect.height) / (dt * velocity.y);
            if (topToBottom >= 0.0f && topToBottom < 1.0f) {
                if (intersectsHorizontally(translateRectangle(movingRect, topToBottom * dt * velocity), staticRect)) {
                    info.setTopToBottom(topToBottom);
                }
            }
            float bottomToTop = (staticRect.top + staticRect.height - movingRect.top) / (dt * velocity.y);
            if (bottomToTop >= 0.0f && bottomToTop < 1.0f) {
                if (intersectsHorizontally(translateRectangle(movingRect, bottomToTop * dt * velocity), staticRect)) {
                    info.setBottomToTop(bottomToTop);
                }
            }
        }
        if (velocity.x != 0.0f) {
            float leftToRight = (staticRect.left - movingRect.left - movingRect.width) / (dt * velocity.x);
            if (leftToRight >= 0.0f && leftToRight < 1.0f) {
                if (intersectsVertically(translateRectangle(movingRect, leftToRight * dt * velocity), staticRect)) {
                    info.setLeftToRight(leftToRight);
                }
            }

            float rightToLeft = (staticRect.left + staticRect.width - movingRect.left) / (dt * velocity.x);
            if (rightToLeft >= 0.0f && rightToLeft < 1.0f) {
                if (intersectsVertically(translateRectangle(movingRect, rightToLeft * dt * velocity), staticRect)) {
                    info.setRightToLeft(rightToLeft);
                }
            }
        }
        return info;
    }

    IntersectionInfo intersect(const IntersectableObject & movingObject, const Object & staticObject, float dt)
    {
        intersect(movingObject.getShape(), movingObject.getVelocity(), staticObject.getShape(), dt);
    }

} // namespace Physics