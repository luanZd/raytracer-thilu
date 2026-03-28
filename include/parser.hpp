#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>

// Namespace para manter as funções do leitor de XML organizadas
namespace Parser {
    
    // Função principal que vai receber o nome do ficheiro (ex: "scene01.xml")
    // e ler as configurações.
    void parse(const std::string& filename);

}

#endif