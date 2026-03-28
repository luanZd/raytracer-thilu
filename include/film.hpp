#include <glm/vec3.hpp> // verificar a possiblidade de usar a classe de 
#include <vector>
#include <glm/vec3.hpp>

using Color = glm::vec3;
class Film
{
private:
    int width;
    int height;
    
   
    std::vector<Color> pixel_buffer;

public:
    Film(int w, int h);
    
    ~Film() = default;

    void draw_pixel(int x, int y, const Color& color);
    Color get_pixel(int x, int y) const;
    
    //Getter funções
    int get_width() const { return width; }
    int get_height() const { return height; }
};

#endif