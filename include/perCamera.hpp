#ifndef PERSPECTIVE_CAMERA_HPP
#define PERSPECTIVE_CAMERA_HPP

#include "camera.hpp"
#include "rt3.hpp"

class PerspectiveCamera : public Camera {
private:
    // O Frame da câmera
    Point3 eye;
    Vector3 u, v, w;

    // A Screen Window (calculada internamente)
    float l, r, b, t;
    int nx, ny;
    
    // Distância focal (o professor assume 1.0 por defeito)
    float fd; 

public:
    // Repara que recebemos o 'fovy' e o 'aspect_ratio' em vez de l, r, b, t
    PerspectiveCamera(const Point3& look_from, const Point3& look_at, const Vector3& up,
                      float fovy, float aspect_ratio,
                      int width, int height);

    Ray generate_ray(int col, int lin) const override;
};

#endif