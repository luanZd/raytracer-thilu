#include "../film.hpp"

Film::Film(int w, int h) : width(w), height(h) {
    pixel_buffer.resize(width * height);
}

void Film::draw_pixel(int x, int y, const Color& color) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        
        // A fórmula mágica em ação
        int index = y * width + x;
        
        pixel_buffer[index] = color;
    }
}

Color Film::get_pixel(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        int index = y * width + x;
        return pixel_buffer[index];
    }
    // Retorna preto se pedirem um píxel fora da tela
    return Color(0.0f, 0.0f, 0.0f); 
}