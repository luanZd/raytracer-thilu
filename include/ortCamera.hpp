#ifndef ORTHOGRAPHIC_CAMERA_HPP
#define ORTHOGRAPHIC_CAMERA_HPP

#include "camera.hpp" 
#include "rt3.hpp"    

class OrthographicCamera : public Camera {
private:
    Point3 eye;         
    Vector3 u, v, w;    

    //Screen Window
    float l, r, b, t; 
    
    // Resolução da imagem
    int nx, ny;       

public:
    OrthographicCamera(const Point3& look_from, const Point3& look_at, const Vector3& up, 
                       float x_min, float x_max, float y_min, float y_max,
                       int width, int height);

    Ray generate_ray(int col, int lin) const override;
};

#endif