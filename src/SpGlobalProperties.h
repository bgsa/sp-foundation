#ifndef SP_GLOBAL_PROPERTIES_HEADER
#define SP_GLOBAL_PROPERTIES_HEADER

#include "SpectrumFoundation.h"
#include "SpMap.h"

namespace NAMESPACE_FOUNDATION
{
	/// <summary>
	/// Define global system properties
	/// </summary>
	class SpGlobalProperties
	{
	private:
		SpMap<sp_uint, void*> map;
		sp_uint length;

	public:
		
		/// <summary>
		/// Default constructor
		/// </summary>
		/// <returns></returns>
		API_INTERFACE SpGlobalProperties()
		{
			length = ZERO_UINT;
		}

		/// <summary>
		/// Initialize the global system properties
		/// </summary>
		/// <returns></returns>
		API_INTERFACE static void init();

		/// <summary>
		/// Dispose all allocated resources
		/// </summary>
		/// <returns></returns>
		API_INTERFACE static void dispose();
		
		/// <summary>
		/// Add new value to global properties
		/// </summary>
		/// <param name="value">New Value</param>
		/// <returns>Index</returns>
		API_INTERFACE inline sp_uint add(void* value)
		{
			map.add(SpPair<sp_uint, void*>(length++, value));
			return length;
		}

		/// <summary>
		/// Remove the value from global properties
		/// </summary>
		/// <param name="index">Index of the element</param>
		/// <returns></returns>
		API_INTERFACE inline void remove(const sp_uint index)
		{
			map.remove(index);
		}

		/// <summary>
		/// Get a global properties by index
		/// </summary>
		/// <param name="index">Index</param>
		/// <returns>Global Property</returns>
		API_INTERFACE inline void* get(const sp_uint index) const
		{
			return map.find(index);
		}

	};

	extern SpGlobalProperties* SpGlobalPropertiesInscance;

	// TODO: REMOVE
#define ID_buildDOP18Time 0
#define ID_paresDOP18 1
#define ID_sapDOP18Time 2
#define ID_buildElementsDOP18Time 3

#define ID_buildAABBTime 4
#define ID_paresAABB 5
#define ID_sapAABBTime 6
#define ID_buildElementsAABBTime 7

#define ID_buildSphereTime 8
#define ID_paresSphere 9
#define ID_sapSphereTime 10
#define ID_buildElementsSphereTime 11

#define ID_radixSortingTime 12
#define ID_gjkEpaCount 13
#define ID_gjkEpaTime 14
#define ID_shapeMatchingTime 15

#define ID_pcaTime 16
#define ID_qtdAlteracoesPCA 17
#define ID_eixoPCA 18

#define ID_renderingTime 19
}

#endif // SP_GLOBAL_PROPERTIES_HEADER