#include "PoolMemoryAllocator.h"

#ifdef WINDOWS
	#include <windows.h>
#elif UNIX

	#include <stdio.h>
	#include <sys/types.h>
	#include <sys/sysctl.h>
	#include <sys/vmmeter.h>
	/*
	//#include <sys/limits.h>
	//#include <vm/vm_param.h>

	struct vmtotal getVMinfo() {
		struct vmtotal vm_info;
		int mib[2];

		mib[0] = CTL_VM;
		mib[1] = VM_TOTAL;

		size_t len = sizeof(vm_info);
		sysctl(mib, 2, &vm_info, &len, NULL, 0);

		return vm_info;
	}

	int getSysCtl(int top_level, int next_level) {
		int mib[2], ctlvalue;
		size_t len;

		mib[0] = top_level;
		mib[1] = next_level;
		len = sizeof(ctlvalue);

		sysctl(mib, 2, &ctlvalue, &len, NULL, 0);

		return ctlvalue;
	}
	*/
#endif

static PoolMemoryBlock* pmaMemoryMap = NULL;
static sp_size pmaMemoryMapLength = ZERO_SIZE;
static sp_size pmaMemoryMapSize = ZERO_SIZE;

static sp_size pmaInitialPointer = NULL;
static std::atomic_size_t pmaCurrentPointer;
static sp_size pmaLastPointer = NULL;

static std::stack<void*> freedMemory;

void allocMemoryMap(sp_size initialSize)
{
	pmaMemoryMapLength = initialSize / DEFAULT_BLOCK_SIZE;
	pmaMemoryMapSize = pmaMemoryMapLength * sizeof(PoolMemoryBlock);

	pmaMemoryMap = (PoolMemoryBlock*)pmaInitialPointer;
	pmaCurrentPointer.store(pmaCurrentPointer + pmaMemoryMapSize);
}


PoolMemoryAllocator::PoolMemoryAllocator()
{
	;
}

void PoolMemoryAllocator::init(const sp_size initialSize) noexcept
{
	pmaInitialPointer = (sp_size) std::malloc(initialSize);
	pmaLastPointer = pmaInitialPointer + initialSize;

	assert(pmaInitialPointer != NULL);

	pmaCurrentPointer = pmaInitialPointer;
	
	allocMemoryMap(initialSize);
}

void PoolMemoryAllocator::free(void** buffer) noexcept
{
	assert(*buffer != NULL);
	assert((sp_size)*buffer >= pmaInitialPointer && (sp_size)*buffer <= pmaLastPointer);

	freedMemory.push(buffer);
}

void PoolMemoryAllocator::defrag() noexcept
{
	if (freedMemory.size() != 0)
	{
		void** moveToHere = (void**) freedMemory.top();
		freedMemory.pop();

		const sp_size blockIndex = SP_BLOCK_INDEX((sp_size)*moveToHere, pmaInitialPointer, pmaMemoryMapSize);
		const sp_size blocksToRemoveLength = pmaMemoryMap[blockIndex].blocks();
		const void* startPointer = pmaMemoryMap[blockIndex + blocksToRemoveLength].pointer;
		
		std::memmove(*moveToHere, startPointer, (pmaCurrentPointer - (sp_size)startPointer));

		pmaCurrentPointer -= blocksToRemoveLength * DEFAULT_BLOCK_SIZE_ADDRESS;

		for (sp_size i = blockIndex; i < blockIndex + blocksToRemoveLength; i++) // shift the memory <<
		{
			pmaMemoryMap[i].pointer = pmaMemoryMap[i + blocksToRemoveLength].pointer;
			pmaMemoryMap[i].size = pmaMemoryMap[i + blocksToRemoveLength].size;
		}
	}
}

sp_size PoolMemoryAllocator::deviceMemorySize() noexcept
{
#ifdef WINDOWS
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	return (sp_size) status.ullTotalPhys;
#elif UNIX
	//return vmsize.t_rm;
	return 0;
#endif
}

sp_size PoolMemoryAllocator::allocatedBlocks() noexcept
{
	return (pmaCurrentPointer.load() - pmaMemoryMapSize - pmaInitialPointer) >> SIZEOF_INT;
}

#define BLOCKS_TO_ALLOCATE(value) \
			sp_ceilBit(value, DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE_BIT_DIVISOR)
void* PoolMemoryAllocator::alloc(const sp_size size) noexcept
{
	assert(hasAvailableMemory(size));

	const sp_size previousAddress = pmaCurrentPointer.fetch_add(BLOCKS_TO_ALLOCATE(size) * DEFAULT_BLOCK_SIZE_ADDRESS);
	const sp_size index = sp_ceilBit((previousAddress - pmaMemoryMapSize - pmaInitialPointer) * SIZEOF_INT, DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE_BIT_DIVISOR);
	pmaMemoryMap[index].size = size;
	pmaMemoryMap[index].pointer = (void*)previousAddress;

	assert(((sp_size)pmaLastPointer) > ((sp_size)pmaCurrentPointer));

	return (void*)previousAddress;
}
#undef BLOCKS_TO_ALLOCATE

void* PoolMemoryAllocator::alloc(const sp_size count, const sp_size size) noexcept
{
	return PoolMemoryAllocator::alloc(count * size);
}

void* PoolMemoryAllocator::copy(const void* source, sp_size size) noexcept
{
	//void* newBuffer = ALLOC_SIZE(size);

	//std::memcpy(newBuffer, source, size);

	//return newBuffer;

	return NULL;
}

sp_size PoolMemoryAllocator::blockIndex(void* buffer) noexcept
{
	return SP_BLOCK_INDEX((sp_size)buffer, pmaInitialPointer, pmaMemoryMapSize);
}

void PoolMemoryAllocator::copy(const void* source, void* destiny, sp_size size) noexcept
{
	std::memcpy(destiny, source, size);
}

void PoolMemoryAllocator::resize(sp_size newSize) noexcept
{
	pmaInitialPointer = (sp_size)std::realloc((void*)pmaInitialPointer, newSize);

	assert(pmaInitialPointer != NULL);

	pmaCurrentPointer = pmaInitialPointer;
	pmaLastPointer = pmaInitialPointer + newSize;
}

sp_bool PoolMemoryAllocator::hasAvailableMemory(const sp_size size) noexcept
{
	return (pmaLastPointer - pmaCurrentPointer - size) > ZERO_SIZE;
}

sp_size PoolMemoryAllocator::availableMemorySize() noexcept
{
	return pmaLastPointer - pmaCurrentPointer;
}

void PoolMemoryAllocator::release() noexcept
{
	std::free((void*)pmaInitialPointer);

	pmaLastPointer = NULL;
	pmaCurrentPointer = NULL;
	pmaInitialPointer = NULL;
	pmaMemoryMap = NULL;
}