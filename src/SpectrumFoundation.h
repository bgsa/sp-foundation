#ifndef SPECTRUM_FOUNDATION_HEADER
#define SPECTRUM_FOUNDATION_HEADER

#define SSE4_ENABLED
#define SSE_ENABLED
#define AVX_ENABLED

#ifdef DEBUG
	#ifndef LOG_ENABLED
		#define LOG_ENABLED
	#endif
	#ifndef SP_ASSERT_ENABLED
		#define SP_ASSERT_ENABLED
	#endif
#endif

#ifndef NAMESPACE_FOUNDATION
	#define NAMESPACE_FOUNDATION SpFoundation
#endif

#include "BasePlatform.h"

#ifdef WINDOWS
	#include "WindowsPlatform.h"
#else
	#include "LinuxPlatform.h"
#endif

#include "Assertions.h"
#include "StackMemoryAllocator.h"
#include "PoolMemoryAllocator.h"
#include "Object.h"
#include <cmath>

namespace NAMESPACE_FOUNDATION
{
	#define SP_DEFAULT_ERROR_MARGIN 0.0001f;
	const sp_float DefaultErrorMargin = SP_DEFAULT_ERROR_MARGIN;

#define sp_const(Type, value) (const Type)(value)
#define sp_constless(Type, value) const_cast<const Type>(value)

	API_INTERFACE SP_CONSTEXPR inline sp_float sp_pow2(sp_float value)
	{
		return value * value;
	}

	template <typename T>
	API_INTERFACE SP_CONSTEXPR inline T epsilon()
	{
		return std::numeric_limits<T>::epsilon();
	}

	API_INTERFACE SP_CONSTEXPR inline sp_float degreesToRadians(sp_float value)
	{
		return value * PI_DIV_180;
	}
	API_INTERFACE SP_CONSTEXPR inline sp_float degreesToRadians(sp_int value)
	{
		return value * PI_DIV_180;
	}

	API_INTERFACE SP_CONSTEXPR inline sp_float radiansToDegrees(sp_float value)
	{
		return value * INV_PI_DIV_180;
	}
	API_INTERFACE SP_CONSTEXPR inline sp_float radiansToDegrees(sp_int value)
	{
		return value * INV_PI_DIV_180;
	}

	API_INTERFACE SP_CONSTEXPR inline sp_float dxdt(sp_float x, sp_float t)
	{
		return (t - x) * 0.5f;
	}

	/*
	/// <summary>
	/// Finds value of position
	/// Given newVelocity using stepSize and initial position at initialX
	/// </summary>
	API_INTERFACE sp_float rungeKutta(sp_float velocity, sp_float position, sp_float newVelocity, sp_float stepSize)
	{
		sp_float k1, k2, k3, k4;
		constexpr sp_float oneOverSix = 1.0f / 6.0f;

		// Count number of iterations using step size or step height h 
		sp_int n = (sp_int)((newVelocity - velocity) / stepSize);

		// Iterate for number of iterations 
		for (sp_int i = 1; i <= n; i++)
		{
			// Apply Runge Kutta Formulas to find next value of position
			k1 = stepSize * dxdt(velocity, position);
			k2 = stepSize * dxdt(velocity + 0.5f*stepSize, position + 0.5f*k1);
			k3 = stepSize * dxdt(velocity + 0.5f*stepSize, position + 0.5f*k2);
			k4 = stepSize * dxdt(velocity + stepSize, position + k3);

			// Update next value of position
			position = position + oneOverSix * (k1 + 2.0f * k2 + 2.0f * k3 + k4);;

			// Update next value of x 
			velocity = velocity + stepSize;
		}

		return position;
	}
	*/

