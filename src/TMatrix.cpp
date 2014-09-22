#include "TMatrix.h"
#include <cmath>
#include <stdexcept>
#include "MathConstants.h"

float TMatrix::PRECISION = static_cast<float>(1.0e-15);

TMatrix::TMatrix()
{
    memset(Matrix, 0, sizeof(float) * 16);
}


TMatrix TMatrix::Identity()
{
    TMatrix m;
    m.Matrix[0][0] = 1.0f;
    m.Matrix[1][1] = 1.0f;
    m.Matrix[2][2] = 1.0f;
    m.Matrix[3][3] = 1.0f;
    return m;
}

TMatrix TMatrix::Multipy(const TMatrix &a, const TMatrix &b)
{
    TMatrix m;
    for (int i = 0; i < 4; i++) {
        m.Matrix[i][0] = (a.Matrix[i][0] * b.Matrix[0][0]) +
                        (a.Matrix[i][1] * b.Matrix[1][0]) +
                        (a.Matrix[i][2] * b.Matrix[2][0]) +
                        (a.Matrix[i][3] * b.Matrix[3][0]) ;

        m.Matrix[i][1] = (a.Matrix[i][0] * b.Matrix[0][1]) +
                        (a.Matrix[i][1] * b.Matrix[1][1]) +
                        (a.Matrix[i][2] * b.Matrix[2][1]) +
                        (a.Matrix[i][3] * b.Matrix[3][1]) ;

        m.Matrix[i][2] = (a.Matrix[i][0] * b.Matrix[0][2]) +
                        (a.Matrix[i][1] * b.Matrix[1][2]) +
                        (a.Matrix[i][2] * b.Matrix[2][2]) +
                        (a.Matrix[i][3] * b.Matrix[3][2]) ;

        m.Matrix[i][3] = (a.Matrix[i][0] * b.Matrix[0][3]) +
                        (a.Matrix[i][1] * b.Matrix[1][3]) +
                        (a.Matrix[i][2] * b.Matrix[2][3]) +
                        (a.Matrix[i][3] * b.Matrix[3][3]) ;
    }
    return m;
}

TMatrix TMatrix::Inverse(const TMatrix &in)
{
    float det_1;
    float abssum, temp;

    /*
    Calculate the determinant of submatrix A and determine if the
    the matrix is singular.
    */
    temp =  in.Matrix[0][0] * in.Matrix[1][1] * in.Matrix[2][2];
    det_1 = temp;
    abssum = fabsf(temp);
    temp =  in.Matrix[1][0] * in.Matrix[2][1] * in.Matrix[0][2];
    det_1 += temp;
    abssum += fabsf(temp);
    temp =  in.Matrix[2][0] * in.Matrix[0][1] * in.Matrix[1][2];
    det_1 += temp;
    abssum += fabsf(temp);
    temp = -in.Matrix[2][0] * in.Matrix[1][1] * in.Matrix[0][2];
    det_1 += temp;
    abssum += fabsf(temp);
    temp = -in.Matrix[1][0] * in.Matrix[0][1] * in.Matrix[2][2];
    det_1 += temp;
    abssum += fabsf(temp);
    temp = -in.Matrix[0][0] * in.Matrix[2][1] * in.Matrix[1][2];
    det_1 += temp;
    abssum += fabsf(temp);

    /* Is the submatrix A singular? */
    if ((det_1 == 0.0f) || (fabsf(det_1 / abssum) < PRECISION))
    {
        /* Matrix M has no inverse */
        throw std::exception();
    }
    else
    {
        /* Calculate inverse(A) = adj(A) / det(A) */
        det_1 = 1.0f / det_1;
        TMatrix result;
        result.Matrix[0][0] = (in.Matrix[1][1] * in.Matrix[2][2] - in.Matrix[2][1] * in.Matrix[1][2]) * det_1;
        result.Matrix[0][1] = -(in.Matrix[1][0] * in.Matrix[2][2] - in.Matrix[2][0] * in.Matrix[1][2]) * det_1;
        result.Matrix[0][2] = (in.Matrix[1][0] * in.Matrix[2][1] - in.Matrix[2][0] * in.Matrix[1][1]) * det_1;

        result.Matrix[1][0] = -(in.Matrix[0][1] * in.Matrix[2][2] - in.Matrix[2][1] * in.Matrix[0][2]) * det_1;
        result.Matrix[1][1] = (in.Matrix[0][0] * in.Matrix[2][2] - in.Matrix[2][0] * in.Matrix[0][2]) * det_1;
        result.Matrix[1][2] = -(in.Matrix[0][0] * in.Matrix[2][1] - in.Matrix[2][0] * in.Matrix[0][1]) * det_1;

        result.Matrix[2][0] = (in.Matrix[0][1] * in.Matrix[1][2] - in.Matrix[1][1] * in.Matrix[0][2]) * det_1;
        result.Matrix[2][1] = -(in.Matrix[0][0] * in.Matrix[1][2] - in.Matrix[1][0] * in.Matrix[0][2]) * det_1;
        result.Matrix[2][2] = (in.Matrix[0][0] * in.Matrix[1][1] - in.Matrix[1][0] * in.Matrix[0][1]) * det_1;

        result.Matrix[3][3] = 1.0f;

        /* Calculate -C * inverse(A) */
        result.Matrix[3][0] = -(in.Matrix[0][3] * result.Matrix[0][0] + in.Matrix[1][3] * result.Matrix[1][0] + in.Matrix[2][3] * result.Matrix[2][0]);
        result.Matrix[3][1] = -(in.Matrix[0][3] * result.Matrix[0][1] + in.Matrix[1][3] * result.Matrix[1][1] + in.Matrix[2][3] * result.Matrix[2][1]),
        result.Matrix[3][2] = -(in.Matrix[0][3] * result.Matrix[0][2] + in.Matrix[1][3] * result.Matrix[1][2] + in.Matrix[2][3] * result.Matrix[2][2]),
        result.Matrix[3][3] = 1.0;

        return result;
    }
}

