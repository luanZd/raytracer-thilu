#include <glm/vec3.hpp> // verificar a possiblidade de usar a classe de 
#include <vector>

using Color = glm::vec3;
class Film
{
private:
    /* data */
    int width{0}, height{0};
    std::vector<Color> pixel_buffer;

public:
    Film(int w, int h);
};
