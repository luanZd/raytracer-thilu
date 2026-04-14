#include "util.hpp"
#include <algorithm> 
#include <locale> // FALTAVA ISTO!
#include <sstream>

namespace Util {

    int parse_int(const std::string& value) {
        return std::stoi(value);
    }

    float parse_float(const std::string& value) {
        return std::stof(value);
    }

    bool parse_bool(const std::string& value) {
        std::string val = value;
        std::transform(val.begin(), val.end(), val.begin(), ::tolower);
        return (val == "true" || val == "1" || val == "on");
    }

    Color parse_color(const std::string& value) {
        std::stringstream ss(value);
        // FORÇA O PADRÃO INTERNACIONAL (ignora a vírgula do Linux em PT)
        ss.imbue(std::locale("C")); 
        
        // MUDAMOS PARA FLOAT (estava int r, g, b)
        float r = 0, g = 0, b = 0; 
        
        if (ss >> r >> g >> b) {
            // JÁ NÃO DIVIDE POR 255!
            return Color(r, g, b); 
        }
        return Color(0.0f, 0.0f, 0.0f); 
    }

    std::vector<float> parse_floats(const std::string& value) {
        std::vector<float> result;
        std::stringstream ss(value);
        
        // FORÇA O PADRÃO INTERNACIONAL AQUI TAMBÉM
        ss.imbue(std::locale("C")); 
        
        float val;
        while (ss >> val) {
            result.push_back(val);
        }
        return result;
    }
}