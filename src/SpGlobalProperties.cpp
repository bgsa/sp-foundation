#include "SpGlobalProperties.h"

namespace NAMESPACE_FOUNDATION
{
	SpGlobalProperties* SpGlobalPropertiesInscance = nullptr;

	void SpGlobalProperties::init()
	{
		sp_assert(SpGlobalPropertiesInscance == nullptr, "InvalidOperationException");

		SpGlobalPropertiesInscance = sp_mem_new(SpGlobalProperties);
	}

	void SpGlobalProperties::dispose()
	{
		if (SpGlobalPropertiesInscance != nullptr)
		{
			sp_mem_delete(SpGlobalPropertiesInscance, SpGlobalProperties);
			SpGlobalPropertiesInscance = nullptr;
		}
	}
}