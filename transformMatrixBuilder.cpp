#include "transformMatrixBuilder.h"

#include <cmath>
#include <stdexcept>

TransformMatrix TransformMatrixBuilder::CreateRotationXMatrix(float angle) {
    TransformMatrix matrix;
    const float sinValue = std::sin(angle);
    const float cosValue = std::cos(angle);

    matrix.SetValue(1, 1, cosValue);
    matrix.SetValue(1, 2, -sinValue);
    matrix.SetValue(2, 1, sinValue);
    matrix.SetValue(2, 2, cosValue);

    return matrix;
}

TransformMatrix TransformMatrixBuilder::CreateRotationYMatrix(float angle) {
    TransformMatrix matrix;
    const float sinValue = std::sin(angle);
    const float cosValue = std::cos(angle);

    matrix.SetValue(0, 0, cosValue);
    matrix.SetValue(0, 2, sinValue);
    matrix.SetValue(2, 0, -sinValue);
    matrix.SetValue(2, 2, cosValue);

    return matrix;
}

TransformMatrix TransformMatrixBuilder::CreateRotationZMatrix(float angle) {
    TransformMatrix matrix;
    const float sinValue = std::sin(angle);
    const float cosValue = std::cos(angle);

    matrix.SetValue(0, 0, cosValue);
    matrix.SetValue(0, 1, -sinValue);
    matrix.SetValue(1, 0, sinValue);
    matrix.SetValue(1, 1, cosValue);

    return matrix;
}

TransformMatrix TransformMatrixBuilder::CreateRotationMatrix(float x, float y, float z) {
    TransformMatrix xMatrix = CreateRotationXMatrix(x);
    TransformMatrix yMatrix = CreateRotationYMatrix(y);
    TransformMatrix zMatrix = CreateRotationZMatrix(z);

    return zMatrix * yMatrix * xMatrix;
}

TransformMatrix TransformMatrixBuilder::CreateMoveMatrix(float x, float y, float z) {
    TransformMatrix matrix;

    matrix.SetValue(0, 3, x);
    matrix.SetValue(1, 3, y);
    matrix.SetValue(2, 3, z);

    return matrix;
}

TransformMatrix TransformMatrixBuilder::CreateScaleMatrix(float x, float y, float z) {
    if (x <= 0.0f || y <= 0.0f || z <= 0.0f) {
        throw std::invalid_argument("Scale coefficients must be positive");
    }

    TransformMatrix matrix;

    matrix.SetValue(0, 0, x);
    matrix.SetValue(1, 1, y);
    matrix.SetValue(2, 2, z);

    return matrix;
}
