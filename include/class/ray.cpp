#pragma once

#include <glm/glm.hpp>
#include <limits>

class Ray {
public:
    // =========================
    // Membros de dados
    // =========================
    glm::vec3 origin;     // O
    glm::vec3 direction;  // D

    float t_min;
    float t_max;

    // =========================
    // Construtores
    // =========================

    // Construtor padrão
    Ray()
        : origin(0.0f),
          direction(0.0f, 0.0f, 1.0f),
          t_min(0.0f),
          t_max(std::numeric_limits<float>::infinity()) {}

    // Construtor completo
    Ray(const glm::vec3& o, const glm::vec3& d,
        float tmin = 0.0f,
        float tmax = std::numeric_limits<float>::infinity())
        : origin(o), direction(d), t_min(tmin), t_max(tmax) {}

    // =========================
    // Método mágico
    // =========================

    // Retorna um ponto na reta: P(t) = O + tD
    glm::vec3 at(float t) const {
        return origin + t * direction;
    }

    // (Opcional) overload do operador ()
    glm::vec3 operator()(float t) const {
        return at(t);
    }
};