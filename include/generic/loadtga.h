#include <cstdio>
#include <cstdint>
#include <cstring>

uint16_t ByteSwap4 (uint16_t nValue){
	//http://www.codeproject.com/KB/cpp/endianness.aspx
	return (((nValue>> 8)) | (nValue << 8));
}

GLuint loadtga(char* filename,bool mipmap){

	unsigned char	actualHeader[12];
	unsigned char	bpp = 32;
	unsigned char	id = 8;
	unsigned short	width;
	unsigned short	height;
	unsigned char	*pPixels = NULL;
	FILE	*fp = NULL;


	
	fp = fopen(filename,"rb");  // FIXED: use "rb" for binary mode!
	
	if (!fp) {
		return 0;
	}
	


	// Read and validate header
	size_t headerRead = fread(actualHeader,sizeof(unsigned char),12,fp);
	if (headerRead != 12) {
		fclose(fp);
		return 0;
	}
	
	// Read dimensions
	if (fread(&width,sizeof(unsigned short),1,fp) != 1 ||
	    fread(&height,sizeof(unsigned short),1,fp) != 1 ||
	    fread(&bpp,sizeof(unsigned char),1,fp) != 1 ||
	    fread(&id,sizeof(unsigned char),1,fp) != 1) {
		fclose(fp);
		return 0;
	}
	

	
	// Validate dimensions to prevent huge allocations
	if (width == 0 || height == 0 || width > 8192 || height > 8192) {
		fclose(fp);
		return 0;
	}
	
	// Validate bpp
	if (bpp != 24 && bpp != 32) {
		fclose(fp);
		return 0;
	}
	
	// Calculate bytes per pixel
	int bytesPerPixel = bpp / 8;
	size_t imageSize = width * height * bytesPerPixel;
	


	// Allocate buffer for actual image data
	unsigned char *rawPixels = new unsigned char[imageSize];
	if (!rawPixels) {
		fclose(fp);
		return 0;
	}
	
	// Read pixel data
	size_t bytesRead = fread(rawPixels, 1, imageSize, fp);
	fclose(fp);
	
	if (bytesRead != imageSize) {
		delete [] rawPixels;
		return 0;
	}
	

	
	// Convert to RGBA if needed
	pPixels = new unsigned char[width * height * 4];
	if (!pPixels) {
		delete [] rawPixels;
		return 0;
	}
	
	if (bpp == 32) {
		// Already RGBA/BGRA, just copy
		memcpy(pPixels, rawPixels, imageSize);
	} else {
		// Convert BGR to BGRA
		for (size_t i = 0; i < width * height; i++) {
			pPixels[i*4 + 0] = rawPixels[i*3 + 0]; // B
			pPixels[i*4 + 1] = rawPixels[i*3 + 1]; // G
			pPixels[i*4 + 2] = rawPixels[i*3 + 2]; // R
			pPixels[i*4 + 3] = 255;                 // A
		}
	}
	
	delete [] rawPixels;
	


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


	delete [] pPixels;


	return texName;


}
