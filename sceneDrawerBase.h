#ifndef SCENEDRAWERBASE_H
#define SCENEDRAWERBASE_H

#include "scene.h"

class SceneDrawerBase {
public:
    virtual ~SceneDrawerBase() = default;

    virtual void DrawScene(const Scene& scene) = 0;
};

#endif // SCENEDRAWERBASE_H
