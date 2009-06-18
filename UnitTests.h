#pragma once

// Run all units tests

#include "Definitions.h"

class CUnitTests
{
public:
	CUnitTests(void);
	~CUnitTests(void);

	SErrorDescriptor Execute();
};
