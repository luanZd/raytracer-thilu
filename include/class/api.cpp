#include <memory>
#include "../api.hpp"
#include "../parser.hpp"
#include "../background.hpp" // Substitui pelos nomes reais dos teus ficheiros
#include "../film.hpp"       // Substitui pelos nomes reais dos teus ficheiros
#include "../camera.hpp"
#include "../ortCamera.hpp"

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
    Camera* curr_camera = nullptr; // Descomenta quando tiveres a câmara
      //std::unique_ptr<Camera> curr_camera = nullptr;

    // Dados temporários do lookat
    Point3 global_look_from;
    Point3 global_look_at;
    Vector3 global_up;
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
    
    // Se o XML tiver o canto inferior esquerdo (bl), assumimos que é interpolado!
    if (ps.count("bl")) {
        std::vector<Color> colors;
        // Temos de empurrar as cores para a lista na mesma ordem do nosso Enum (bl, tl, tr, br)
        colors.push_back(ps.get_color("bl"));
        colors.push_back(ps.get_color("tl"));
        colors.push_back(ps.get_color("tr"));
        colors.push_back(ps.get_color("br"));
        
        // Chamamos o teu construtor avançado do std::vector!
        curr_background = new Background(colors); 
    } 
    else {
        // Se não tiver cantos, procura por "color" (Fundo sólido)
        Color bg_color = ps.get_color("color");
        curr_background = new Background(bg_color);
    }
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


     curr_film = new Film(x_res, y_res, filename);
}

void API::render() {
    std::cout << "[API] A iniciar o processo de Renderização!\n";

    if (!curr_film || !curr_background) {
        std::cerr << "[ERRO] Cena incompleta! Falta o Film ou o Background.\n";
        return;
    }

    int width = curr_film->get_width();
    int height = curr_film->get_height();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            
            // 1. Converter (x, y) para (u, v) normalizados (0.0 até 1.0)
            // Dividimos pelo (tamanho - 1) para que o último píxel seja exatamente 1.0
            float u = static_cast<float>(x) / static_cast<float>(width - 1);
            float v = static_cast<float>(y) / static_cast<float>(height - 1);
            
            // 2. Pedir a cor misturada ao teu Background usando o U e o V!
            // (Nota: se no teu ecrã o Y cresce para baixo, mas a matemática do lerp
            // espera que o V cresça para cima, podes usar (1.0f - v) aqui,
            // mas testa primeiro com 'v' puro para ver se a imagem fica invertida).
            Color pixel_color = curr_background->sampleUV(u, v);
            
            curr_film->add_sample(x, y, pixel_color);
        }
    }

    curr_film->write_image(); 
    std::cout << "[API] Imagem renderizada com sucesso!\n";
}

void API::lookat(const ParamSet& ps) {
    std::cout << "[API] A processar o LookAt...\n";

    global_look_from = ps.get_point3("look_from");
    global_look_at   = ps.get_point3("look_at");
    global_up        = ps.get_vector3("up");
}

void API::camera(const ParamSet& ps) {
    std::cout << "[API] A processar a Camera...\n";

    if (!curr_film) {
        std::cerr << "[ERRO] Film deve ser definido antes da Camera!\n";
        return;
    }

    std::string type = ps.get_string("type", "orthographic");

    int width = curr_film->get_width();
    int height = curr_film->get_height();

    if (type == "orthographic") {

        std::vector<float> sw = ps.get_float_list("screen_window");

        if (sw.size() != 4) {
            std::cerr << "[ERRO] screen_window inválido!\n";
            return;
        }

        curr_camera = std::make_unique<OrthographicCamera>(
            global_look_from,
            global_look_at,
            global_up,
            sw[0], sw[1], sw[2], sw[3],
            width, height
        );
    }
    else if (type == "perspective") {

        float fovy = ps.get_float("fovy", 60.0f);
        float aspect = static_cast<float>(width) / static_cast<float>(height);

        curr_camera = std::make_unique<PerspectiveCamera>(
            global_look_from,
            global_look_at,
            global_up,
            fovy,
            aspect,
            width,
            height
        );
    }
    else {
        std::cerr << "[ERRO] Tipo de camera desconhecido: " << type << "\n";
    }
}