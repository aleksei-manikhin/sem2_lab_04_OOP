#ifndef TRANSFORMMATRIXBUILDER_H
#define TRANSFORMMATRIXBUILDER_H

#include "transformMatrix.h"

class TransformMatrixBuilder {
private:
    static TransformMatrix CreateRotationXMatrix(float angle);
    static TransformMatrix CreateRotationYMatrix(float angle);
    static TransformMatrix CreateRotationZMatrix(float angle);

public:
    static TransformMatrix CreateRotationMatrix(float x, float y, float z);
    static TransformMatrix CreateMoveMatrix(float x, float y, float z);
    static TransformMatrix CreateScaleMatrix(float x, float y, float z);
};

#endif // TRANSFORMMATRIXBUILDER_H
