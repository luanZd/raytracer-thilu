#include "../film.hpp"

Film::Film(int w, int h)
{
    width = w;
    height = h;
    pixel_buffer.resize(width * height);
}