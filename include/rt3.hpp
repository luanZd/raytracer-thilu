#ifndef RT3_HPP
#define RT3_HPP

#include <string>
#include <glm/glm.hpp>
#include <vector>

using Point3 = glm::vec3;  
using Vector3 = glm::vec3;

struct RunningOpt
{
  std::string infile;
  bool help = false;
  std::string outfile;
  bool quick_render = false;
  std::vector<float> crop_window;
};

struct Surfel {
    glm::vec3 p;      // Ponto de contato
    glm::vec3 n;      // Normal da superfície no ponto p
    glm::vec3 wo;     // Direção de saída (geralmente -ray.d)
    float time;       // O valor 't' da interseção
    glm::vec2 uv;     // Coordenadas de textura (para o futuro)
    const class Primitive *primitive; // Qual objeto foi atingido

    Surfel() : primitive(nullptr) {}
};

#endif 