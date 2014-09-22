#ifndef T3DOBJECT_H
#define T3DOBJECT_H

#include "OpenGl.h"
#include "TVertex.h"

class T3DObject
{
public:
    T3DObject();

    void SetTexture(GLuint textureId);

private:
    GLuint TextureID;
    GLuint VertexBuffer;
    TVertex Position;
    GLfloat Rotation;
};

#endif // T3DOBJECT_H
