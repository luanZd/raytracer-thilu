#include "../film.hpp"

Film::Film(int w, int h) : width(w), height(h)
{
    pixel_buffer.resize(width * height);
}

void Film::draw_pixel(int x, int y, const Color &color)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {

/* Isso é para endereçar da seguinte forma:

Suponha altura = 3 e largura = 4, e pediram para desenhar o pixel(2,2) logo:
indíce = 2*4+2 = 10


        x=0   x=1   x=2   x=3  <-- (Colunas)
    +-----+-----+-----+-----+
y=0 |  0  |  1  |  2  |  3  |
    +-----+-----+-----+-----+
y=1 |  4  |  5  |  6  |  7  |
    +-----+-----+-----+-----+
y=2 |  8  |  9  | 10  | 11  |
    +-----+-----+-----+-----+
 ^
(Linhas)
Por que isso funciona? Simplesmente, economiza e velocidade, em vez de uma estrutura complexa
temos uma estrutura simples.

*/
        int index = y * width + x;

        pixel_buffer[index] = color;
    }
}

Color Film::get_pixel(int x, int y) const
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        int index = y * width + x;
        return pixel_buffer[index];
    }
    // Retorna preto se pedirem um píxel fora da tela
    return Color(0.0f, 0.0f, 0.0f);
}