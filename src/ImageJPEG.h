#ifndef IMAGE_JPEG_HEADER
#define IMAGE_JPEG_HEADER

#include "SpectrumFoundation.h"
#include <fstream>
#include "Image.h"

typedef struct
{
	sp_word SOIMarker;         // start of image marker
	sp_word APP0_Marker;       // Application use marker
	sp_word APP0_Length;       // Length of APP0 field
	sp_byte Identifier[5];     // zero terminating string "JFIF",X'4A', X'46', X'49', X'46', X'00'
	sp_byte Version[2];        // X'01',X'02'
	sp_byte Units;             // units = 0:no units ;; units = 1:X and Y are dots per inch ;; units = 2:X and Y are dots per cm
	sp_word XDensity;          // horizontal pixel density
	sp_word YDensity;          // vertical pixel density
	sp_byte XThumbnail;        // Thumbnail horizontal pixel density
	sp_byte YThumbnail;        // Thumbnail vertical pixel density
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
