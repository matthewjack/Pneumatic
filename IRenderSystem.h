#pragma once

#include "Settings.h"
#include "ISystem.h"
#include "IRender.h"

struct IRenderSystem : public ISystem
{
	// ISystem methods
	virtual SErrorDescriptor UnitTest(ILogSystem *pLog = NULL) { return PN_NO_ERROR; }  
	virtual SErrorDescriptor Shutdown() = 0;

	// New methods
	virtual ~IRenderSystem() {};
	virtual SErrorDescriptor Init() = 0;
	virtual void Update(float fDelta) = 0;
};
