#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#ifdef _WIN32
#include "glaux.h"
#else
// For non-Windows platforms, use a stub or alternative image loading
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

// Stub for AUX_RGBImageRec
typedef struct {
	GLint sizeX, sizeY;
	unsigned char *data;
} AUX_RGBImageRec;
#endif


//#pragma comment(lib,"GLaux.lib")

class SKYBOX
{
public:
	SKYBOX(){}
	~SKYBOX(){}

	bool Initialize();
	void Render( float camera_yaw, float camera_pitch );
	void Finalize();

// Common interface for all platforms
private:
	void DrawSkyBox( float camera_yaw, float camera_pitch );

	AUX_RGBImageRec * LoadBMP( char * file );

	GLuint cube_map_texture_ID;
};

#endif