	/// <summary>
	/// Linear interpolation between v1 and v2, given t
	/// </summary>
	API_INTERFACE inline sp_float lerp(sp_float v1, sp_float v2, sp_float t)
	{
		return (ONE_FLOAT - t) * v1 + t * v2;
	}

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
	API_INTERFACE inline sp_bool isEven<sp_uint>(sp_uint value)
	{
		return !(value & ONE_UINT);
	}
#ifdef ENV_64BITS
	template <>
	API_INTERFACE inline sp_bool isEven<sp_size>(sp_size value)
	{
		return !(value & ONE_SIZE);
	}
#endif

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
		return (sp_size)(fabsf(*expoent - value) * 10000.0f);
	}

	///<summary>
	///Get a digit of the number given by value parameter and the index
	///</summary>
	API_INTERFACE inline sp_short digit(sp_int value, sp_int index)
	{
		sp_short result = (sp_short)((sp_uint)(value / std::pow(DECIMAL_BASE, index)) % DECIMAL_BASE);

		sp_assert(result >= ZERO_SHORT && result < TEN_SHORT, "IndexOutOfRange");
		return result;
	}
	///<summary>
	///Get a digit of the number given by value parameter and the index
	///</summary>
	API_INTERFACE inline sp_short digit(sp_uint value, sp_uint index)
	{
		sp_short result = (sp_short)((sp_uint)(value / std::pow(DECIMAL_BASE, index)) % DECIMAL_BASE);

		sp_assert(result >= ZERO_SHORT && result < TEN_SHORT, "IndexOutOfRange");
		return result;
	}
	///<summary>
	///Get a digit of the number given by value parameter and the index
	///</summary>
	API_INTERFACE inline sp_short digit(sp_float value, sp_int index)
	{
		sp_short result = (sp_short)((sp_uint)(value / std::pow(DECIMAL_BASE, index)) % DECIMAL_BASE);

		sp_assert(result >= ZERO_SHORT && result < TEN_SHORT, "IndexOutOfRange");
		return result;
	}
	///<summary>
	///Get a digit of the number given by value parameter and the index
	///</summary>
	API_INTERFACE inline sp_short digit(sp_size value, sp_int index)
	{
		sp_short result = (sp_short)((sp_uint)(value / std::pow(DECIMAL_BASE, index)) % DECIMAL_BASE);

		sp_assert(result >= ZERO_SHORT && result < TEN_SHORT, "IndexOutOfRange");
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
	API_INTERFACE inline sp_int sign(sp_float value)
	{
		return (ZERO_FLOAT < value) - (value < ZERO_FLOAT);
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
	API_INTERFACE inline sp_int nextPowOf2(sp_int value)
	{
		sp_int rval = ONE_INT;

		while (rval < value)
			rval = multiplyBy2(rval);

		return rval;
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

	API_INTERFACE inline sp_uint nextDivisorOf(sp_uint n, sp_uint startFrom)
	{
		for (sp_uint i = startFrom; i <= n; i++)
			if (n % i == 0)
				return i;

		return n;
	}

	API_INTERFACE inline sp_uint nextDivisorOf_(sp_uint value, sp_uint of)
	{
		return of - (value % of);
	}

	///<summary>
	///Round the number given a amount of decimals
	///</summary>
	template<typename T>
	API_INTERFACE inline T round(T number, sp_int decimals)
	{
		sp_double m = (number < 0.0) ? -ONE_DOUBLE : ONE_DOUBLE; // check if input is negative
		sp_double power = std::pow(10, decimals);

		return T((std::floor(m * number * power + HALF_DOUBLE) / power) * m);
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
		sp_float d = modff(value, &temp);
		sp_size counter = ZERO_SIZE;

		while (d > ZERO_FLOAT && !isCloseEnough(d, ZERO_FLOAT)) {
			d *= TEN_FLOAT;
			d = d - (sp_uint)d;
			counter++;
		}

		return counter;
	}

	API_INTERFACE inline sp_int gcd(sp_int a, sp_int b)
	{
		while(true)
		{
			if (a == 0) 
				return b;

			b %= a;

			if (b == 0) 
				return a;

			a %= b;
		}
	}

	///<summary>
	/// Least Commom Multiple (MMC)
	///</summary>
	API_INTERFACE inline sp_int lcm(sp_int a, sp_int b)
	{
		sp_int temp = gcd(a, b);

		return temp ? (a / temp * b) : 0;
	}

	/// <summary>
	/// Clamp "value" parameter to lie within the range [min, max]
	/// </summary>
	/// <param name="value">Value to be clamped</param>
	/// <param name="min">Minimium value</param>
	/// <param name="max">Maximum value</param>
	/// <returns>Valule clamped</returns>
	API_INTERFACE inline sp_float clamp(const sp_float value, const sp_float min, const sp_float max)
	{  
		if (value < min)
			return min;

		if (value > max)
			return max;  
		
		return value;  
	} 

}


#endif // !SPECTRUM_FOUNDATION_HEADER
