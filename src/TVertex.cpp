#include "TVertex.h"
#include <cstring>

TVertex::TVertex()
{
    memset(Vertex, 0, sizeof(float)*3);
}

TVertex::TVertex(float x, float y, float z)
{
    Vertex[0] = x;
    Vertex[1] = y;
    Vertex[2] = z;
}

void TVertex::Set(float x, float y, float z)
{
    Vertex[0] = x;
    Vertex[1] = y;
    Vertex[2] = z;
}
