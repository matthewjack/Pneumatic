#pragma once

// Run all units tests

#include "Definitions.h"

class CUnitTests
{
public:
	CUnitTests(void);
	~CUnitTests(void);

	SErrorDescriptor Execute();

protected:
	SErrorDescriptor Fail(SErrorDescriptor error) const;     // Log the failure and return the same error
};
