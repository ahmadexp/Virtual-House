// GLFW-based GLU function implementations for Linux
// These functions replace the GLU library functions

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <GLFW/glfw3.h>
#include <cmath>

// gluPerspective replacement
void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    GLdouble fH = tan(fovy / 360.0 * M_PI) * zNear;
    GLdouble fW = fH * aspect;
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

// gluOrtho2D replacement
void gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
{
    glOrtho(left, right, bottom, top, -1.0, 1.0);
}

// gluBuild2DMipmaps replacement - simplified version
GLint gluBuild2DMipmaps(GLenum target, GLint internalFormat, GLsizei width, GLsizei height, 
                        GLenum format, GLenum type, const void *data)
{
    // For now, just upload the base texture without mipmaps
    // A full implementation would need to generate mipmap levels
    glTexImage2D(target, 0, internalFormat, width, height, 0, format, type, data);
    
    // Optionally enable automatic mipmap generation if supported
    // This requires OpenGL 1.4+ or the GL_SGIS_generate_mipmap extension
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Note: Modern OpenGL would use glGenerateMipmap() but that requires OpenGL 3.0+
    // For now, we'll rely on the driver's automatic mipmap generation
    
    return 0;  // Success
}
