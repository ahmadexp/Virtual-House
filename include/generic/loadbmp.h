//http://www.codeproject.com/KB/cpp/endianness.aspx

#include <cstdint>
#include <cstdio>

uint32_t EndianFlipUnsignedLong(uint32_t nLongNumber){
   return (((nLongNumber&0x000000FF)<<24)+((nLongNumber&0x0000FF00)<<8)+
   ((nLongNumber&0x00FF0000)>>8)+((nLongNumber&0xFF000000)>>24));
}

int32_t EndianFlipLong(int32_t nLongNumber){
   return (((nLongNumber&0x000000FF)<<24)+((nLongNumber&0x0000FF00)<<8)+
   ((nLongNumber&0x00FF0000)>>8)+((nLongNumber&0xFF000000)>>24));
}

uint16_t EndianFlipUnsignedShort(uint16_t nValue){
	return (((nValue>> 8)) | (nValue << 8));
}

int16_t EndianFlipShort(int16_t nValue){
	return (((nValue>> 8)) | (nValue << 8));
}

GLuint loadbmp(char* filename,bool mipmap){

	uint16_t Type;          // signature - 'BM'
	uint32_t  Size;          // file size in bytes
	uint16_t Reserved1;     // 0
	uint16_t Reserved2;     // 0
	uint32_t  OffBits;       // offset to bitmap
	uint32_t  StructSize;    // size of this struct (40)
	uint32_t  Width;         // bmap width in pixels
	uint32_t  Height;        // bmap height in pixels
	uint16_t Planes;        // num planes - always 1
	uint16_t BitCount;      // bits per pixel
	uint32_t  Compression;   // compression flag
	uint32_t  SizeImage;     // image size in bytes
	int32_t           XPelsPerMeter; // horz resolution
	int32_t           YPelsPerMeter; // vert resolution
	uint32_t  ClrUsed;       // 0 -> color table size
	uint32_t  ClrImportant;  // important color count

	unsigned char	*pPixels = NULL;

	FILE	*fp = NULL;


	
	fp = fopen(filename,"rb");  // FIXED: use "rb" for binary mode!

	if(fp==NULL) {
		return 0;
	}

	if (fread(&Type,sizeof(uint16_t),1,fp) != 1 ||
	    fread(&Size,sizeof(uint32_t),1,fp) != 1 ||
	    fread(&Reserved1,sizeof(uint16_t),1,fp) != 1 ||
	    fread(&Reserved2,sizeof(uint16_t),1,fp) != 1 ||
	    fread(&OffBits,sizeof(uint32_t),1,fp) != 1 ||
	    fread(&StructSize,sizeof(uint32_t),1,fp) != 1 ||
	    fread(&Width,sizeof(uint32_t),1,fp) != 1 ||
	    fread(&Height,sizeof(uint32_t),1,fp) != 1 ||
	    fread(&Planes,sizeof(uint16_t),1,fp) != 1 ||
	    fread(&BitCount,sizeof(uint16_t),1,fp) != 1 ||
	    fread(&Compression,sizeof(uint32_t),1,fp) != 1 ||
	    fread(&SizeImage,sizeof(uint32_t),1,fp) != 1 ||
	    fread(&XPelsPerMeter,sizeof(int32_t),1,fp) != 1 ||
	    fread(&YPelsPerMeter,sizeof(int32_t),1,fp) != 1 ||
	    fread(&ClrUsed,sizeof(uint32_t),1,fp) != 1 ||
	    fread(&ClrImportant,sizeof(uint32_t),1,fp) != 1) {
		fclose(fp);
		return 0;
	}



	// Validate dimensions
	if (Width == 0 || Height == 0 || Width > 8192 || Height > 8192) {
		fclose(fp);
		return 0;
	}

	// Validate BitCount
	if (BitCount != 24 && BitCount != 32) {
		fclose(fp);
		return 0;
	}

	// Calculate bytes per pixel (FIXED: was using BitCount directly!)
	int bytesPerPixel = BitCount / 8;
	size_t imageSize = Width * Height * bytesPerPixel;
	


	pPixels = new unsigned char[imageSize];
	if (!pPixels) {
		fclose(fp);
		return 0;
	}
	
	// Read pixel data (FIXED: was using BitCount as element size!)
	size_t bytesRead = fread(pPixels, 1, imageSize, fp);
	fclose(fp);
	
	if (bytesRead != imageSize) {
		delete [] pPixels;
		return 0;
	}
	


	GLuint texName;
	glGenTextures(1,&texName);
	glBindTexture(GL_TEXTURE_2D,texName);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	if(mipmap){
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		if(BitCount==24)
			gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,Width,Height,
			#ifdef WIN32
			GL_BGR_EXT,GL_UNSIGNED_BYTE,pPixels);
			#else
			GL_BGR,GL_UNSIGNED_BYTE,pPixels);
			#endif
		if(BitCount==32)
			gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,Width,Height,
			GL_BGRA,GL_UNSIGNED_BYTE,pPixels);
	}else{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		if(BitCount==24)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,Width,Height,
			#ifdef WIN32
			0,GL_BGR_EXT,GL_UNSIGNED_BYTE,pPixels);
			#else
			0,GL_BGR,GL_UNSIGNED_BYTE,pPixels);
			#endif
		if(BitCount==32)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,Width,Height,
			0,GL_BGRA,GL_UNSIGNED_BYTE,pPixels);
	}


	delete [] pPixels;

	return texName;

}
