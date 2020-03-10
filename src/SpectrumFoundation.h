#ifndef SPECTRUM_FOUNDATION_HEADER
#define SPECTRUM_FOUNDATION_HEADER

#define SIZEOF_BOOL      (1)
#define SIZEOF_CHAR      (1)
#define SIZEOF_SHORT     (2)
#define SIZEOF_INT       (4)
#define SIZEOF_LONG      (8)
#define SIZEOF_SIZE      (8)
#define SIZEOF_LONG_LONG (8)
#define SIZEOF_FLOAT     (4)
#define SIZEOF_DOUBLE    (8)
#define SIZEOF_LDOUBLE   (10)

#define SIZEOF_UCHAR     (1)
#define SIZEOF_USHORT    (2)
#define SIZEOF_UINT      (4)
#define SIZEOF_ULONG     (8)
#define SIZEOF_ULONGLONG (8)

#define SP_SHORT_MAX        SHRT_MAX
#define SP_USHORT_MAX       USHRT_MAX
#define SP_INT_MAX          INT_MAX
#define SP_UINT_MAX         UINT_MAX
#define SP_SIZE_MAX         UINTMAX_MAX
#define SP_FLOAT_MAX        FLT_MAX
#define SP_DOUBLE_MAX       DBL_MAX

#define SP_FLOAT_MIN        (-FLT_MAX)
#define SP_SHORT_MIN        (-SHRT_MAX)
#define SP_USHORT_MIN       (-USHRT_MAX)
#define SP_INT_MIN          (-INT_MAX)
#define SP_UINT_MIN         (-UINT_MAX)
#define SP_SIZE_MIN         (-UINTMAX_MAX)
#define SP_FLOAT_MIN        (-FLT_MAX)
#define SP_DOUBLE_MIN       (-DBL_MAX)

#define SP_HUGE_VALUE_FLOAT ((sp_float) 1e50)
#define SP_INFINITY         SP_HUGE_VALUE_FLOAT

#if defined(WINDOWS)

	typedef bool   sp_bool;
	typedef char   sp_char;
	typedef float  sp_float;
	typedef double sp_double;
	
	typedef signed __int8    sp_int8;
	typedef signed __int16   sp_short;
	typedef signed __int16   sp_int16;
	typedef signed __int32   sp_int;
	typedef signed __int32   sp_int32;
	typedef signed __int64   sp_long;
	typedef signed __int64   sp_int64;
	typedef signed long long sp_longlong;

	typedef unsigned __int8     sp_uint8;
	typedef unsigned __int8     sp_byte;
	typedef unsigned __int8     sp_uchar;
	typedef unsigned __int16    sp_uint16;
	typedef unsigned __int16    sp_ushort;
	typedef unsigned __int16    sp_half;
	typedef unsigned __int32    sp_uint32;
	typedef unsigned __int32    sp_uint;
	typedef unsigned __int64    sp_uint64;
	typedef unsigned __int64    sp_ulong;
	typedef unsigned __int64    sp_size;
	typedef unsigned long long  sp_long_size;

	#define ONE_SHORT  (1i16)
	#define ONE_USHORT (1ui16)
	#define ONE_INT    (1i32)
	#define ONE_UINT   (1ui32)
	#define ONE_LONG   (1i64)
	#define ONE_ULONG  (1ui64)
	#define ONE_SIZE   (1ui64)
	#define ONE_FLOAT  (1.0f)
	#define ONE_DOUBLE (1.0)
	
	#define SP_NOT_A_NUMBER     (CL_INFINITY - CL_INFINITY)

