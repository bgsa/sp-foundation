#ifndef SP_APPLICATION_ARGUMENTS_HEADER
#define SP_APPLICATION_ARGUMENTS_HEADER

#include "SpectrumFoundation.h"
#include "SpArray.h"

namespace NAMESPACE_FOUNDATION
{
	class SpApplicationArguments
	{
	private:
		SpArray<sp_char*>* _parameters;

	public:

		/// <summary>
		/// Get an Application Argument
		/// </summary>
		/// <param name="index">Parameter Index</param>
		/// <returns>Parameter Value</returns>
		API_INTERFACE sp_char* get(const sp_int index) const
		{
			return _parameters->get(index);
		}

		/// <summary>
		/// Initialize ApplicationArguments
		/// </summary>
		/// <param name="parametersLength">Parameters Length</param>
		/// <param name="parameters">Parameters</param>
		/// <returns>void</returns>
		API_INTERFACE static void init(sp_int parametersLength, sp_char** parameters);

		/// <summary>
		/// Dispose allocated resources in ApplicationArguments
		/// </summary>
		/// <returns></returns>
		API_INTERFACE static void dispose();

		~SpApplicationArguments()
		{
			if (_parameters != nullptr)
			{
				sp_mem_delete(_parameters, SpArray<sp_char*>);
				_parameters = nullptr;
			}
		}

	};

	extern SpApplicationArguments* SpApplicationArgumentsInstace;
}

#endif // SP_APPLICATION_ARGUMENTS_HEADER