#ifndef SPECTRUM_FOUNDATION_HEADER
#define SPECTRUM_FOUNDATION_HEADER

#ifndef NAMESPACE_FOUNDATION
	#define NAMESPACE_FOUNDATION SpFoundation
#endif

#include "BasePlatform.h"

#ifdef WINDOWS
	#include "WindowsPlatform.h"
#else
	#include "LinuxPlatform.h"
#endif

#include <cassert>
#include "StackMemoryAllocator.h"
#include "PoolMemoryAllocator.h"
#include "Log.hpp"
#include "Object.h"

namespace NAMESPACE_FOUNDATION
{
	const sp_float DefaultErrorMargin = 0.0001f;

#define sp_const(Type, value) (const Type)(value)
#define sp_constless(Type, value) const_cast<const Type>(value)

	///<summary>
	///Check the number is even or not
	///</summary>
	template <typename T>
	API_INTERFACE inline sp_bool isEven(T value)
	{
		return (value % TWO_DOUBLE) == ZERO_DOUBLE;
	}
	template <>
	API_INTERFACE inline sp_bool isEven<sp_int>(sp_int value)
	{
		return !(value & ONE_INT);
	}
	template <>
	API_INTERFACE inline sp_bool isEven<size_t>(size_t value)
	{
		return !(value & ONE_INT);
	}

	///<summary>
	///Check the number is odd or not
	///</summary>
	template <typename T>
	API_INTERFACE inline sp_bool isOdd(T value)
	{
		return !isEven(value);
	}
	template <>
	API_INTERFACE inline sp_bool isOdd<sp_int>(sp_int value)
	{
		return value & ONE_INT;
	}
	template <>
	API_INTERFACE inline sp_bool isOdd<sp_size>(sp_size value)
	{
		return value & ONE_INT;
	}

	///<summary>
	///Modify a bit of a integer value, given a index bit
	///</summary>
	API_INTERFACE inline sp_int modifyBit(sp_int value, sp_int index, sp_int bit)
	{
		return (value & ~(SHIFT_BIT_ONE << index)) | ((bit << index) & (SHIFT_BIT_ONE << index));
	}

	///<summary>
	///Set a bit to ZERO of a integer value, given a index bit
	///</summary>
	API_INTERFACE inline sp_int clearBit(sp_int value, sp_int index)
	{
		return modifyBit(value, index, ZERO_INT);
	}

	///<summary>
	///Set a bit to ONE of a integer value, given a index bit
	///</summary>
	API_INTERFACE inline sp_int setBit(sp_int value, sp_int index)
	{
		return modifyBit(value, index, ONE_INT);
	}

	///<summary>
	///GFet a bit of a integer value, given a index bit
	///</summary>
	API_INTERFACE inline sp_int getBit(sp_int value, sp_int index)
	{
		return (value & (SHIFT_BIT_ONE << index)) >> index;
	}
	///<summary>
	///GFet a bit of a integer value, given a index bit
	///</summary>
	API_INTERFACE inline sp_int getBit(size_t value, sp_int index)
	{
		return (value & (SHIFT_BIT_ONE << index)) >> index;
	}

	///<summary>
	///Get the parts of float (expoent and mantissa)
	///The mantissa just returns the 4th numbers
	///</summary>
	API_INTERFACE inline sp_size floatParts(sp_float value, sp_size* expoent)
	{
		*expoent = (sp_size)value;
		return (sp_size)(std::fabsf(*expoent - value) * 10000.0f);
	}

	///<summary>
	///Get a digit of the number given by value parameter and the index
	///</summary>
	API_INTERFACE inline sp_short digit(sp_int value, sp_int index)
	{
		sp_short result = (sp_short)((sp_uint)(value / std::pow(DECIMAL_BASE, index)) % DECIMAL_BASE);

		assert(result >= ZERO_SHORT && result < TEN_SHORT);
		return result;
	}
	///<summary>
	///Get a digit of the number given by value parameter and the index
	///</summary>
	API_INTERFACE inline sp_short digit(sp_uint value, sp_uint index)
	{
		sp_short result = (sp_short)((sp_uint)(value / std::pow(DECIMAL_BASE, index)) % DECIMAL_BASE);

		assert(result >= ZERO_SHORT && result < TEN_SHORT);
		return result;
	}
	///<summary>
	///Get a digit of the number given by value parameter and the index
	///</summary>
	API_INTERFACE inline sp_short digit(sp_float value, sp_int index)
	{
		sp_short result = (sp_short)((sp_uint)(value / std::pow(DECIMAL_BASE, index)) % DECIMAL_BASE);

		assert(result >= ZERO_SHORT && result < TEN_SHORT);
		return result;
	}
	///<summary>
	///Get a digit of the number given by value parameter and the index
	///</summary>
	API_INTERFACE inline sp_short digit(sp_size value, sp_int index)
	{
		sp_short result = (sp_short)((sp_uint)(value / std::pow(DECIMAL_BASE, index)) % DECIMAL_BASE);

		assert(result >= ZERO_SHORT && result < TEN_SHORT);
		return result;
	}

