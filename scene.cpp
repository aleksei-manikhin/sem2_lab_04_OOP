#include "scene.h"

#include <utility>

Scene::Scene(std::vector<Figure> figures)
    : figures(std::move(figures)) {}

const std::vector<Figure>& Scene::GetFigures() const {
    return figures;
}

void Scene::AddFigure(Figure&& figure) {
    figures.push_back(std::move(figure));
}

void Scene::TransformFigures(const TransformMatrix& matrix) {
    for (Figure& figure : figures) {
        figure.Transform(matrix);
    }
}
