#ifndef APOLLO_HEADER
#define APOLLO_HEADER

#define SIZEOF_BOOL      (1)
#define SIZEOF_CHAR      (1)
#define SIZEOF_SHORT     (2)
#define SIZEOF_INT       (4)
#define SIZEOF_LONG      (8)
//#define SIZEOF_LONG_LONG (8)
#define SIZEOF_FLOAT     (4)
#define SIZEOF_DOUBLE    (8)
#define SIZEOF_LDOUBLE   (10)

#define SIZEOF_UCHAR     (1)
#define SIZEOF_USHORT    (2)
#define SIZEOF_UINT      (4)
#define SIZEOF_ULONG     (8)


#ifdef ENV_32BITS
	#define SHIFT_BIT 1

	typedef bool      sp_bool;
	typedef char      sp_char;
	typedef char      sp_byte;
	typedef short     sp_short;
	typedef int       sp_int;
	typedef float     sp_float;
	typedef long      sp_long;
	typedef long long sp_longlong;
	typedef double    sp_double;

	typedef unsigned char       sp_uchar;
	typedef unsigned char       sp_ubyte;
	typedef unsigned short      sp_ushort;
	typedef unsigned int        sp_uint;
	typedef unsigned long       sp_ulong;
	typedef unsigned long long  sp_ulonglong;

#elif ENV_64BITS
	#define SHIFT_BIT 1i64

	typedef char      sp_char;
	typedef char      sp_byte;
	typedef short     sp_short;
	typedef __int64   sp_int;
	typedef float     sp_float;
	typedef long      sp_long;
	typedef long long sp_longlong;
	typedef double    sp_double;

	typedef unsigned char       sp_uchar;
	typedef unsigned char       sp_ubyte;
	typedef unsigned short      sp_ushort;
	typedef unsigned __int64    sp_uint;
	typedef unsigned long       sp_ulong;
	typedef unsigned long long  sp_ulonglong;

#else
	#error "Environment not 32 or 64-bit"
#endif

#ifdef WINDOWS
	#ifdef API_IMPORT
		#define API_INTERFACE __declspec(dllimport)		
	#else
		#ifdef API_EXPORT
			#define API_INTERFACE __declspec(dllexport)
		#else
			#define API_INTERFACE
		#endif
	#endif	
#else
	#ifdef API_IMPORT
		#define API_INTERFACE __attribute__((visibility("hidden")))
	#else
		#ifdef API_EXPORT
			#define API_INTERFACE __attribute__((visibility("default")))
		#else
			#define API_INTERFACE
		#endif
	#endif	
#endif 

#define ONE_KILOBYTE SIZEOF_CHAR * 1024
#define ONE_MEGABYTE ONE_KILOBYTE * 1024
#define ONE_GIGABYTE ONE_MEGABYTE * 1024

#define PI (3.14159265358979323846)
#define TWO_PI (6.28318530717958647692)
#define HALF_PI (1.57079632679489661923)
#define PI_DIV_180 (0.017453292519943296)
#define INV_PI_DIV_180 (57.2957795130823229)
#define	PI_DIV_360 (0.008726646259971647)

#define degreesToRadians(x)	((x) * PI_DIV_180)
#define radiansToDegrees(x)	((x) * INV_PI_DIV_180)

#define hourToDegrees(x) ( x * (1.0f / 15.0f) )
#define hourToRadians(x) degreesToRadians(hourToDegrees(x))

#define degreesToHout(x) ((x) * 15.0f))
#define radiansToHour(x) degreesToHout(radiansToDegrees(x))

#define DECIMAL_BASE (10)

extern "C" {

	typedef unsigned char  BYTE;  // 1byte
	typedef unsigned short WORD;  // 2bytes
	typedef unsigned long  DWORD; // 4bytes

	const char END_OF_LINE = '\n';
	const char END_OF_STRING = '\0';
}

#include <cassert>
#include "MemoryAllocatorManager.h"
#include "Log.hpp"


#endif // !APOLLO_HEADER