#include "../api.hpp"
#include "../parser.hpp"
#include "../background.hpp" // Substitui pelos nomes reais dos teus ficheiros
#include "../film.hpp"       // Substitui pelos nomes reais dos teus ficheiros
#include <iostream>

// Instanciação da variável estática da classe
RunningOpt API::curr_run_opt;

// ==============================================================================
// O "Graphics State" (Estado Gráfico)
// Ao colocar isto num namespace sem nome, estas variáveis ficam globais,
// mas APENAS visíveis dentro deste ficheiro api.cpp! É o encapsulamento perfeito.
// ==============================================================================
namespace {
    Background* curr_background = nullptr;
    Film* curr_film = nullptr;
    // Camera* curr_camera = nullptr; // Descomenta quando tiveres a câmara
}

// ==============================================================================
// Implementação dos Métodos da API
// ==============================================================================

void API::init_engine(const RunningOpt& opt) {
    curr_run_opt = opt;
    
    // Garantimos que a memória está limpa antes de começar
    curr_background = nullptr;
    curr_film = nullptr;
    
    std::cout << "[API] Motor inicializado.\n";
}

void API::run() {
    std::cout << "[API] A iniciar a leitura do ficheiro: " << curr_run_opt.infile << "\n";
    // O comando abaixo arranca o Parser, que por sua vez vai ler o XML e
    // começar a chamar os métodos API::background, API::film, etc.
    Parser::parse(curr_run_opt.infile);
}

void API::clean_up() {
    std::cout << "[API] A limpar a memória da cena...\n";
    
    // Como o README exige, temos de libertar todos os recursos alocados
    if (curr_background) {
        delete curr_background;
        curr_background = nullptr;
    }
    if (curr_film) {
        delete curr_film;
        curr_film = nullptr;
    }
}

void API::background(const ParamSet& ps) {
    std::cout << "[API] A processar o Background...\n";
    // Extrai a cor da caixa mágica do ParamSet
    Color bg_color = ps.get_color("color");
    
    // Instancia o objeto real (ajusta ao construtor da tua classe Background)
    // curr_background = new Background(bg_color); 
}

void API::film(const ParamSet& ps) {
    std::cout << "[API] A processar o Film...\n";
    
    int x_res = ps.get_int("x_res", 800); // 800 é o valor por defeito se falhar
    int y_res = ps.get_int("y_res", 600);
    std::string filename = ps.get_string("filename", "output.ppm");

    // Verifica se a opção do terminal --outfile substituiu o nome do XML
    if (!curr_run_opt.outfile.empty()) {
        filename = curr_run_opt.outfile;
    }

    // Instancia o Filme (ajusta ao construtor da tua classe Film)
    // curr_film = new Film(x_res, y_res, filename);
}

void API::camera(const ParamSet& ps) {
    std::cout << "[API] A processar a Camera...\n";
    // TODO: Criar a câmara quando ela for implementada
}

void API::render() {
    std::cout << "[API] A iniciar o processo de Renderização!\n";

    // Proteção: Só podemos renderizar se tivermos um filme e um fundo!
    /* Descomenta isto quando os teus objetos estiverem a ser instanciados acima
    if (!curr_film || !curr_background) {
        std::cerr << "[ERRO] Cena incompleta! Falta o Film ou o Background.\n";
        return;
    }

    int width = curr_film->get_width();
    int height = curr_film->get_height();

    // O Main Loop descrito no README (Passo 5)
    // Percorre cada píxel da imagem (linhas e colunas)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            
            // Mais tarde: Ray r = curr_camera->generate_ray(x, y);
            
            // Para já, apenas amostramos a cor do fundo!
            Color pixel_color = curr_background->sample(x, y);
            
            // E pintamos essa cor no nosso Array 1D da classe Film
            curr_film->add_sample(x, y, pixel_color);
        }
    }

    // Quando o ciclo terminar, guardamos a matriz no ficheiro PPM
    curr_film->write_image();
    */
    
    std::cout << "[API] Imagem renderizada com sucesso!\n";
}