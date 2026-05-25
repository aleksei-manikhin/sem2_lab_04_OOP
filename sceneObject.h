#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "transformMatrix.h"

class SceneObject {
public:
    virtual ~SceneObject() = default;

    virtual void Transform(const TransformMatrix& matrix) = 0;
};

#endif // SCENEOBJECT_H
