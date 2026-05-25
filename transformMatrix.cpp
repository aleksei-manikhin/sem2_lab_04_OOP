#include "transformMatrix.h"

#include <cmath>
#include <stdexcept>

TransformMatrix::TransformMatrix() {
    for (int row = 0; row < MatrixSize; row++) {
        for (int column = 0; column < MatrixSize; column++) {
            matr[row][column] = row == column ? 1.0f : 0.0f;
        }
    }
}

TransformMatrix TransformMatrix::operator*(const TransformMatrix& matrix) const {
    TransformMatrix result;

    for (int row = 0; row < MatrixSize; row++) {
        for (int column = 0; column < MatrixSize; column++) {
            float value = 0.0f;

            for (int index = 0; index < MatrixSize; index++) {
                value += matr[row][index] * matrix.matr[index][column];
            }

            result.SetValue(row, column, value);
        }
    }

    return result;
}

Point3D TransformMatrix::TransformPoint(const Point3D& point) const {
    float source[MatrixSize] = {point.X, point.Y, point.Z, 1.0f};
    float result[MatrixSize] = {};

    for (int row = 0; row < MatrixSize; row++) {
        for (int column = 0; column < MatrixSize; column++) {
            result[row] += matr[row][column] * source[column];
        }
    }

    return Point3D(result[0], result[1], result[2]);
}

float TransformMatrix::GetValue(int row, int column) const {
    ValidateIndex(row, column);

    return matr[row][column];
}

void TransformMatrix::SetValue(int row, int column, float value) {
    ValidateIndex(row, column);
    ValidateValue(value);

    matr[row][column] = value;
}

void TransformMatrix::ValidateIndex(int row, int column) {
    if (row < 0 || row >= MatrixSize || column < 0 || column >= MatrixSize) {
        throw std::out_of_range("Transform matrix index is out of range");
    }
}

void TransformMatrix::ValidateValue(float value) {
    if (!std::isfinite(value)) {
        throw std::invalid_argument("Transform matrix value must be finite");
    }
}
