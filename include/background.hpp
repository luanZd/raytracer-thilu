#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <vector>
#include <glm/vec3.hpp> 

using Color = glm::vec3; //devemos substituir para uma struct (r,g,b)?

class Background {
private:
    Color corners[4];
    
    enum Corners_e { 
        bl = 0, // Bottom left
        tl = 1, // Top left
        tr = 2, // Top right
        br = 3  // Bottom right
    };

    
    Color lerp(const Color &A, const Color &B, float t) const;

public:
    Background(const std::vector<Color>& colors);
    
    ~Background() = default;

    Color sampleUV(float u, float v) const;
};

#endif