	///<summary>
	///Check the numbers have the same sign
	///</summary>
	API_INTERFACE inline sp_bool sameSign(sp_int value1, sp_int value2)
	{
		return (value1 ^ value2) >= ZERO_INT;
	}

	///<summary>
	///Return -1 if value <  0
	///Return  0 if value == 0
	///Return  1 if value >  0
	///</summary>
	template <typename T>
	API_INTERFACE inline int sign(T value)
	{
		return (T(0) < value) - (value < T(0));
	}

	///<summary>
	///Check the number is power of 2
	///</summary>
	API_INTERFACE inline sp_bool isPowerOf2(sp_size value)
	{
		return value && !(value & (value - ONE_SIZE));
	}

	///<summary>
	///Get the next number power of 2
	///</summary>
	API_INTERFACE inline sp_uint nextPowOf2(sp_uint value)
	{
		sp_uint rval = 1;

		while (rval < value)
			rval = multiplyBy2(rval);

		return rval;
	}

	///<summary>
	///Get the next number power of 2
	///</summary>
	API_INTERFACE inline sp_int nextPowOf2(sp_int value)
	{
		sp_int rval = ONE_INT;

		while (rval < value)
			rval = multiplyBy2(rval);

		return rval;
	}

	API_INTERFACE inline sp_uint nextDivisorOf(sp_uint n, sp_uint startFrom)
	{
		for (sp_uint i = startFrom; i <= n; i++)
			if (n % i == 0)
				return i;

		return n;
	}


#if defined(ENV_64BITS)
	///<summary>
	///Get the next number power of 2
	///</summary>
	API_INTERFACE inline sp_size nextPowOf2(sp_size value)
	{
		sp_size rval = ONE_INT;

		while (rval < value)
			rval = rval << 1; // multiply by 2

		return rval;
	}
#endif

	///<summary>
	///Round the number given a amount of decimals
	///</summary>
	template<typename T>
	API_INTERFACE inline T round(T number, sp_int decimals)
	{
		sp_double m = (number < 0.0) ? -ONE_DOUBLE : ONE_DOUBLE; // check if input is negative
		sp_double power = pow(10, decimals);

		return T((floor(m * number * power + HALF_DOUBLE) / power) * m);
	}

	///<summary>
	///Round the number (in float) given a amount of decimals
	///</summary>
	API_INTERFACE inline sp_float roundf(sp_float number, sp_int decimals)
	{
		return round<sp_float>(number, decimals);
	}

	///<summary>
	///Round the number (in double) given a amount of decimals
	///</summary>
	API_INTERFACE inline sp_double roundd(sp_double number, sp_int decimals)
	{
		return round<sp_double>(number, decimals);
	}

	///<summary>
	///
	///</summary>
	template <typename T>
	API_INTERFACE inline T clamp(T value, T minValue, T maxValue)
	{
		if (value < minValue)
			value = minValue;
		else
			if (value > maxValue)
				value = maxValue;

		return value;
	}

	///<summary>
	///Check the number is close enough given a other number. It is used to check aproximation value and calculate the error measure.
	///Epsilon is the tolerated value
	///</summary>
	template<typename T>
	API_INTERFACE inline sp_bool isCloseEnough(T value, T compare, T epsilon)
	{
		return abs(value - compare) < epsilon;
	}

	///<summary>
	///Check the number is close enough given a other number. It is used to check aproximation value and calculate the error measure.
	///</summary>
	template<typename T>
	API_INTERFACE inline sp_bool isCloseEnough(T value, T compare)
	{
		return isCloseEnough(value, compare, T(DefaultErrorMargin));
	}

	///<summary>
	///Get the count of digits of the number given by value parameter
	///</summary>
	API_INTERFACE inline sp_uint digitCount(sp_int value)
	{
		sp_uint len = ONE_UINT;

		if (value < ZERO_INT)
			value *= -ONE_INT;

		for (len = ZERO_UINT; value > ZERO_INT; len++)
			value = value / 10;

		return len;
	}
	///<summary>
	///Get the count of digits of the number given by value parameter
	///</summary>
	API_INTERFACE inline sp_uint digitCount(sp_size value)
	{
		sp_uint len = ONE_SIZE;

		for (len = ZERO_UINT; value > ZERO_SIZE; len++)
			value = value / 10;

		return len;
	}
	///<summary>
	///Get the count of digits of the number given by value parameter
	///</summary>
	API_INTERFACE inline size_t digitMantissaCount(sp_float value)
	{
		sp_float temp;
		sp_float d = std::modff(value, &temp);
		sp_size counter = ZERO_SIZE;

		while (d > ZERO_FLOAT && !isCloseEnough(d, ZERO_FLOAT)) {
			d *= TEN_FLOAT;
			d = d - (sp_uint)d;
			counter++;
		}

		return counter;
	}
}


#endif // !SPECTRUM_FOUNDATION_HEADER