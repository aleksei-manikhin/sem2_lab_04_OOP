#ifndef FACADE_H
#define FACADE_H

#include "baseFileReader.h"
#include "facadeOperationResult.h"
#include "normalizationParameters.h"
#include "scene.h"
#include "sceneDrawerBase.h"

#include <string>

class Facade {
private:
    BaseFileReader& fileReader;
    SceneDrawerBase& sceneDrawer;
    Scene scene;

    FacadeOperationResult ApplyTransform(const TransformMatrix& matrix);

public:
    Facade(BaseFileReader& fileReader, SceneDrawerBase& sceneDrawer);

    FacadeOperationResult DrawScene();
    FacadeOperationResult LoadScene(const std::string& path, const NormalizationParameters& parameters);
    FacadeOperationResult LoadScene(const std::string& path, float min, float max, float dxStep, float dyStep);
    FacadeOperationResult MoveScene(float x, float y, float z); //
    FacadeOperationResult RotateScene(float x, float y, float z);
    FacadeOperationResult ScaleScene(float x, float y, float z);
};

#endif // FACADE_H
