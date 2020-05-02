#ifndef BASE_PLATFORM_HEADER
#define BASE_PLATFORM_HEADER

#define HEAP_PROFILING_ALLOC
#define DEPRECATED

#if defined (_MSC_VER)
	#define MSVC_COMPILER
	#define COMPILER_VERSION _MSC_FULL_VER
	#define UNINITIALIZED_HEAP_ADDRESS 0xcdcdcdcd

	#if defined(_M_X64) || defined(_M_AMD64)
		#define ENV_64BITS
	#else
		#define ENV_32BITS
	#endif

	#if defined(_M_ARM) || defined(_M_ARM_ARMV7VE) || defined(_M_ARM_FP) || defined(_M_ARM64)
		#define ARM_PROCESSOR
	#elif defined(_M_IX86) || defined(_M_IA64)
		#define INTEL_PROCESSOR
	#endif

	#if defined(DEBUG)
		//#define _CRTDBG_MAP_ALLOC
		//#undef free

		#undef HEAP_PROFILING_ALLOC
		#define HEAP_PROFILING_ALLOC __declspec(allocator)
	#endif

	#undef  DEPRECATED
	#define DEPRECATED __declspec(deprecated)

	//	Type Traits compile definitions
	#define isPrimitive(Type) !(__is_class(Type))
	#define isClass(Type) __is_class(Type)
	#define isAbstractClass(Type) __is_abstract(Type)
	#define isEnum(Type) __is_enum(Type)
	#define isConvertibleTo(from,to) __is_convertible_to(from, to)
	#define isDerivedOf(Base,Derived) __is_base_of(Base, Derived)

#elif defined (__GNUC__)
	#define GCC_COMPILER
	#define COMPILER_VERSION __GNUC___.__GNUC_MINOR__
	#define UNINITIALIZED_HEAP_ADDRESS 0x00000000

	#undef  DEPRECATED
	#define DEPRECATED __attribute__((deprecated))

	#if defined(__x86_64__)
		#define ENV_64BITS

		#if defined(__ia64__) || defined(_IA64) || defined(__IA64__)
			#define INTEL_PROCESSOR
		#endif
	#else
		#define ENV_32BITS

		#if defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__)
			#define INTEL_PROCESSOR
		#endif
	#endif

	//	Type Traits compile definitions
	#define isPrimitive(Type) !(__is_class(Type))
	#define isClass(Type) __is_class(Type)
	#define isAbstractClass(Type) __is_abstract(Type)
	#define isEnum(Type) __is_enum(Type)
	#define isConvertibleTo(from,to) __is_convertible_to(from, to)
	#define isDerivedOf(Base,Derived) __is_base_of(Base, Derived)

#elif defined (__clang__)
	#define CLANG_COMPILER
	#define COMPILER_VERSION __clang_major__.__clang_minor__.__clang_patchlevel__
	#define UNINITIALIZED_HEAP_ADDRESS 0x00000000

	#undef  DEPRECATED
	#define DEPRECATED __attribute__((deprecated))

	#if defined(__x86_64__)
		#define ENV_64BITS
	#else
		#define ENV_32BITS
	#endif

	#if defined(__has_extension(attribute_deprecated_with_message))
		#undef  DEPRECATED
		#define DEPRECATED __attribute__((deprecated("Deprecated!")))
	#endif

//__has_feature(cxx_constexpr)
//__has_feature(cxx_exceptions)
//__has_feature(cxx_rtti)

	//	Type Traits compile definitions
	#define isPrimitive(Type) !(__is_class(Type))
	#define isClass(Type) __is_class(Type)
	#define isAbstractClass(Type) __is_abstract(Type)
	#define isEnum(Type) __is_enum(Type)
	#define isConvertibleTo(from,to) __is_convertible_to(from, to)
	#define isDerivedOf(Base,Derived) __is_base_of(Base, Derived)

