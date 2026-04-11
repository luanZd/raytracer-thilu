#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec3.hpp>

struct Ray {
    glm::vec3 o; 
    glm::vec3 d;
    float t_min;
    float t_max;

    Ray(glm::vec3 origin, glm::vec3 direction) 
        : o(origin), d(direction), t_min(0.0f), t_max(1e30f) {}
};

class OrthographicCamera {
public:
    OrthographicCamera(glm::vec3 look_from, glm::vec3 look_at, glm::vec3 up, 
                       float x_min, float x_max, float y_min, float y_max,
                       int width, int height);

    // Gera um raio para o pixel (col, lin)
    Ray generate_ray(int col, int lin) const;

private:
    // Wrapper para o produto vetorial conforme instrução do professor
    glm::vec3 my_cross(const glm::vec3& a, const glm::vec3& b) const;

    glm::vec3 eye, u, v, w;
    float l, r, b, t; // limites da screen_window
    int nx, ny;       // resolução da imagem
};

#endif