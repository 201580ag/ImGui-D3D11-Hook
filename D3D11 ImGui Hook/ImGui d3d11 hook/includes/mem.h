#pragma once
#include "includes.h"

namespace mem
{
	uintptr_t FindAddress(uintptr_t ptr, std::vector<unsigned int> offsets)
	{
		uintptr_t address = ptr;
		for (unsigned int i = 0; i < offsets.size(); ++i)
		{
			address = *(uintptr_t*)address;
			address += offsets[i];
		}
		return address;
	};
}