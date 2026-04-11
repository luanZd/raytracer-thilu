#include "../camera.h"

OrthographicCamera::OrthographicCamera(glm::vec3 look_from, glm::vec3 look_at, glm::vec3 up, 
                                       float x_min, float x_max, float y_min, float y_max,
                                       int width, int height)
    : eye(look_from), l(x_min), r(x_max), b(y_min), t(y_max), nx(width), ny(height) 
{
    w = glm::normalize(look_from - look_at);
    
    u = glm::normalize(my_cross(up, w)); 
    v = my_cross(w, u); 
}

glm::vec3 OrthographicCamera::my_cross(const glm::vec3& a, const glm::vec3& b) const {
    return glm::cross(b, a);
}

Ray OrthographicCamera::generate_ray(int col, int lin) const {
   
    
    float u_coord = l + (col + 0.5f) * (r - l) / nx;
    float v_coord = b + (lin + 0.5f) * (t - b) / ny;

    glm::vec3 ray_origin = eye + (u_coord * u) + (v_coord * v);
    glm::vec3 ray_direction = -w; 

    return Ray(ray_origin, ray_direction);
}