void TMatrix::Translate(float tx, float ty, float tz)
{
    Matrix[3][0] += (Matrix[0][0] * tx + Matrix[1][0] * ty + Matrix[2][0] * tz);
    Matrix[3][1] += (Matrix[0][1] * tx + Matrix[1][1] * ty + Matrix[2][1] * tz);
    Matrix[3][2] += (Matrix[0][2] * tx + Matrix[1][2] * ty + Matrix[2][2] * tz);
    Matrix[3][3] += (Matrix[0][3] * tx + Matrix[1][3] * ty + Matrix[2][3] * tz);
}

void TMatrix::Scale(float sx, float sy, float sz)
{
    Matrix[0][0] *= sx;
    Matrix[0][1] *= sx;
    Matrix[0][2] *= sx;
    Matrix[0][3] *= sx;

    Matrix[1][0] *= sy;
    Matrix[1][1] *= sy;
    Matrix[1][2] *= sy;
    Matrix[1][3] *= sy;

    Matrix[2][0] *= sz;
    Matrix[2][1] *= sz;
    Matrix[2][2] *= sz;
    Matrix[2][3] *= sz;
}

void TMatrix::Rotate(float angle, float x, float y, float z)
{
    float sinAngle, cosAngle;
    float mag = sqrtf(x * x + y * y + z * z);

    sinAngle = sinf(angle * PI / 180.0f);
    cosAngle = cosf(angle * PI / 180.0f);
    if (mag > 0.0f)
    {
        float xx, yy, zz, xy, yz, zx, xs, ys, zs;
        float oneMinusCos;

        x /= mag;
        y /= mag;
        z /= mag;

        xx = x * x;
        yy = y * y;
        zz = z * z;
        xy = x * y;
        yz = y * z;
        zx = z * x;
        xs = x * sinAngle;
        ys = y * sinAngle;
        zs = z * sinAngle;
        oneMinusCos = 1.0f - cosAngle;

        /*
        TMatrix rotation {
            {(oneMinusCos * xx) + cosAngle, (oneMinusCos * xy) + zs, (oneMinusCos * zx) - ys, 0.0f},
            {(oneMinusCos * xy) - zs, (oneMinusCos * yy) + cosAngle, (oneMinusCos * yz) + xs, 0.0f},
            {(oneMinusCos * zx) + ys, (oneMinusCos * yz) - xs, (oneMinusCos * zz) + cosAngle, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
        };
        */

        TMatrix rotation;

        rotation.Matrix[0][0] = (oneMinusCos * xx) + cosAngle;
        rotation.Matrix[0][1] = (oneMinusCos * xy) + zs;
        rotation.Matrix[0][2] = (oneMinusCos * zx) - ys;

        rotation.Matrix[1][0] = (oneMinusCos * xy) - zs;
        rotation.Matrix[1][1] = (oneMinusCos * yy) + cosAngle;
        rotation.Matrix[1][2] = (oneMinusCos * yz) + xs;

        rotation.Matrix[2][0] = (oneMinusCos * zx) + ys;
        rotation.Matrix[2][1] = (oneMinusCos * yz) - xs;
        rotation.Matrix[2][2] = (oneMinusCos * zz) + cosAngle;

        rotation.Matrix[3][3] = 1.0f;

        *this = TMatrix::Multipy(rotation, *this);
    }
}

