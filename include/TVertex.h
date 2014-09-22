#ifndef TVERTEX_H
#define TVERTEX_H

class TVertex
{
public:
    TVertex();
    TVertex(float x, float y, float z);

    void Set(float x, float y, float z);

public:
    float Vertex[3];
};

#endif // TVERTEX_H
