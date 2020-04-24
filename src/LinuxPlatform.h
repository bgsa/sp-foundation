#ifdef LINUX

#ifndef LINUX_PLATFORM_HEADER
#define LINUX_PLATFORM_HEADER

#include "BasePlatform.h"

#ifdef API_IMPORT
	#define API_INTERFACE __attribute__((visibility("hidden")))
#else
	#ifdef API_EXPORT
		#define API_INTERFACE __attribute__((visibility("default")))
	#else
		#define API_INTERFACE
	#endif
#endif	

#if defined(ENV_32BITS)
	#define SHIFT_BIT_ONE   1
	#define SHIFT_BIT_TWO   2
	#define SHIFT_BIT_THREE 3
	#define SHIFT_BIT_FOUR  4
#elif defined(ENV_64BITS)
	#define SHIFT_BIT_ONE   1L
	#define SHIFT_BIT_TWO   2L
	#define SHIFT_BIT_THREE 3L
	#define SHIFT_BIT_FOUR  4L
#else
	#error "Environment not 32 or 64-bit"
#endif

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
#define HALF_FLOAT  0.5f
#define ONE_FLOAT   1.0f
#define TWO_FLOAT   2.0f
#define THREE_FLOAT 3.0f
#define FOUT_FLOAT  4.0f
#define TEN_FLOAT  10.0f

#define ZERO_DOUBLE  0.0
#define HALF_DOUBLE  0.5
#define ONE_DOUBLE   1.0
#define TWO_DOUBLE   2.0
#define THREE_DOUBLE 3.0
#define FOUR_DOUBLE  4.0
#define TEN_DOUBLE  10.0

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

#endif // LINUX_PLATFORM_HEADER

#endif // LINUX