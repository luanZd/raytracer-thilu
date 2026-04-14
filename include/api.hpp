#ifndef API_HPP
#define API_HPP

#include "rt3.hpp"       
#include "param.hpp"  
#include "material.h"
#include "sphere.h"

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
    // --- O Coração do Ray Tracer ---
    static void render();

    static void material(const ParamSet& ps);
    static void sphere(const ParamSet& ps);
    static void lookat(const ParamSet& ps); 

private:
    static RunningOpt curr_run_opt;
};

#endif