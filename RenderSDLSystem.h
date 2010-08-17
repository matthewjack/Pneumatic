#pragma once

// Correct name would be RenderSDLOpenGL?
// Or possible OGL/DX are subclasses, but that seems OTT

#include "IRenderSystem.h"

class CRenderSDLSystem : public IRenderSystem
{
public:
	//// ISystem interface
	SErrorDescriptor Shutdown();

	//// IRenderSystem interface
	SErrorDescriptor Init();
	void Update(float fDelta);

	// New methods
	CRenderSDLSystem(void);
	~CRenderSDLSystem(void);

private:
	void FrameSetup(void);                                   // Clearing, matrix setup, etc, before actual rendering
};
