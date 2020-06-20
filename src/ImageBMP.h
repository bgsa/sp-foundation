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
typedef struct 
{
	sp_uint red_mask{ 0x00ff0000 };         // Bit mask for the red channel
	sp_uint green_mask{ 0x0000ff00 };       // Bit mask for the green channel
	sp_uint blue_mask{ 0x000000ff };        // Bit mask for the blue channel
	sp_uint alpha_mask{ 0xff000000 };       // Bit mask for the alpha channel
	sp_int color_space_type{ 0x73524742 }; // Default "sRGB" (0x73524742)
	sp_int unused[16]{ 0 };                // Unused data for sRGB color space
} BMPColorHeader;
#pragma pack(pop)

namespace NAMESPACE_FOUNDATION
{
	class ImageBMP 
		: public Image
	{
	private:

		inline void convertFromBGRToRGB(const sp_size size)
		{
			for (sp_size i = ZERO_SIZE; i < size; i += THREE_SIZE)
				std::swap(_data[i], _data[i + TWO_SIZE]);
		}

	public:

		ImageBMP()
		{
			colorFormat = 0x1907; // TODO: REMOVE!  GL_RGB constant
		}
		
		API_INTERFACE ColorRGB getPixelRGB(sp_int x, sp_int y) override;
		
		API_INTERFACE static ImageBMP* load(const sp_char* filename)
		{
			ImageBMP *image = sp_mem_new(ImageBMP)();
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

			image->data = ALLOC_ARRAY(sp_uchar, size); // allocate 3 bytes per pixel
			AAsset_read(file, image->data, size);

			AAsset_close(file);
	#endif
	#ifdef WINDOWS
			FILE *file;
			fopen_s(&file, filename, "rb");
			
			fread(&fileHeader, sizeof(BMPFileHeader), 1, file);
			fread(&headerInfo, sizeof(BMPHeaderInfo), 1, file);

			//sp_assert(headerInfo.bitCount == 8); // BMP images should be 8 bits ?!

			image->_width = headerInfo.width;
			image->_height = headerInfo.height;

			const sp_size size = THREE_INT * image->_width * image->_height;

			fseek(file, fileHeader.offBits, SEEK_SET);
			
			image->_data = (sp_uchar*) sp_mem_calloc(size, SIZEOF_UCHAR);
			fread(image->_data, SIZEOF_UCHAR, size, file);

			fclose(file);
	#endif
	#if defined(LINUX) || defined(OSX)
			FILE *file = fopen(filename, "rb");
			
			fread(&fileHeader, sizeof(BMPFileHeader), 1, file);
			fread(&headerInfo, sizeof(BMPHeaderInfo), 1, file);

			//sp_assert(headerInfo.bitCount == 8); // BMP images should be 8 bits ?!

			image->_width = headerInfo.width;
			image->_height = headerInfo.height;

			const sp_size size = THREE_INT * image->_width * image->_height;

			fseek(file, fileHeader.offBits, SEEK_SET);
			
			image->_data = (sp_uchar*) sp_mem_calloc(size, SIZEOF_UCHAR);
			fread(image->_data, SIZEOF_UCHAR, size, file);

			fclose(file);
	#endif
			image->convertFromBGRToRGB(size);

			return image;
		}

		~ImageBMP()
		{
			if (_data != NULL)
			{
				sp_mem_release(_data);
			}
		}

	};
}

#endif // !IMAGE_BMP_HEADER
