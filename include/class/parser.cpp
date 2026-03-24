#include "../parser.hpp"
#include "../../ext/pugixml/src/pugixml.hpp" // Inclui a biblioteca pugixml
#include <iostream>

namespace Parser {

    void parse(const std::string& filename) {
        pugi::xml_document doc;
        
        // Tenta carregar o ficheiro XML
        pugi::xml_parse_result result = doc.load_file(filename.c_str());

        if (!result) {
            std::cerr << "Erro ao ler o ficheiro XML: " << result.description() << "\n";
            return;
        }

        std::cout << "Ficheiro XML carregado com sucesso!\n";

        // A tag principal é sempre <RT3>
        pugi::xml_node root = doc.child("RT3");
        if (!root) {
            std::cerr << "Erro: Tag <RT3> não encontrada.\n";
            return;
        }

        // 1. Procurar a tag <film>
        pugi::xml_node film_node = root.child("film");
        if (film_node) {
            int x_res = film_node.attribute("x_res").as_int(800); // 800 é o valor por defeito se falhar
            int y_res = film_node.attribute("y_res").as_int(600);
            std::string img_filename = film_node.attribute("filename").as_string("output.ppm");

            std::cout << "Filme encontrado: " << x_res << "x" << y_res << ", Salvar em: " << img_filename << "\n";
            
            // Aqui, no futuro, faremos: API::film(x_res, y_res, img_filename);
        }

        // 2. Procurar a tag <world_begin> e depois <background>
        pugi::xml_node world_node = root.child("world_begin");
        if (world_node) {
            pugi::xml_node bkg_node = world_node.child("background");
            
            if (bkg_node) {
                std::string type = bkg_node.attribute("type").as_string();
                std::cout << "Fundo encontrado do tipo: " << type << "\n";
                
                // Aqui vais ler as cores (color="153 204 255" ou bl="..." tl="..." etc)
                // e mandar para a API criar o teu objeto Background!
            }
        }
    }
}