TMatrix TMatrix::Frustum(float left, float right, float bottom, float top, float nearZ, float farZ)
{
    float deltaX = right - left;
    float deltaY = top - bottom;
    float deltaZ = farZ - nearZ;

    if ((nearZ <= 0.0f) || (farZ <= 0.0f) || (deltaX <= 0.0f) || (deltaY <= 0.0f) || (deltaZ <= 0.0f)) {
        throw std::exception();
    }

    /*
    TMatrix furstum {
        {2.0f * nearZ / deltaX, 0.0f, 0.0f, 0.0f},
        {0.0f, 2.0f * nearZ / deltaY, 0.0f, 0.0f},
        {(right + left) / deltaX, (top + bottom) / deltaY, -(nearZ + farZ) / deltaZ, -1.0f},
        {0.0f, 0.0f, -2.0f * nearZ * farZ / deltaZ, 0.0f}
    };
    */

    TMatrix furstum;
    furstum.Matrix[0][0] = 2.0f * nearZ / deltaX;
    furstum.Matrix[1][1] = 2.0f * nearZ / deltaY;
    furstum.Matrix[2][0] = (right + left) / deltaX;
    furstum.Matrix[2][1] = (top + bottom) / deltaY;
    furstum.Matrix[2][2] = -(nearZ + farZ) / deltaZ;
    furstum.Matrix[2][3] = -1.0f;
    furstum.Matrix[3][2] = -2.0f * nearZ * farZ / deltaZ;

    return TMatrix::Multipy(furstum, TMatrix::Identity());
}

TMatrix TMatrix::Ortho(float left, float right, float bottom, float top, float nearZ, float farZ)
{
    float deltaX = right - left;
    float deltaY = top - bottom;
    float deltaZ = farZ - nearZ;

    if ((deltaX == 0.0f) || (deltaY == 0.0f) || (deltaZ == 0.0f)) {
        throw std::exception();
    }

    /*
    TMatrix ortho {
        {2.0f / deltaX, 0.0f, 0.0f, 0.0f},
        {0.0f, 2.0f / deltaY, 0.0f, 0.0f},
        {0.0f, 0.0f, -2.0f / deltaZ, 0.0f},
        {-(right + left) / deltaX, -(top + bottom) / deltaY, -(nearZ + farZ) / deltaZ, 1.0f}

    };
    */

    TMatrix ortho;
    ortho.Matrix[0][0] = 2.0f / deltaX;
    ortho.Matrix[1][1] = 2.0f / deltaX;
    ortho.Matrix[2][2] = -2.0f / deltaZ;
    ortho.Matrix[3][0] = -(right + left) / deltaX;
    ortho.Matrix[3][1] = -(top + bottom) / deltaY;
    ortho.Matrix[3][2] = -(nearZ + farZ) / deltaZ;
    ortho.Matrix[3][3] = 1.0f;

    return TMatrix::Multipy(ortho, TMatrix::Identity());
}

TMatrix TMatrix::Perspective(float fovy, float aspect, float zNear, float zFar)
{
    float sine, cotangent, deltaZ;
    float radians = fovy / 2.0f * PI / 180.0f;

    deltaZ = zFar - zNear;
    sine = sinf(radians);
    if ((deltaZ == 0) || (sine == 0) || (aspect == 0)) {
        throw std::exception();
    }
    cotangent = cosf(radians) / sine;

    TMatrix perspective;
    perspective.Matrix[0][0] = cotangent / aspect;
    perspective.Matrix[1][1] = cotangent;
    perspective.Matrix[2][2] = -(zFar + zNear) / deltaZ;
    perspective.Matrix[2][3] = -1.0f;
    perspective.Matrix[3][2] = -2 * zNear * zFar / deltaZ;

    return TMatrix::Multipy(perspective, TMatrix::Identity());
}
