#pragma once

#include "IRenderSystem.h"

class CRenderSDLSystem : public IRenderSystem
{
public:
	/// ISystem interface
	SErrorDescriptor Shutdown();

	/// IRenderSystem interface
	SErrorDescriptor Init();
	void Update(float fDelta);

	// New methods
	CRenderSDLSystem(void);
	~CRenderSDLSystem(void);
};
