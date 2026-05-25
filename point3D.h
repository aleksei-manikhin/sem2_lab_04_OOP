#ifndef POINT3D_H
#define POINT3D_H

class Point3D {
public:
    float X = 0.0f;
    float Y = 0.0f;
    float Z = 0.0f;

    Point3D(float x, float y, float z)
        : X(x), Y(y), Z(z){}
};

#endif // POINT3D_H