#elif defined (__MINGW32__)
	#define MINGW32_COMPILER
	#define COMPILER_VERSION __MINGW32_MAJOR_VERSION.__MINGW32_MINOR_VERSION

	#if defined(_X86_)
		#define INTEL_PROCESOR
	#endif

#elif defined (__MINGW64__)
	#define MINGW64_COMPILER
	#define COMPILER_VERSION __MINGW64_VERSION_MAJOR.__MINGW64_VERSION_MINOR

#elif defined(__wasm__)
	#define WASM_COMPILER
	#define COMPILER_VERSION 0

#elif defined(__CC_ARM)
	#define ARM_COMPILER
	#define COMPILER_VERSION __ARMCC_VERSION

#elif defined(__INTEL_COMPILER)
	#define INTEL_COMPILER
	#define COMPILER_VERSION __INTEL_COMPILER

	#undef  DEPRECATED
	#define DEPRECATED [[deprecated]]
#endif

#if defined(__CUDACC__)
	#define CUDA_ENABLED
//CUDA_VERSION
#endif



// Define the Operating System
#if defined (_WIN32) || defined (_WIN64)
	#define WINDOWS
#elif defined (__linux__ && !__ANDROID__)
	#define LINUX
#elif defined (__ANDROID__)
	#define ANDROID
	//__ANDROID_API__
#elif defined (__APPLE__) // MacOS ou iOS
	#define OSX
#endif

/* Define Processor Architecture
__i386__
__x86_64__
__arm__. If defined, you can further check:
	__ARM_ARCH_5T__
	__ARM_ARCH_7A__
	__powerpc64__
	__aarch64__
*/


/* Define the C++ libraries
__GLIBCXX__	       libstdc++
__GLIBCPP__
__INTEL_CXXLIB_ICC


_LIBCPP_VERSION	   libc++
_MSC_VER	       MSVC

__GLIBC__	       GNU glibc
<features.h>
__GNU_LIBRARY__

__BIONIC__	       Bionic libc
<sys/types.h>

__INTEL_CXXLIB_ICC
*/


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

#define SIZEOF_WORD              (4)
#define SIZEOF_TWO_WORDS         (8)
#define SIZEOF_WORD_DIVISOR_BIT  (2)

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

#define EULER_NUMBER (2.71828f)   // e^1 = 2.71828
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

#define MAX_DIGITS_EXPOENT  (5)
#define MAX_DIGITS_MANTISSA (4)

#define divideBy(value, bit) (value >> bit)
#define divideBy2(value) divideBy(value, SHIFT_BIT_ONE)
#define divideBy4(value) (value >> SHIFT_BIT_TWO)
#define divideBy8(value) (value >> SHIFT_BIT_THREE)
#define divideBy16(value) (value >> SHIFT_BIT_FOUR)

#define multiplyBy(value, bit) (value << bit)
#define multiplyBy2(value) multiplyBy(value, SHIFT_BIT_ONE)
#define multiplyBy3(value) (multiplyBy2(value) + value)
#define multiplyBy4(value) multiplyBy(value, SHIFT_BIT_TWO)
#define multiplyBy5(value) (multiplyBy4(value) + value)
#define multiplyBy6(value) (multiplyBy4(value) + multiplyBy2(value))
#define multiplyBy8(value) multiplyBy(value, SHIFT_BIT_THREE)
#define multiplyBy9(value) (multiplyBy8(value) + value)
#define multiplyBy10(value) (multiplyBy8(value) + multiplyBy2(value))
#define multiplyBy16(value) multiplyBy(value, SHIFT_BIT_FOUR)

#define sp_ceilBit(value, divisor, bit)   \
	((value % divisor == ZERO_DOUBLE) ?   \
		divideBy(value, bit)              \
	:                                     \
		divideBy(value, bit) + 1)


extern "C" {
	typedef unsigned char  sp_byte;  // 1byte
	typedef unsigned short sp_word;  // 2bytes
	typedef unsigned long  sp_dword; // 4bytes

	const char END_OF_LINE = '\n';
	const char END_OF_STRING = '\0';
}

#endif // BASE_PLATFORM_HEADER