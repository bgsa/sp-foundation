#ifndef SP_FOUNDATION_TEST_HEADER
#define SP_FOUNDATION_TEST_HEADER

#include "SpectrumFoundation.h"
#include "SpPerformanceCounter.h"
#include "SpLogger.h"
#include "SpLogMsTestProvider.h"
#include <mutex>

#ifndef NAMESPACE_FOUNDATION_TEST
	#define NAMESPACE_FOUNDATION_TEST SpFoundationTest
#endif

using namespace NAMESPACE_FOUNDATION;

#ifdef GOOGLETEST_ENABLED
	#include "gtest/gtest.h"

	#define SP_TEST_CLASS(className)                  class className : public ::testing::Test
	#define SP_TEST_METHOD(className, methodMame)     TEST_F(className, methodMame)
	#define SP_TEST_METHOD_DEF(methodMame)

	#define LINE_INFO() __FILE__ , __FUNCTION__, __LINE__

	namespace NAMESPACE_PHYSICS_TEST
	{
		class Assert
		{
		public:

			static void AreEqual(size_t value1, size_t value2, const wchar_t* message, const char* filename, const char* functionName, const int line)
			{

			}
			static void AreEqual(int value1, int value2, const wchar_t* message, const char* filename, const char* functionName, const int line)
			{

			}
			static void AreEqual(float value1, float value2, const wchar_t* message, const char* filename, const char* functionName, const int line)
			{

			}
			static void AreEqual(double value1, double value2, const wchar_t* message, const char* filename, const char* functionName, const int line)
			{

			}
			static void AreEqual(std::string value1, std::string value2, const wchar_t* message, const char* filename, const char* functionName, const int line)
			{

			}
			static void AreEqual(const Vec2& value1, const Vec2& value2, const wchar_t* message, const char* filename, const char* functionName, const int line)
			{

			}
			static void AreEqual(const Vec3& value1, const Vec3& value2, const wchar_t* message, const char* filename, const char* functionName, const int line)
			{

			}
			static void AreEqual(const CollisionStatus& value1, const CollisionStatus& value2, const wchar_t* message, const char* filename, const char* functionName, const int line)
			{

			}

			static void IsTrue(bool value, const wchar_t* message, const char* filename, const char* functionName, const int line)
			{

			}
			static void IsFalse(bool value, const wchar_t* message, const char* filename, const char* functionName, const int line)
			{

			}

			static void IsNull(void* value, const wchar_t* message, const char* filename, const char* functionName, const int line)
			{

			}
			static void IsNotNull(void* value, const wchar_t* message, const char* filename, const char* functionName, const int line)
			{

			}
			static void Fail(const wchar_t* message, const char* filename, const char* functionName, const int line)
			{

			}
		};
	}

#endif

#ifdef MSTEST_ENABLED
	#include "CppUnitTest.h"
	#define SP_TEST_CLASS(className)              TEST_CLASS(className)
	#define SP_TEST_METHOD(className, methodMame) void className::methodMame()
	#define SP_TEST_METHOD_DEF(methodName)            TEST_METHOD(methodName)
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#endif // MSTEST_ENABLED

namespace NAMESPACE_FOUNDATION_TEST
{
	class TestFoundation
	{
	public:
		API_INTERFACE inline static void lock();
		API_INTERFACE inline static void unlock();
	};

	API_INTERFACE void resetMemory();
	API_INTERFACE void setupModule();
	API_INTERFACE void tearDownModule();
}

#endif // SP_FOUNDATION_TEST_HEADER
