#include "transformMatrix.h"

TransformMatrix::TransformMatrix() {
    for (int row = 0; row < MatrixSize; row++) {
        for (int column = 0; column < MatrixSize; column++) {
            matr[row][column] = row == column ? 1.0f : 0.0f;
        }
    }
}

TransformMatrix::TransformMatrix(const float matrixValues[MatrixSize][MatrixSize]) {
    for (int row = 0; row < MatrixSize; row++) {
        for (int column = 0; column < MatrixSize; column++) {
            matr[row][column] = matrixValues[row][column];
        }
    }
}

TransformMatrix TransformMatrix::operator*(const TransformMatrix& matrix) const {
    float result[MatrixSize][MatrixSize] = {};

    for (int row = 0; row < MatrixSize; row++) {
        for (int column = 0; column < MatrixSize; column++) {
            for (int index = 0; index < MatrixSize; index++) {
                result[row][column] += matr[row][index] * matrix.matr[index][column];
            }
        }
    }

    return TransformMatrix(result);
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
    return matr[row][column];
}
