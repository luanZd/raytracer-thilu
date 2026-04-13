#ifndef PARAMSET_HPP
#define PARAMSET_HPP

#include <map>
#include <string>
#include <vector>
#include <glm/vec3.hpp>

using Color = glm::vec3;

class ParamSet {
private:
    // O nosso dicionário de atributos (Chave -> Valor em texto)
    std::map<std::string, std::string> attributes;

public:
    ParamSet() = default;
    ~ParamSet() = default;

    // --- Gestão do Dicionário ---
    
    // Adiciona um par chave-valor lido pelo Parser
    void add(const std::string& key, const std::string& value);

    // Verifica se uma chave existe no dicionário
    bool count(const std::string& key) const;

    // --- Extratores Inteligentes (Com valores por defeito seguros) ---

    // Retorna o texto puro (ex: filename="imagem.ppm")
    std::string get_string(const std::string& key, const std::string& default_val = "") const;

    // Retorna um número inteiro (ex: x_res="800")
    int get_int(const std::string& key, int default_val = 0) const;

    // Retorna um número decimal (ex: radius="2.5")
    float get_float(const std::string& key, float default_val = 0.0f) const;

    // Retorna um booleano (ex: quick_render="true")
    bool get_bool(const std::string& key, bool default_val = false) const;

    // Retorna uma cor normalizada (ex: color="255 128 0" -> vec3(1.0, 0.5, 0.0))
    Color get_color(const std::string& key, const Color& default_val = Color(0.0f, 0.0f, 0.0f)) const;


    // Retorna uma lista de números (ex: crop_window="0.0 1.0 0.0 1.0")
    std::vector<float> get_floats(const std::string& key) const;
};

#endif