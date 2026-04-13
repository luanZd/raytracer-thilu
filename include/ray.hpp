#ifndef RAY_HPP
#define RAY_HPP

#include <glm/glm.hpp>
#include "rt3.hpp" 
#include <limits>

class Ray {
public:
    // =========================
    // Membros de dados
    // =========================
    Point3 origin;     
    Vector3 direction; 

    float t_min;
    float t_max;

    // =========================
    // Construtores
    // =========================
    Ray();

    Ray(const Point3& o, const Vector3& d,
        float tmin = 0.0f,
        float tmax = std::numeric_limits<float>::infinity());

    // =========================
    // Métodos
    // =========================
    Point3 at(float t) const;
    Point3 operator()(float t) const;
};

#endif