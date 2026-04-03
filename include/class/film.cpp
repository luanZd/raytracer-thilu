#include "../film.hpp"
#include <fstream>    // Para escrevermos no ficheiro (std::ofstream)
#include <iostream>   // Para mensagens de terminal
#include <algorithm>  // Para usarmos o std::clamp (C++17)

void Film::write_image() const {
    // 1. Tentar criar/abrir o ficheiro de destino
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "[Film] ERRO: Não foi possível criar o ficheiro " << filename << "!\n";
        return;
    }

    // 2. Escrever o "Cabeçalho Mágico" do formato PPM
    // P3 -> Formato de texto ASCII
    // width height -> A resolução da imagem
    // 255 -> O valor máximo que uma cor pode ter
    file << "P3\n";
    file << width << " " << height << "\n";
    file << "255\n";

    // 3. Escrever os píxeis um a um!
    // Como o nosso std::vector já está na ordem perfeita (da esquerda para a direita, 
    // de cima para baixo), podemos usar um "for" moderno e simples para percorrer tudo.
    for (const Color& pixel : pixels) {
        
        // Proteção: std::clamp garante que se a luz de um píxel "estourar" o valor 1.0,
        // ou ficar negativa, o valor é forçado a ficar exatamente entre 0.0f e 1.0f.
        float r = std::clamp(pixel.r, 0.0f, 1.0f);
        float g = std::clamp(pixel.g, 0.0f, 1.0f);
        float b = std::clamp(pixel.b, 0.0f, 1.0f);

        // Traduzir de float (0.0 a 1.0) para inteiro (0 a 255)
        // Multiplicamos por 255.999f em vez de 255 para evitar arredondamentos errados do C++
        int ir = static_cast<int>(r * 255.999f);
        int ig = static_cast<int>(g * 255.999f);
        int ib = static_cast<int>(b * 255.999f);

        // Escrever os três números no ficheiro separados por espaço
        file << ir << " " << ig << " " << ib << "\n";
    }

    // 4. Fechar o ficheiro e avisar o utilizador
    file.close();
    std::cout << "[Film] Imagem guardada com sucesso em: " << filename << "\n";
}