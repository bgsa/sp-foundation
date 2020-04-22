#ifndef BASE_PLATFORM_HEADER
#define BASE_PLATFORM_HEADER

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

#define sp_ceilBit(value, divisor, bit)   \
	((value % divisor != 0.0) ?           \
		divideBy(value, bit) + 1          \
	:                                     \
		divideBy(value, bit))


extern "C" {

	typedef unsigned char  BYTE;  // 1byte
	typedef unsigned short WORD;  // 2bytes
	typedef unsigned long  DWORD; // 4bytes

	const char END_OF_LINE = '\n';
	const char END_OF_STRING = '\0';
}

#endif // BASE_PLATFORM_HEADER