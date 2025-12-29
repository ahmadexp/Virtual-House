#include <cstdio>
#include <cstdint>

uint16_t ByteSwap4 (uint16_t nValue){
	//http://www.codeproject.com/KB/cpp/endianness.aspx
	return (((nValue>> 8)) | (nValue << 8));
}

GLuint loadtga(char* filename,bool mipmap){

	unsigned char	header[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	unsigned char	bpp = 32;
	unsigned char	id = 8;
	unsigned short	width;
	unsigned short	height;
	unsigned char	*pPixels = NULL;
	FILE	*fp = NULL;

	// printf("DEBUG: loadtga() - about to open '%s'\n", filename);
	// fflush(stdout);
	
	fp = fopen(filename,"rb");  // FIXED: use "rb" for binary mode!
	
	if (!fp) {
		// printf("ERROR: loadtga() - failed to open '%s'\n", filename);
		// fflush(stdout);
		return 0;
	}
	
	// printf("DEBUG: loadtga() - file opened successfully\n");
	// fflush(stdout);

	fread(header,sizeof(unsigned char),12,fp);
	fread(&width,sizeof(unsigned short),1,fp);
	fread(&height,sizeof(unsigned short),1,fp);
	fread(&bpp,sizeof(unsigned char),1,fp);
	fread(&id,sizeof(unsigned char),1,fp);
	
	printf("DEBUG: loadtga() - width=%u height=%u bpp=%u id=%u\n", width, height, bpp, id);
	fflush(stdout);

	pPixels = new unsigned char[width * height * 4];
	fread(pPixels, 4, width * height, fp);
	fclose(fp);
	
	// printf("DEBUG: loadtga() - read pixels, creating OpenGL texture\n");
	// fflush(stdout);

	GLuint texName;
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);	
	glGenTextures(1,&texName);
	glBindTexture(GL_TEXTURE_2D,texName);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	if(mipmap){
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,width,height,
#ifdef _WIN32
			GL_BGRA_EXT,GL_UNSIGNED_BYTE,pPixels);
#else
			GL_BGRA,GL_UNSIGNED_BYTE,pPixels);
#endif
	}else{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,
#ifdef _WIN32
			0,GL_BGRA_EXT,GL_UNSIGNED_BYTE,pPixels);
#else
			0,GL_BGRA,GL_UNSIGNED_BYTE,pPixels);
#endif
	}

	printf("DEBUG: loadtga() - about to delete[] pPixels\n");
	fflush(stdout);
	delete [] pPixels;
	printf("DEBUG: loadtga() - delete[] pPixels succeeded\n");
	fflush(stdout);

	return texName;


}
