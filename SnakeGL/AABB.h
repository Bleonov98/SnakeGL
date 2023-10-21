#ifndef AABB_H
#define AABB_H

#include <glm/glm.hpp>

class AABB {
public:

    bool Intersects(const AABB& other) const { 
        return (min.x <= other.max.x && max.x >= other.min.x &&
                min.y <= other.max.y && max.y >= other.min.y); 
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

