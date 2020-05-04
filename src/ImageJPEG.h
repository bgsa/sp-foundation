#ifndef IMAGE_JPEG_HEADER
#define IMAGE_JPEG_HEADER

#include "SpectrumFoundation.h"
#include <fstream>
#include "Image.h"

typedef struct
{
	WORD SOIMarker;         // start of image marker
	WORD APP0_Marker;       // Application use marker
	WORD APP0_Length;       // Length of APP0 field
	BYTE Identifier[5];     // zero terminating string "JFIF",X'4A', X'46', X'49', X'46', X'00'
	BYTE Version[2];        // X'01',X'02'
	BYTE Units;             // units = 0:no units ;; units = 1:X and Y are dots per inch ;; units = 2:X and Y are dots per cm
	WORD XDensity;          // horizontal pixel density
	WORD YDensity;          // vertical pixel density
	BYTE XThumbnail;        // Thumbnail horizontal pixel density
	BYTE YThumbnail;        // Thumbnail vertical pixel density
} JFIFHeader;

namespace NAMESPACE_FOUNDATION
{
	class ImageJPEG 
		: public Image
	{
	public:	
		API_INTERFACE inline ColorRGB getPixelRGB(sp_int x, sp_int y) override;
		
		API_INTERFACE static ImageJPEG * load(const sp_char* filename)
		{
			ImageJPEG *image = ALLOC_NEW(ImageJPEG)();
			FILE *file = fopen(filename, "rb");

			JFIFHeader fileHeader;
			fread(&fileHeader, sizeof(JFIFHeader), 1, file);

			fclose(file);
			ALLOC_DELETE(image, ImageJPEG);

			//NOT IMPLEMENTED EXCEPTION		

			return nullptr;
		}

	};
}

#endif // !IMAGE_JPEG_HEADER