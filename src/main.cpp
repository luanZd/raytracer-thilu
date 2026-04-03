#include "rt3.hpp"
#include "api.hpp"

int main(int argc, char* argv[]) {
    // 1. Lemos os argumentos do terminal (tu podes criar uma função para isto depois)
    RunningOpt opt;
    opt.infile = "scenes/scene01.xml"; // Simulação de ler do argv

    // 2. O Ciclo de Vida da API ditado pelo professor
    API::init_engine(opt);
    API::run();
    API::clean_up();

    return 0;
}