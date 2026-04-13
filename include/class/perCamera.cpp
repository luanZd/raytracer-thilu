#include "perCamera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

PerspectiveCamera::PerspectiveCamera(
    const Point3& look_from,
    const Point3& look_at,
    const Vector3& up,
    float fovy, float aspect_ratio,
    int width, int height)
{
    // Eye
    eye = look_from;

    // Base ortonormal (igual à ortográfica)
    w = glm::normalize(look_at - look_from);
    u = glm::normalize(glm::cross(up, w));
    v = glm::normalize(glm::cross(w, u));

    // Distância focal
    fd = 1.0f;

    // FOV → screen window
    float theta = glm::radians(fovy);
    float h = tan(theta / 2.0f);

    t = h;
    b = -h;
    r = t * aspect_ratio;
    l = -r;

    // Resolução
    nx = width;
    ny = height;
}
Ray PerspectiveCamera::generate_ray(int col, int lin) const
{
    // Screen space (igual à ortográfica)
    float u_screen = l + (r - l) * (col + 0.5f) / nx;
    float v_screen = b + (t - b) * (lin + 0.5f) / ny;

    // Origem fixa
    Point3 ray_origin = eye;

    // Direção (do olho até o pixel)
    Vector3 ray_dir = (fd * w) + (u_screen * u) + (v_screen * v);

    // Normalizar é essencial
    ray_dir = glm::normalize(ray_dir);

    return Ray(ray_origin, ray_dir);
}