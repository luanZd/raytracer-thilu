#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <vector>
#include <glm/vec3.hpp>

using Color = glm::vec3;

class Background {
public:
    // Os índices dos cantos que usas no teu .cpp
    // bl = bottom-left, tl = top-left, tr = top-right, br = bottom-right
    enum Corners { bl = 0, tl = 1, tr = 2, br = 3 };

private:
    // O array para guardar as cores dos 4 cantos
    Color corners[4]; 

    // A declaração da tua função auxiliar de matemática
    Color lerp(const Color &A, const Color &B, float t) const;

public:
    // O teu construtor avançado que aceita uma lista de cores
    Background(const std::vector<Color>& colors);
    
    // Construtor extra: se a API passar só 1 cor, preenchemos os 4 cantos iguais!
    Background(const Color& c);

    ~Background() = default;

    // A declaração da tua função de amostrar a cor interpolada
    Color sampleUV(float u, float v) const;
};

#endif