#ifndef API_HPP
#define API_HPP

#include "rt3.hpp"       // Onde está a tua struct RunningOpt
#include "param.hpp"  // A nossa "caixa" de atributos do XML
#include "material.h"
#include "sphere.h"

// Forward declarations (Diz ao compilador: "Estas classes existem, confia em mim", 
// para não termos de fazer includes pesados aqui no cabeçalho)
class Background;
class Film;

class API {
public:
    // --- Controlo Central do Motor ---
    static void init_engine(const RunningOpt& opt);
    static void run();
    static void clean_up();

    // --- Criação de Componentes da Cena (Chamados pelo Parser) ---
    static void background(const ParamSet& ps);
    static void film(const ParamSet& ps);
    static void camera(const ParamSet& ps);
    static void API::lookat(const ParamSet& ps);
    // --- O Coração do Ray Tracer ---
    static void render();

    static void material(const ParamSet& ps);
    static void sphere(const ParamSet& ps);
    static void lookat(const ParamSet& ps); // Certifique-se que não tem "API::" aqui

private:
    // Guardamos as opções de execução globais
    static RunningOpt curr_run_opt;
};

#endif