#include <iostream>
#include "rt3.hpp"
#include "api.hpp"


int main(int argc, char* argv[]) {
    // 1. Lemos os argumentos do terminal (tu podes criar uma função para isto depois)
    RunningOpt opt;
    if (argc > 1) {
        opt.infile = argv[1]; 
    } 
    else {
        // Se o utilizador só escreveu "./rt3" e não passou ficheiro, avisamos!
        std::cerr << "Uso: ./rt3 <caminho_para_o_ficheiro.xml>\n";
        return 1; // Sai do programa com erro
    }
    // 2. O Ciclo de Vida da API ditado pelo professor
    API::init_engine(opt);
    API::run();
    API::clean_up();

    return 0;
}