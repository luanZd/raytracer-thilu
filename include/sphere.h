#ifndef SPHERE_H
#define SPHERE_H

#include "Primitive.h"
#include "Param.hpp"
#include <glm/glm.hpp>

class Sphere : public Primitive {
public:
    // Construtor que extrai dados do ParamSet (vindo do Parser)
    Sphere(const ParamSet& ps, std::shared_ptr<Material> mat);

    // Implementação dos métodos virtuais da classe Primitive
    virtual bool intersect(const Ray& r, Surfel *sf) const override;
    virtual bool intersect_p(const Ray& r) const override;
    
    // Retorna o material associado a esta esfera
    virtual std::shared_ptr<Material> get_material() const override { return material; }

private:
    glm::vec3 center;
    float radius;
    std::shared_ptr<Material> material;
};

#endif