#ifndef IMAGE_BMP_HEADER
#define IMAGE_BMP_HEADER

#include "SpectrumFoundation.h"
#include <fstream>
#include "Image.h"
#include <cstdio>

#ifdef ANDROID
#include <android/asset_manager.h> 
#include "FileManagerAndroid.h"
#endif

#pragma pack(push, 2)
typedef struct
{
	sp_char   type[2];
	sp_uint   size;
	sp_ushort reserved1;
	sp_ushort reserved2;
	sp_uint   offBits;
} BMPFileHeader;
typedef struct
{
	sp_uint   size;            /* Size of info header */
	sp_int            width;           /* Width of image */
	sp_int            height;          /* Height of image */
	sp_ushort planes;          /* Number of color planes */
	sp_ushort bitCount;        /* Number of bits per pixel */
	sp_uint   compression;     /* Type of compression to use (0=none, 1=RLE-8, 2=RLE-4) */
	sp_uint   sizeImage;       /* Size of image data (including padding) */
	sp_int            xPelsPerMeter;   /* X pixels per meter - horizontal resolution in pixels per meter (unreliable) */
	sp_int            yPelsPerMeter;   /* Y pixels per meter - vertical resolution in pixels per meter (unreliable) */
	sp_uint   colorsUsed;      /* Number of colors used */
	sp_uint   colorsImportant; /* Number of important colors */
} BMPHeaderInfo;
#pragma pack(pop)

namespace NAMESPACE_FOUNDATION
{
	class ImageBMP : public Image
	{
	private:

	public:
		
		ColorRGBc getPixelRGB(sp_int x, sp_int y);
		
		static ImageBMP * load(const sp_char* filename)
		{
			const sp_uint opengl_RGB = 0x1907; //TODO: REMOVE!

			ImageBMP *image = ALLOC_NEW(ImageBMP)();
			image->colorFormat = opengl_RGB;

			BMPFileHeader fileHeader;
			BMPHeaderInfo headerInfo;
					
	#ifdef ANDROID
			FileManagerAndroid fileManager;
			AAssetManager *assetManager = fileManager.getAssetManager();
			AAsset* file = AAssetManager_open(assetManager, filename, AASSET_MODE_RANDOM);

			AAsset_read(file, &fileHeader, sizeof(BMPFileHeader));
			AAsset_read(file, &headerInfo, sizeof(BMPHeaderInfo));
			
			image->width = headerInfo.width;
			image->height = headerInfo.height;

			sp_uint size = 3 * image->width * image->height;
			image->data = ALLOC_ARRAY(sp_uchar, size); // allocate 3 bytes per pixel
			AAsset_read(file, image->data, size);

			AAsset_close(file);
	#endif
	#ifdef WINDOWS
			FILE *file;
			fopen_s(&file, filename, "rb");
			
			fread(&fileHeader, sizeof(BMPFileHeader), 1, file);
			fread(&headerInfo, sizeof(BMPHeaderInfo), 1, file);

			image->width = headerInfo.width;
			image->height = headerInfo.height;

			fseek(file, 54 * SIZEOF_CHAR, SEEK_SET); //move o cursor para a posi��o 54 do arquivo, contando do in�cio
			
			unsigned int size = 3 * image->width * image->height;
			image->data = ALLOC_ARRAY(sp_uchar, size); // allocate 3 bytes per pixel
			fread(image->data, SIZEOF_UCHAR, size, file); // read the rest of the data at once

			fclose(file);
	#endif
			//coloca no formato RGB ao inv�s de BGR
			/*		
			for (int i = 0; i < size; i += 3)		
			{
				unsigned char tmp = image->data[i];
				image->data[i] = image->data[i + 2];
				image->data[i + 2] = tmp;
			}
			*/

			/*
			int padding = 0;
			int scanlinebytes = image->width * 3;
			while ((scanlinebytes + padding) % 4 != 0)
				padding++;
			int psw = scanlinebytes + padding;
			
			long bufpos = 0;
			long newpos = 0;
			for (int y = 0; y < image->height; y++)
				for (int x = 0; x < 3 * image->width; x += 3)
				{
					newpos = y * 3 * image->width + x;
					bufpos = (image->height - y - 1) * psw + x;

					image->data[newpos] = image->data[bufpos + 2];
					image->data[newpos + 1] = image->data[bufpos + 1];
					image->data[newpos + 2] = image->data[bufpos];
				}
				*/

			return image;
		}

	};
}

#endif // !IMAGE_BMP_HEADER