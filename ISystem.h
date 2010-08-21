#pragma once

// Skeleton of common interface across all system interfaces
// Should eventually encompass memory statistics etc

// Some kind of virtual constructor... is perhaps the tricky bit. Best left out actually, to allow for multiple implementations
// Update?

// Constructors of systems can't fail, but init can fail, returning an error code
//	virtual SErrorDescriptor Init() {};  Should this be compulsory? Or does it always need different parameters?

#include "Definitions.h"

struct ILogSystem;

struct ISystem
{
	virtual SErrorDescriptor UnitTest(ILogSystem *pLog = NULL) = 0;         // Giving a logger is optional
	virtual SErrorDescriptor Shutdown() { return PN_NO_ERROR; };            // Shutdown to clean state that could be reinitialised
	virtual ~ISystem() {};                                                  // Destroy the system
};