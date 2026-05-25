#ifndef SCENE_H
#define SCENE_H

#include "figure.h"
#include "transformMatrix.h"

#include <vector>

class Scene {
private:
    std::vector<Figure> figures;

public:
    Scene() = default;
    explicit Scene(std::vector<Figure> figures);

    Scene(const Scene& scene) = delete;
    Scene& operator=(const Scene& scene) = delete;
    Scene(Scene&& scene) noexcept = default;
    Scene& operator=(Scene&& scene) noexcept = default;

    const std::vector<Figure>& GetFigures() const;
    void AddFigure(Figure&& figure);
    void TransformFigures(const TransformMatrix& matrix);
};

#endif // SCENE_H
