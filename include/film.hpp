
#include <vector>

class Film
{
private:
    /* data */
    int width{0}, height{0};
    std::vector<Color> pixel_buffer;

public:
    Film(int w, int h);
};
