#include <memory>
#include "../api.hpp"
#include "../parser.hpp"
#include "../background.hpp" // Substitui pelos nomes reais dos teus ficheiros
#include "../film.hpp"       // Substitui pelos nomes reais dos teus ficheiros
#include "../camera.hpp"
#include "../ortCamera.hpp"
#include "../perCamera.hpp"
#include "../sphere.h"
#include "../material.h"

// Instanciação da variável estática da classe
RunningOpt API::curr_run_opt;

// ==============================================================================
// O "Graphics State" (Estado Gráfico)
// Ao colocar isto num namespace sem nome, estas variáveis ficam globais,
// mas APENAS visíveis dentro deste ficheiro api.cpp! É o encapsulamento perfeito.
// ==============================================================================
namespace
{
    std::shared_ptr<Background> curr_background = nullptr;
    std::shared_ptr<Film> curr_film = nullptr;
    std::shared_ptr<Camera> curr_camera = nullptr;
    // std::unique_ptr<Camera> curr_camera = nullptr;

    // Dados temporários do lookat
   /*  Color global_look_from;
    Color global_look_at;
    Color global_up; */
    Point3 global_look_from;
    Point3 global_look_at;
    Vector3 global_up;
    std::vector<std::shared_ptr<Primitive>> scene_objects;
    std::shared_ptr<Material> last_material = nullptr;

    ParamSet global_camera_ps;
    bool has_camera_ps = false;
}

// ==============================================================================
// Implementação dos Métodos da API
// ==============================================================================

void API::init_engine(const RunningOpt &opt)
{
    curr_run_opt = opt;

    // Garantimos que a memória está limpa antes de começar
    curr_background = nullptr;
    curr_film = nullptr;

    std::cout << "[API] Motor inicializado.\n";
}

void API::run()
{
    std::cout << "[API] A iniciar a leitura do ficheiro: " << curr_run_opt.infile << "\n";
    // O comando abaixo arranca o Parser, que por sua vez vai ler o XML e
    // começar a chamar os métodos API::background, API::film, etc.
    Parser::parse(curr_run_opt.infile);
}

void API::clean_up()
{
    std::cout << "[API] A limpar a memória...\n";
    curr_background = nullptr;
    curr_film = nullptr;
    curr_camera = nullptr;
    scene_objects.clear(); // Limpa a lista de esferas
}

void API::background(const ParamSet &ps)
{
    std::cout << "[API] A processar o Background...\n";

    if (ps.count("bl"))
    {
        std::vector<Color> colors;
        colors.push_back(ps.get_color("bl"));
        colors.push_back(ps.get_color("tl"));
        colors.push_back(ps.get_color("tr"));
        colors.push_back(ps.get_color("br"));

        curr_background = std::make_shared<Background>(colors);
    }
    else
    {
        Color bg_color = ps.get_color("color");

        curr_background = std::make_shared<Background>(bg_color);
    }
}

void API::film(const ParamSet &ps)
{
    std::cout << "[API] A processar o Film...\n";

    int x_res = ps.get_int("x_res", 800); // 800 é o valor por defeito se falhar
    int y_res = ps.get_int("y_res", 600);
    std::string filename = ps.get_string("filename", "output.ppm");

    // Verifica se a opção do terminal --outfile substituiu o nome do XML
    if (!curr_run_opt.outfile.empty())
    {
        filename = curr_run_opt.outfile;
    }

    curr_film = std::make_shared<Film>(x_res, y_res, filename);
}

void API::render()
{
    int width = curr_film->get_width();
    int height = curr_film->get_height();

    if (!curr_film)
    {
        std::cerr << "[ERRO FATAL] Film não foi definido no XML!\n";
        return;
    }

    if (has_camera_ps && !curr_camera)
    {
        std::string type = global_camera_ps.get_string("type", "orthographic");

        if (type == "orthographic")
        {
            std::vector<float> sw = global_camera_ps.get_floats("screen_window");

            // Variáveis por defeito (caso o XML não tenha screen_window)
            float l = -1.0f, r = 1.0f, b = -1.0f, t = 1.0f;

            // Cinto de segurança: Só usamos o 'sw' se ele leu exatamente 4 números!
            if (sw.size() == 4)
            {
                l = sw[0];
                r = sw[1];
                b = sw[2];
                t = sw[3];
            }
            else
            {
                std::cerr << "[AVISO] screen_window falhou ou está incompleto. A usar valores por defeito (-1, 1, -1, 1).\n";
            }

            curr_camera = std::make_shared<OrthographicCamera>(
                global_look_from, global_look_at, global_up,
                l, r, b, t,
                width, height);
        }
        else if (type == "perspective")
        {
            float fovy = global_camera_ps.get_float("fovy", 60.0f);
            float aspect = static_cast<float>(width) / static_cast<float>(height);
            curr_camera = std::make_shared<PerspectiveCamera>(
                global_look_from, global_look_at, global_up,
                fovy, aspect, width, height);
        }
    }

    // Cinto de segurança final
    if (!curr_camera || !curr_background)
    {
        std::cerr << "[ERRO FATAL] Faltam elementos essenciais na cena!\n";
        return;
    }

    std::cout << "[API] A renderizar a imagem (" << width << "x" << height << ")...\n";

    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            // Cálculo de U e V para o Background (0.0 a 1.0)
            float u = float(i) / float(width);
            float v = float(j) / float(height);

            Ray ray = curr_camera->generate_ray(i, j);
            Surfel sf;
            Color pixel_color = curr_background->sampleUV(u, v); // Cor base é o fundo

            float closest_t = ray.t_max;
            bool hit = false;
            //curr_film->add_sample(i, j, pixel_color);

            for (const auto &obj : scene_objects)
            {
                if (obj->intersect(ray, &sf))
                {
                    if (sf.time < closest_t)
                    {
                        closest_t = sf.time;
                        // Flat Shading: pega a cor do material
                        // Precisas de implementar a classe Material e FlatMaterial!
                        pixel_color = sf.primitive->get_material()->get_color();
                        hit = true;
                    }
                }
            }
            curr_film->add_sample(i, j, pixel_color);
        }
    }
    curr_film->write_image();
}

void API::lookat(const ParamSet &ps)
{
    std::cout << "[API] A processar o LookAt...\n";

    global_look_from = ps.get_point3("look_from");
    global_look_at = ps.get_point3("look_at");
    global_up = ps.get_vector3("up");
}
void API::material(const ParamSet &ps)
{
    Color color = ps.get_color("color", Color(1, 1, 1));
    last_material = std::make_shared<FlatMaterial>(color);
}

void API::sphere(const ParamSet &ps)
{
    auto sphere = std::make_shared<Sphere>(ps, last_material);
    scene_objects.push_back(sphere);
}

void API::camera(const ParamSet &ps)
{
    std::cout << "[API] A guardar os dados da Camera para inicialização tardia...\n";
    global_camera_ps = ps;
    has_camera_ps = true;
}