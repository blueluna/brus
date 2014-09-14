#include "classicnoise.h"

ClassicNoise::ClassicNoise()
    : time(0.0)
{
}

void ClassicNoise::Generate(QImage *image)
{
    double x;
    double y;
    double z = time;
    double c;
    double cmin = 1000.0;
    double cmax = -1000.0;
    uint8_t color = 0;
    uint32_t color32 = 0;

    time += 0.01;

    int width = image->width();
    int height = image->height();

    for (int iy = 0; iy < height; iy++) {
        y = static_cast<double>(iy) / 10.0;
        for (int ix = 0; ix < width; ix++) {
            x = static_cast<double>(ix) / 10.0;
            c = NoiseFunc(x, y, z);

            cmin = c < cmin ? c : cmin;
            cmax = c > cmax ? c : cmax;
            color = (((c + 1.0) / 2.0) * 255);

            color32 = 0x00000000
                     | (color << 16)
                     | (color << 8)
                     | (color);

            image->setPixel(QPoint(ix, iy), color32);
        }
    }

    // qDebug("func: %f - %f\n", cmin, cmax);
}

double ClassicNoise::NoiseFunc(double xx, double yy, double zz)
{
    // Find unit grid cell containing point
    int X = floor(xx);
    int Y = floor(yy);
    int Z = floor(zz);

    // Get relative xyz coordinates of point within that cell
    double x = xx - X;
    double y = yy - Y;
    double z = zz - Z;

    // Wrap the integer cells at 255 (smaller integer period can be introduced here)
    X = X & 255;
    Y = Y & 255;
    Z = Z & 255;

    // Calculate a set of eight hashed gradient indices
    int p_z1 = permutations[Z];
    int p_z2 = permutations[Z + 1];
    int p_y1 = permutations[(Y + p_z1) % 256];
    int p_y2 = permutations[(Y + p_z2) % 256];
    int p_y3 = permutations[(Y + 1 + p_z1) % 256];
    int p_y4 = permutations[(Y + 1 + p_z2) % 256];
    int gi000 = permutations[(X + p_y1) % 256] % 12;
    int gi001 = permutations[(X + p_y2) % 256] % 12;
    int gi010 = permutations[(X + p_y3) % 256] % 12;
    int gi011 = permutations[(X + p_y4) % 256] % 12;
    int gi100 = permutations[(X + 1 + p_y1) % 256] % 12;
    int gi101 = permutations[(X + 1 + p_y2) % 256] % 12;
    int gi110 = permutations[(X + 1 + p_y3) % 256] % 12;
    int gi111 = permutations[(X + 1 + p_y4) % 256] % 12;

    // The gradients of each corner are now:
    // g000 = grad3[gi000];
    // g001 = grad3[gi001];
    // g010 = grad3[gi010];
    // g011 = grad3[gi011];
    // g100 = grad3[gi100];
    // g101 = grad3[gi101];
    // g110 = grad3[gi110];
    // g111 = grad3[gi111];

    // Calculate noise contributions from each of the eight corners
    double n000 = dot(gradients[gi000], x, y, z);
    double n100 = dot(gradients[gi100], x - 1, y, z);
    double n010 = dot(gradients[gi010], x, y - 1, z);
    double n110 = dot(gradients[gi110], x - 1, y - 1, z);
    double n001 = dot(gradients[gi001], x, y, z - 1);
    double n101 = dot(gradients[gi101], x - 1, y, z - 1);
    double n011 = dot(gradients[gi011], x, y - 1, z - 1);
    double n111 = dot(gradients[gi111], x - 1, y - 1, z - 1);

    // Compute the fade curve value for each of x, y, z
    double u = fade(x);
    double v = fade(y);
    double w = fade(z);

    // Interpolate along x the contributions from each of the corners
    double nx00 = mix(n000, n100, u);
    double nx01 = mix(n001, n101, u);
    double nx10 = mix(n010, n110, u);
    double nx11 = mix(n011, n111, u);

    // Interpolate the four results along y
    double nxy0 = mix(nx00, nx10, v);
    double nxy1 = mix(nx01, nx11, v);

    // Interpolate the two last results along z
    double nxyz = mix(nxy0, nxy1, w);

    return nxyz;
}
