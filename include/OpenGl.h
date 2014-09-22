#ifndef OPENGL_H
#define OPENGL_H

#ifdef QT_CORE_LIB
#include <qopengl.h>
#else
#if !defined(HAVE_GLES)
#include <GL/gl.h>
#else
#include <GLES/gl.h>
#endif
#endif

#endif // OPENGL_H
