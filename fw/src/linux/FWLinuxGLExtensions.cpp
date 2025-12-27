#include "FWLinuxGLInclude.h"
#include <cmath>

// Stub implementation – no actual OpenGL extension handling needed for build.

void gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
{
    glOrtho(left, right, bottom, top, -1.0, 1.0);
}

void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    GLdouble m[16];
    for(int i = 0; i < 16; i++) m[i] = 0.0;

    GLdouble radians = fovy / 2.0 * 3.14159265358979323846 / 180.0;
    GLdouble f = 1.0 / std::tan(radians);

    m[0] = f / aspect;
    m[5] = f;
    m[10] = (zFar + zNear) / (zNear - zFar);
    m[11] = -1.0;
    m[14] = (2.0 * zFar * zNear) / (zNear - zFar);
    
    glMultMatrixd(m);
}
