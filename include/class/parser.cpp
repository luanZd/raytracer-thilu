#include "../parser.hpp"
#include "../api.hpp"       
#include "../param.hpp"  
#include "../../ext/pugixml/src/pugixml.hpp"
#include <iostream>
#include "../sphere.h"
#include <stdexcept>

namespace Parser {

void parse(const std::string& filename) {
    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file(filename.c_str());

    if (!result) {
        throw std::runtime_error(std::string("Erro ao carregar XML: ") + result.description());
    }

    std::cout << "[Parser] Ficheiro XML carregado com sucesso!\n";

    // 1. Encontrar a raiz (RAYTHILU)
    pugi::xml_node raythilu = doc.child("RAYTHILU");
    if (!raythilu) {
        throw std::runtime_error("Erro: Tag raiz <RAYTHILU> não encontrada!");
    }

    for (pugi::xml_node node = raythilu.first_child(); node; node = node.next_sibling()) {
        
        std::string node_name = node.name();

        if (node_name == "world_begin") {
            std::cout << "[Parser] A iniciar a cena...\n";
            continue; // Passa para a próxima tag
        } 
        else if (node_name == "world_end") {
            std::cout << "[Parser] Fim da cena! A chamar o renderizador...\n";
            
            API::render(); 
            break; 
        }

        // 3. Se for uma tag normal (film, background, camera), preenchemos o ParamSet
        ParamSet ps;
        
        // Iterar por todos os atributos da tag atual (ex: x_res="200" y_res="100")
        for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
            ps.add(attr.name(), attr.value());
        }

        if (node_name == "film") {
            API::film(ps);
        } 
        else if (node_name == "background") {
            API::background(ps);
        } 
        else if (node_name == "camera") {
            // API::camera(ps); // Descomenta quando criar o método camera na API
            std::cout << "[Parser] Aviso: Tag <camera> lida, mas não foi implementada.\n";
        } 
        if (node_name == "material") {
    ParamSet ps;
    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        ps.add(attr.name(), attr.value());
    }
    // API::material cria um material e guarda-o como "current_material"
    API::material(ps); 
} 
else if (node_name == "object") {
    std::string type = node.attribute("type").value();
    ParamSet ps;
    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        ps.add(attr.name(), attr.value());
    }

    if (type == "sphere") {
        API::sphere(ps); 
    }
        else {
            std::cerr << "[Parser] Aviso: Tag desconhecida ignorada: <" << node_name << ">\n";
        }
    }
}

} // namespace Parser