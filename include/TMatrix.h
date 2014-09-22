#ifndef TMATRIX_H
#define TMATRIX_H

class TMatrix
{
public:
    TMatrix();

    static TMatrix Identity();

    static TMatrix Multipy(const TMatrix& a, const TMatrix& b);
    static TMatrix Inverse(const TMatrix& a);

    void Translate(float tx, float ty, float tz);
    void Scale(float sx, float sy, float sz);
    void Rotate(float angle, float x, float y, float z);

    static TMatrix Frustum(float left, float right, float bottom, float top, float nearZ, float farZ);
    static TMatrix Ortho(float left, float right, float bottom, float top, float nearZ, float farZ);
    static TMatrix Perspective(float fovy, float aspect, float zNear, float zFar);

public:
    float Matrix[4][4];

    static float PRECISION;
};

#endif // TMATRIX_H
