#include "skybox.h"

#include <stdio.h>  
#ifdef _WIN32
#include <gl\gl.h>  
#include "glaux.h"
#else
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <cstring>
#include <cstdlib>
#include <cstdint>
#endif

#define GL_TEXTURE_CUBE_MAP_ARB             0x8513
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB  0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB  0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB  0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB  0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB  0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB  0x851A
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_TEXTURE_WRAP_R 0x8072

// Cross-platform implementation
bool SKYBOX::Initialize()
{
	char* extensions = (char*) glGetString(GL_EXTENSIONS); 

	if(strstr(extensions, "GL_ARB_texture_cube_map") != NULL)
	{
		GLenum cube_map_target[6] = {           
			GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
			GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB
		};

		AUX_RGBImageRec * texture_image[6];
		texture_image[0] = LoadBMP( "Media/sky/XN.bmp" );
		texture_image[1] = LoadBMP( "Media/sky/XP.bmp" );
		texture_image[2] = LoadBMP( "Media/sky/YN.bmp" );
		texture_image[3] = LoadBMP( "Media/sky/YP.bmp" );
		texture_image[4] = LoadBMP( "Media/sky/ZN.bmp" );
		texture_image[5] = LoadBMP( "Media/sky/ZP.bmp" );

		glGenTextures(1, &cube_map_texture_ID);

		glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, cube_map_texture_ID);

		for (int i = 0; i < 6; i++)
		{
			if (texture_image[i])				
			{
				glTexImage2D(cube_map_target[i], 0, 3, texture_image[i]->sizeX, texture_image[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_image[i]->data);

				if (texture_image[i]->data)	
				{
					free(texture_image[i]->data);	
				}
				free(texture_image[i]);	
			}
		}

	
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
		return true;
	} 

	return false;
}

void SKYBOX::Render( float camera_yaw, float camera_pitch )
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_CUBE_MAP_ARB); 
	glDisable(GL_LIGHTING);

	glDepthMask(GL_FALSE);

	DrawSkyBox( camera_yaw, camera_pitch );

	glDepthMask(GL_TRUE);

	glDisable(GL_TEXTURE_CUBE_MAP_ARB); 
	glEnable(GL_LIGHTING);
}

void SKYBOX::Finalize()
{
	// Suppression de la skybox
	glDeleteTextures( 1, &cube_map_texture_ID );
}

void SKYBOX::DrawSkyBox( float camera_yaw, float camera_pitch )
{
	// Cube size
	float t = 1.5f;

	//use of the cube map texture
	glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, cube_map_texture_ID);

	//setting the orientation
	glPushMatrix();
	glLoadIdentity();
	glRotatef( camera_pitch, 1.0f, 0.0f, 0.0f );
	glRotatef( camera_yaw, 0.0f, 1.0f, 0.0f );	
	

	// Rendering the geometry
	glBegin(GL_TRIANGLE_STRIP);			// X Negative	
		glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t); 	
		glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
		glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
		glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);			// X Positive
		glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
		glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
		glTexCoord3f(t,t,-t); glVertex3f(t,t,-t); 
		glTexCoord3f(t,t,t); glVertex3f(t,t,t); 	
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);			// Y Negative	
		glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t);
		glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
		glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
		glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);			// Y Positive		
		glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
		glTexCoord3f(t,t,-t); glVertex3f(t,t,-t); 
		glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
		glTexCoord3f(t,t,t); glVertex3f(t,t,t); 	
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);			// Z Negative		
		glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t);
		glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
		glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
		glTexCoord3f(t,t,-t); glVertex3f(t,t,-t); 
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);			// Z Positive	
		glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
		glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
		glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
		glTexCoord3f(t,t,t); glVertex3f(t,t,t); 	
	glEnd();

	// Reinitialization of the the mode view matrix
	glPopMatrix();
}


// Cross-platform LoadBMP
AUX_RGBImageRec * SKYBOX::LoadBMP(char *Filename)  // Loading Bitmap
{
    FILE *File = NULL;

    if (!Filename)
    {
        return NULL;
    }

    File = fopen(Filename, "rb");

    if (File)
    {
#ifdef _WIN32
        fclose(File);
        return auxDIBImageLoad(Filename);
#else
        // Custom BMP loader for non-Windows platforms
        uint16_t Type;          // signature - 'BM'
        uint32_t Size;          // file size in bytes
        uint16_t Reserved1;     // 0
        uint16_t Reserved2;     // 0
        uint32_t OffBits;       // offset to bitmap
        uint32_t StructSize;    // size of this struct (40)
        uint32_t Width;         // bmap width in pixels
        uint32_t Height;        // bmap height in pixels
        uint16_t Planes;        // num planes - always 1
        uint16_t BitCount;      // bits per pixel
        uint32_t Compression;   // compression flag
        uint32_t SizeImage;     // image size in bytes
        int32_t  XPelsPerMeter; // horz resolution
        int32_t  YPelsPerMeter; // vert resolution
        uint32_t ClrUsed;       // 0 -> color table size
        uint32_t ClrImportant;  // important color count

        fread(&Type, sizeof(uint16_t), 1, File);
        fread(&Size, sizeof(uint32_t), 1, File);
        fread(&Reserved1, sizeof(uint16_t), 1, File);
        fread(&Reserved2, sizeof(uint16_t), 1, File);
        fread(&OffBits, sizeof(uint32_t), 1, File);
        fread(&StructSize, sizeof(uint32_t), 1, File);
        fread(&Width, sizeof(uint32_t), 1, File);
        fread(&Height, sizeof(uint32_t), 1, File);
        fread(&Planes, sizeof(uint16_t), 1, File);
        fread(&BitCount, sizeof(uint16_t), 1, File);
        fread(&Compression, sizeof(uint32_t), 1, File);
        fread(&SizeImage, sizeof(uint32_t), 1, File);
        fread(&XPelsPerMeter, sizeof(int32_t), 1, File);
        fread(&YPelsPerMeter, sizeof(int32_t), 1, File);
        fread(&ClrUsed, sizeof(uint32_t), 1, File);
        fread(&ClrImportant, sizeof(uint32_t), 1, File);

        AUX_RGBImageRec* image = (AUX_RGBImageRec*)malloc(sizeof(AUX_RGBImageRec));
        image->sizeX = (GLint)Width;
        image->sizeY = (GLint)Height;
        
        // Calculate size if SizeImage is 0
        if (SizeImage == 0) {
            SizeImage = Width * Height * (BitCount / 8);
        }
        
        image->data = (unsigned char*)malloc(SizeImage);

        // Move to the beginning of bitmap data
        fseek(File, OffBits, SEEK_SET);

        // Read the data
        fread(image->data, 1, SizeImage, File);

        // Swap BGR to RGB if necessary (BMPs are usually BGR)
        // But for GL_RGB textures, we might need to swap. 
        // Let's assume the texture data is BGR as is standard for BMP.
        // However, standard GL_RGB expects RGB. 
        // We will swap bytes here.
        if (BitCount == 24) {
            unsigned char temp;
            for (unsigned int i = 0; i < SizeImage; i += 3) {
                temp = image->data[i];
                image->data[i] = image->data[i+2];
                image->data[i+2] = temp;
            }
        }

        fclose(File);
        return image;
#endif
    }

    return NULL;
}


