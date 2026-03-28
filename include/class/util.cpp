#include "../util.hpp"

namespace Util {

    int parse_int(const std::string& value) {
        // std::stoi é a função padrão do C++ (String TO Integer)
        return std::stoi(value);
    }

    float parse_float(const std::string& value) {
        // std::stof (String TO Float)
        return std::stof(value);
    }

    Color parse_color(const std::string& value) {
        std::stringstream ss(value);
        int r = 0, g = 0, b = 0;
        
        // Tenta ler os três números do texto
        if (ss >> r >> g >> b) {
            // Normaliza de 0-255 para 0.0-1.0
            return Color(r / 255.0f, g / 255.0f, b / 255.0f);
        }
        
        // Se falhar a leitura, devolve preto por segurança
        return Color(0.0f, 0.0f, 0.0f); 
    }

}