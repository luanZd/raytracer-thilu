
#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "ray.hpp" 
#include "rt3.hpp"
#include <memory>
#include "material.h"

class Material; // Forward declaration

class Primitive {
public:
    virtual ~Primitive() = default;
    
    virtual bool intersect(const Ray& r, Surfel *sf) const = 0;
    
    virtual bool intersect_p(const Ray& r) const = 0;

    virtual std::shared_ptr<Material> get_material() const = 0;
};
#endif