#include "ortCamera.hpp"
#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

OrthographicCamera::OrthographicCamera(
    const Point3& look_from,
    const Point3& look_at,
    const Vector3& up,
    float x_min, float x_max,
    float y_min, float y_max,
    int width, int height)
{
    // Eye
    eye = look_from;

    // Base ortonormal
    w = glm::normalize(look_at - look_from);   // direção (gaze)
    u = glm::normalize(glm::cross(up, w));     // direita
    /* u = cross(up, w); */   
    v = glm::normalize(glm::cross(w, u));      // cima corrigido

    // Screen window
    l = x_min;
    r = x_max;
    b = y_min;
    t = y_max;

    // Resolução
    nx = width;
    ny = height;
}

Ray OrthographicCamera::generate_ray(int col, int lin) const
{
    // Screen space
    float u_screen = l + (r - l) * (col + 0.5f) / nx;
    float v_screen = b + (t - b) * (lin + 0.5f) / ny;
    //float v_screen = t - (t - b) * (lin + 0.5f) / ny;

    // Origem do raio
    Point3 ray_origin = eye + (u_screen * u) + (v_screen * v);

    // Direção (sempre igual na ortográfica)
    Vector3 ray_dir = w;

    return Ray(ray_origin, ray_dir);
}