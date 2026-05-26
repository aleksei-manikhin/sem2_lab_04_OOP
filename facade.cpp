#include "facade.h"

#include "transformMatrixBuilder.h"

#include <exception>

Facade::Facade(BaseFileReader& fileReader, SceneDrawerBase& sceneDrawer)
    : fileReader(fileReader), sceneDrawer(sceneDrawer) {}

FacadeOperationResult Facade::DrawScene() {
    try {
        sceneDrawer.DrawScene(scene, true);
        return FacadeOperationResult(true, "");
    } catch (const std::exception& exception) {
        return FacadeOperationResult(false, exception.what());
    }
}

FacadeOperationResult Facade::LoadScene(const std::string& path,
                                        const NormalizationParameters& parameters) {
    try {
        scene = fileReader.ReadScene(path, parameters);
        sceneDrawer.DrawScene(scene, true);

        return FacadeOperationResult(true, "");
    } catch (const std::exception& exception) {
        return FacadeOperationResult(false, exception.what());
    }
}

FacadeOperationResult Facade::LoadScene(const std::string& path,
                                        float min, float max, float dxStep, float dyStep) {
    try {
        return LoadScene(path, NormalizationParameters(min, max, dxStep, dyStep));
    } catch (const std::exception& exception) {
        return FacadeOperationResult(false, exception.what());
    }
}

FacadeOperationResult Facade::MoveScene(float x, float y, float z) {
    try {
        return ApplyTransform(TransformMatrixBuilder::CreateMoveMatrix(x, y, z));
    } catch (const std::exception& exception) {
        return FacadeOperationResult(false, exception.what());
    }
}

FacadeOperationResult Facade::RotateScene(float x, float y, float z) {
    try {
        return ApplyTransform(TransformMatrixBuilder::CreateRotationMatrix(x, y, z));
    } catch (const std::exception& exception) {
        return FacadeOperationResult(false, exception.what());
    }
}

FacadeOperationResult Facade::ScaleScene(float x, float y, float z) {
    try {
        return ApplyTransform(TransformMatrixBuilder::CreateScaleMatrix(x, y, z));
    } catch (const std::exception& exception) {
        return FacadeOperationResult(false, exception.what());
    }
}

FacadeOperationResult Facade::ApplyTransform(const TransformMatrix& matrix) {
    try {
        scene.TransformFigures(matrix);
        sceneDrawer.DrawScene(scene, false);

        return FacadeOperationResult(true, "");
    } catch (const std::exception& exception) {
        return FacadeOperationResult(false, exception.what());
    }
}
