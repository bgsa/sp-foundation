#include "SpApplicationArguments.h"

namespace NAMESPACE_FOUNDATION
{

	SpApplicationArguments* SpApplicationArgumentsInstace = nullptr;

	void SpApplicationArguments::init(sp_int parametersLength, sp_char** parameters)
	{
		if (SpApplicationArgumentsInstace == nullptr)
		{
			SpApplicationArgumentsInstace = sp_mem_new(SpApplicationArguments);

			SpApplicationArgumentsInstace->_parameters = sp_mem_new(SpArray<sp_char*>)(parametersLength);

			for (sp_uint i = 0; i < parametersLength; i++)
				SpApplicationArgumentsInstace->_parameters->add(parameters[i]);
		}
	}

	void SpApplicationArguments::dispose()
	{
		if (SpApplicationArgumentsInstace != nullptr)
		{
			sp_mem_delete(SpApplicationArgumentsInstace, SpApplicationArguments);
		}

		SpApplicationArgumentsInstace = nullptr;
	}

}