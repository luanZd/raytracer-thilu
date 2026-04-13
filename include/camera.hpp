#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "rt3.hpp"
#include "ray.hpp" 


class Camera {
public:

    virtual ~Camera() = default;

    //ao usar, lembre-se de escrever a lógica disso aqui
    virtual Ray generate_ray(int col, int lin) const = 0;
};

#endif