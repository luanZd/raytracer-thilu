#ifndef MATERIAL_H
#define MATERIAL_H

#include "rt3.hpp"

class Material {
public:
    virtual ~Material() = default;
    virtual Color get_color() const = 0;
};

class FlatMaterial : public Material {
    Color c;
public:
    FlatMaterial(Color color) : c(color) {}
    Color get_color() const override { return c; }
};
#endif