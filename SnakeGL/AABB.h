#ifndef AABB_H
#define AABB_H

#include <glm/glm.hpp>

class AABB {
public:

    bool Intersects(const AABB& other) const { 
        return (min.x <= other.max.x && max.x >= other.min.x &&
                min.y <= other.max.y && max.y >= other.min.y); 
    }

    bool IntersectField() const {
        return (min.x <= 135.0f || min.y <= 105.0f || max.x >= 1050.0f || max.y >= 715.0f);
    }

    bool IntersectPoint(const glm::vec2 point) const {
        return (min.x <= point.x && max.x >= point.x &&
                min.y <= point.y && max.y >= point.y);
    }

    void SetBorder(const glm::vec2& newMin, const glm::vec2& newMax) { 
        min = newMin; 
        max = newMax; 
    }

private:
    glm::vec2 min;
    glm::vec2 max;
};

#endif // !AABB_H

