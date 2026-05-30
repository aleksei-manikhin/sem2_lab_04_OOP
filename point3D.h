#ifndef POINT3D_H
#define POINT3D_H

class Point3D {
private:
    float X = 0.0f;
    float Y = 0.0f;
    float Z = 0.0f;

public:
    Point3D(float x, float y, float z)
        : X(x), Y(y), Z(z) {}

    float GetX() const {
        return X;
    }

    float GetY() const {
        return Y;
    }

    float GetZ() const {
        return Z;
    }

};

#endif // POINT3D_H
