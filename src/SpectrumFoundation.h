#ifndef SPECTRUM_FOUNDATION_HEADER
#define SPECTRUM_FOUNDATION_HEADER

#ifndef NAMESPACE_FOUNDATION
	#define NAMESPACE_FOUNDATION SpFoundation
#endif

#define SIZEOF_BOOL      (1)
#define SIZEOF_CHAR      (1)
#define SIZEOF_SHORT     (2)
#define SIZEOF_INT       (4)
#define SIZEOF_LONG      (8)
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
#define SP_FLOAT_MAX        FLT_MAX
#define SP_DOUBLE_MAX       DBL_MAX

#define SP_FLOAT_MIN        (-FLT_MAX)
#define SP_SHORT_MIN        (-SHRT_MAX)
#define SP_USHORT_MIN       (-USHRT_MAX)
#define SP_INT_MIN          (-INT_MAX)
#define SP_UINT_MIN         (-UINT_MAX)
#define SP_FLOAT_MIN        (-FLT_MAX)
#define SP_DOUBLE_MIN       (-DBL_MAX)

#ifdef ENV_32BITS
	#define SIZEOF_SIZE      (4)
	#define SP_SIZE_MAX      UINT32_MAX
	#define SP_SIZE_MIN      (-SP_SIZE_MAX)
#else
	#define SIZEOF_SIZE      (8)
	#define SP_SIZE_MAX      UINT64_MAX
	#define SP_SIZE_MIN      (-SP_SIZE_MAX)
#endif

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
	typedef unsigned long long  sp_long_size;

	#ifdef ENV_32BITS
		typedef unsigned int     sp_size;
	//	typedef int              ptrdiff_t;
	//	typedef int              intptr_t;
	#else
		typedef unsigned __int64 sp_size;
	//	typedef __int64          ptrdiff_t;
	//	typedef __int64          intptr_t;
	#endif

	#define ZERO_SHORT   0i16
	#define ONE_SHORT    1i16
	#define TWO_SHORT    2i16
	#define THREE_SHORT  3i16
	#define FOUR_SHORT   4i16
	#define TEN_SHORT   10i16

	#define ZERO_USHORT   0ui16
	#define ONE_USHORT    1ui16
	#define TWO_USHORT    2ui16
	#define THREE_USHORT  3ui16
	#define FOUR_USHORT   4ui16
	#define TEN_USHORT   10ui16

	#define ZERO_INT   0i32
	#define ONE_INT    1i32
	#define TWO_INT    2i32
	#define THREE_INT  3i32
	#define FOUR_INT   4i32
	#define TEN_INT   10i32

	#define ZERO_UINT   0ui32
	#define ONE_UINT    1ui32
	#define TWO_UINT    2ui32
	#define THREE_UINT  3ui32
	#define FOUR_UINT   4ui32
	#define TEN_UINT   10ui32

	#define ZERO_LONG   0i64
	#define ONE_LONG    1i64
	#define TWO_LONG    2i64
	#define TRHEE_LONG  3i64
	#define FOUR_LONG   4i64
	#define TEN_LONG   10i64

	#define ZERO_ULONG   0ui64
	#define ONE_ULONG    1ui64
	#define TWO_ULONG    2ui64
	#define THREE_ULONG  3ui64
	#define FOUR_ULONG   4ui64
	#define TEN_ULONG   10ui64

	#define ZERO_SIZE   0ui64
	#define ONE_SIZE    1ui64
	#define TWO_SIZE    2ui64
	#define THREE_SIZE  3ui64
	#define FOUR_SIZE   4ui64
	#define TEN_SIZE   10ui64

	#define ZERO_FLOAT  0.0f
	#define ONE_FLOAT   1.0f
	#define TWO_FLOAT   2.0f
	#define THREE_FLOAT 3.0f
	#define FOUT_FLOAT  4.0f
	#define TEN_FLOAT  10.0f

	#define ZERO_DOUBLE  0.0
	#define ONE_DOUBLE   1.0
	#define TWO_DOUBLE   2.0
	#define THREE_DOUBLE 3.0
	#define FOUR_DOUBLE  4.0
	#define TEN_DOUBLE  10.0
	
	#define SP_NOT_A_NUMBER     (INFINITY - INFINITY)

#else

	#include <stdint.h>
	#include <cfloat>

	#define ZERO_INT  0
	#define ONE_INT   1
	#define TWO_INT   2
	#define THREE_INT 3
	#define FOUR_INT  4
	#define TEN_INT  10

	#define ZERO_LONG   0L
	#define ONE_LONG    1L
	#define TWO_LONG    2L
	#define THREE_LONG  3L
	#define FOUR_LONG   4L
	#define TEN_LONG   10L

	#define ZERO_UINT  0u
	#define ONE_UINT   1u
	#define TWO_UINT   2u
	#define THREE_UINT 3u
	#define FOUR_UINT  4u
	#define TEN_UINT  10u

	#define ZERO_ULONG   0UL
	#define ONE_ULONG    1UL
	#define TWO_ULONG    2UL
	#define THREE_ULONG  3UL
	#define FOUR_ULONG   4UL
	#define TEN_ULONG   10UL

	#define ZERO_SIZE  0UL
	#define ONE_SIZE   1UL
	#define TWO_SIZE   2UL
	#define THREE_SIZE 3UL
	#define FOUR_SIZE  4UL
	#define TEN_SIZE  10UL

	#define ZERO_FLOAT  0.0f
	#define ONE_FLOAT   1.0f
	#define TWO_FLOAT   2.0f
	#define THREE_FLOAT 3.0f
	#define FOUT_FLOAT  4.0f
	#define TEN_FLOAT  10.0f

	#define ZERO_DOUBLE  0.0d
	#define ONE_DOUBLE   1.0d
	#define TWO_DOUBLE   2.0d
	#define THREE_DOUBLE 3.0d
	#define FOUR_DOUBLE  4.0d
	#define TEN_DOUBLE  10.0d

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
#define multiplyBy10(value) ((value << SHIFT_BIT_THREE) + (value << SHIFT_BIT_ONE))
#define multiplyBy16(value) multiplyBy(value, SHIFT_BIT_FOUR)
#define multiplyBy5(value) divideBy2(multiplyBy10(value, SHIFT_BIT_TWO))

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