#else

	#include <stdint.h>
	#include <cfloat>

	typedef bool   sp_bool;
	typedef char   sp_char;
	typedef float  sp_float  __attribute__((aligned(SIZEOF_FLOAT)));
	typedef double sp_double __attribute__((aligned(SIZEOF_DOUBLE)));

	typedef int8_t    sp_int8;
	typedef int16_t   sp_int16     __attribute__((aligned(SIZEOF_SHORT)));
	typedef int16_t   sp_short     __attribute__((aligned(SIZEOF_SHORT)));
	typedef int32_t   sp_int32     __attribute__((aligned(SIZEOF_INT)));
	typedef int32_t   sp_int       __attribute__((aligned(SIZEOF_INT)));
	typedef int64_t   sp_int64     __attribute__((aligned(SIZEOF_LONG)));
	typedef int64_t   sp_long      __attribute__((aligned(SIZEOF_LONG)));
	typedef long long sp_longlong  __attribute__((aligned(SIZEOF_LONG_LONG)));

	typedef uint8_t        sp_uint8;
	typedef uint8_t        sp_byte;
	typedef uint8_t        sp_uchar;
	typedef uint16_t       sp_uint16     __attribute__((aligned(SIZEOF_SHORT)));;
	typedef uint16_t       sp_ushort     __attribute__((aligned(SIZEOF_SHORT)));;
	typedef uint16_t       sp_half       __attribute__((aligned(SIZEOF_SHORT)));
	typedef uint32_t       sp_uint32     __attribute__((aligned(SIZEOF_INT)));
	typedef uint32_t       sp_uint       __attribute__((aligned(SIZEOF_INT)));
	typedef uint64_t       sp_uint64     __attribute__((aligned(SIZEOF_LONG)));
	typedef uint64_t       sp_ulong      __attribute__((aligned(SIZEOF_LONG)));
	typedef uint64_t       sp_size       __attribute__((aligned(SIZEOF_LONG)));
	typedef uint_least64_t sp_long_size  __attribute__((aligned(SIZEOF_LONG_LONG)));

	#define ONE_SHORT  ((sp_short)  1)
	#define ONE_USHORT ((sp_ushort) 1)
	#define ONE_INT    (1)
	#define ONE_UINT   (1U)
	#define ONE_LONG   (1L)
	#define ONE_ULONG  (1UL)
	#define ONE_SIZE   (1UL)
	#define ONE_FLOAT  (1.0f)
	#define ONE_DOUBLE (1.0)

	#if defined( __GNUC__ )
		#define SP_NOT_A_NUMBER   __builtin_nanf( "" )
		#define FLT_MAX           __FLT_MAX__
		#define FLT_MIN           __FLT_MIN__
	#else
		float nanf(const char *);
		#define SP_NOT_A_NUMBER   nanf( "" )  
	#endif

#endif

#if defined(ENV_32BITS)
	#define SHIFT_BIT_ONE   1
	#define SHIFT_BIT_TWO   2
	#define SHIFT_BIT_THREE 3
	#define SHIFT_BIT_FOUR  4
#elif defined(ENV_64BITS)
	#ifdef WINDOWS
		#define SHIFT_BIT_ONE   1i64
		#define SHIFT_BIT_TWO   2i64
		#define SHIFT_BIT_THREE 3i64
		#define SHIFT_BIT_FOUR  4i64
	#else
		#define SHIFT_BIT_ONE   1L
		#define SHIFT_BIT_TWO   2L
		#define SHIFT_BIT_THREE 3L
		#define SHIFT_BIT_FOUR  4L
	#endif // WINDOWS
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

#define divideBy(value, bit) (value >> bit)
#define divideBy2(value) divideBy(value, SHIFT_BIT_ONE)
#define divideBy4(value) (value >> SHIFT_BIT_TWO)
#define divideBy8(value) (value >> SHIFT_BIT_THREE)
#define divideBy16(value) (value >> SHIFT_BIT_FOUR)

#define multiplyBy(value, bit) (value << bit)
#define multiplyBy2(value) multiplyBy(value, SHIFT_BIT_ONE)
#define multiplyBy4(value) multiplyBy(value, SHIFT_BIT_TWO)
#define multiplyBy8(value) multiplyBy(value, SHIFT_BIT_THREE)
#define multiplyBy10(value) ((value << SHIFT_BIT_THREE) + (value << SHIFT_BIT_ONE));
#define multiplyBy16(value) multiplyBy(value, SHIFT_BIT_FOUR)

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


#endif // !SPECTRUM_FOUNDATION_HEADER