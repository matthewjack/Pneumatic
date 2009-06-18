#pragma once

// Skeleton of common interface across all system interfaces
// Should eventually encompass memory statistics etc

#include "Definitions.h"

struct ILogSystem;

struct ISystem
{

	virtual SErrorDescriptor UnitTest(ILogSystem *pLog = NULL) = 0;         // Giving a logger is optional
};