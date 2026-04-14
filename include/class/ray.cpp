#pragma once

#include "../ray.hpp"
#include <glm/glm.hpp>
#include <limits>

    // =========================
    // Construtores
    // =========================

   // Construtor padrão
Ray::Ray()
    : origin(0.0f), direction(0.0f, 0.0f, -1.0f),
      t_min(0.0f), t_max(std::numeric_limits<float>::infinity()) {}

// Construtor completo
Ray::Ray(const Point3& o, const Vector3& d, float tmin, float tmax)
    : origin(o), direction(d), t_min(tmin), t_max(tmax) {}

// Método at()
Point3 Ray::at(float t) const {
    return origin + t * direction;
}

// Operador ()
Point3 Ray::operator()(float t) const {
    return at(t);
};