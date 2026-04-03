#ifndef FILM_HPP
#define FILM_HPP

#include <vector>
#include <string>
#include <glm/vec3.hpp>

using Color = glm::vec3;

class Film {
private:
    int width;
    int height;
    std::string filename;
    
    // O nosso bloco contínuo de memória 1D super otimizado!
    std::vector<Color> pixels; 

public:
    // Construtor: Inicializa logo o Vector com o tamanho exato necessário
    Film(int w, int h, const std::string& name) 
        : width(w), height(h), filename(name), pixels(w * h) {}
    
    ~Film() = default;

    int get_width() const { return width; }
    int get_height() const { return height; }

    // Onde a magia acontece: transformar (x, y) numa posição 1D
    void add_sample(int x, int y, const Color& color) {
        pixels[y * width + x] = color;
    }

    // A função de exportação (só a declaramos aqui, vamos implementá-la no .cpp)
    void write_image() const;
};

#endif