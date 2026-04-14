#ifndef SCENE_H
#define SCENE_H

#include "Primitive.h"
#include "Background.hpp"
#include "Camera.hpp"
#include <vector>
#include <memory>

class Scene {
public:
    std::shared_ptr<Background> background;
    std::shared_ptr<Camera> camera;
    std::vector<std::shared_ptr<Primitive>> objects;

    Scene(std::shared_ptr<Camera> cam, 
          std::shared_ptr<Background> bkg, 
          std::vector<std::shared_ptr<Primitive>> objs)
        : camera(cam), background(bkg), objects(objs) {}
};

#endif