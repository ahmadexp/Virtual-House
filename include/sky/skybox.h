#ifndef __SKYBOX_H__
#define __SKYBOX_H__

// Don't include GL headers here - let the parent file handle it
// This avoids conflicts between GLFW and Windows GL headers

// Forward declarations for GL types
#ifndef GLint
typedef int GLint;
#endif
#ifndef GLuint
typedef unsigned int GLuint;
#endif

// Custom BMP loader for all platforms (glaux is deprecated)
typedef struct {
	GLint sizeX, sizeY;
	unsigned char *data;
} AUX_RGBImageRec;


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

	AUX_RGBImageRec * LoadBMP( const char * file );

	GLuint cube_map_texture_ID;
};

#endif