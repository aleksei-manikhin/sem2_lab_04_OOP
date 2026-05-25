#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H

#include "point3D.h"

class TransformMatrix {
public:
    static constexpr int MatrixSize = 4;

private:
    float matr[MatrixSize][MatrixSize];

public:
    TransformMatrix();

    TransformMatrix operator*(const TransformMatrix& matrix) const;
    Point3D TransformPoint(const Point3D& point) const;

    float GetValue(int row, int column) const;
    void SetValue(int row, int column, float value);
};

#endif // TRANSFORMMATRIX_H
