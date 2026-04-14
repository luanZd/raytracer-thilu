#include "../Sphere.h"
#include <cmath>
#include <algorithm>

Sphere::Sphere(const ParamSet& ps, std::shared_ptr<Material> mat) 
    : material(mat) {
    // Extrai o raio e o centro. O get_vec3 deve ser implementado no seu ParamSet/Util
    radius = ps.get_float("radius", 1.0f);
    center = ps.get_color("center", glm::vec3(0,0,0)); // Usando get_color como proxy para vec3
}

bool Sphere::intersect(const Ray& r, Surfel *sf) const {
    // Vetor do centro da esfera até a origem do raio
    glm::vec3 oc = r.origin - center;

    // Simplificação da equação quadrática para maior precisão (h = b/2)
    float a = glm::dot(r.direction, r.direction);
    float h = glm::dot(r.direction, oc);
    float c = glm::dot(oc, oc) - radius * radius;

    float discriminant = h * h - a * c;

    // Se o discriminante for negativo, não há interseção real
    if (discriminant < 0) return false;

    float sqrt_d = std::sqrt(discriminant);

    // Encontrar a raiz mais próxima (t1) que esteja no intervalo [t_min, t_max]
    float t = (-h - sqrt_d) / a;
    if (t < r.t_min || t > r.t_max) {
        // Tenta a segunda raiz (t2)
        t = (-h + sqrt_d) / a;
        if (t < r.t_min || t > r.t_max) return false;
    }

    // Se sf não for nulo, preenchemos as informações de contato
    if (sf) {
        sf->time = t;
        sf->p = r(t); // Ponto P = O + tD
        // A normal é o vetor do centro até o ponto de impacto, normalizado
        sf->n = glm::normalize(sf->p - center);
        sf->wo = -r.direction;
        sf->primitive = this;
    }

    return true;
}

bool Sphere::intersect_p(const Ray& r) const {
    // Versão simplificada (apenas booleana) para performance
    glm::vec3 oc = r.origin - center;
    float a = glm::dot(r.direction, r.direction);
    float h = glm::dot(r.direction, oc);
    float c = glm::dot(oc, oc) - radius * radius;

    float discriminant = h * h - a * c;
    if (discriminant < 0) return false;

    float sqrt_d = std::sqrt(discriminant);
    float t = (-h - sqrt_d) / a;
    if (t < r.t_min || t > r.t_max) {
        t = (-h + sqrt_d) / a;
    }

    return (t >= r.t_min && t <= r.t_max);
}