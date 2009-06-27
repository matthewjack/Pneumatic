#include "RenderSDLSystem.h"

#include "../Sources/SDL-1.2.13/include/SDL.h"

#include "Environment.h"
#include "ILogSystem.h"

CRenderSDLSystem::CRenderSDLSystem()
{
}

SErrorDescriptor CRenderSDLSystem::Init()
{
	SErrorDescriptor err(0, eSI_RenderSDL, 0, 0);

	gEnv.sys.pLogSystem->Log(eLV_EVENTS, "SDL: Initialising\n");

	if((SDL_Init(SDL_INIT_VIDEO)==-1)) 
	{ 
		gEnv.sys.pLogSystem->Log(eLV_ERRORS, "Could not initialize SDL: %s\n", SDL_GetError());
		err.type = eET_External; err.location = 1;
    return err;
	}

	return PN_NO_ERROR;
}  

SErrorDescriptor CRenderSDLSystem::Shutdown()
{
	//SErrorDescriptor err(0, eSI_RenderSDL, 0, 2);
	gEnv.sys.pLogSystem->Log(eLV_EVENTS, "SDL: Shutting down\n");
  SDL_Quit();
	return PN_NO_ERROR;
}


CRenderSDLSystem::~CRenderSDLSystem()
{
	if (true)
		Shutdown();
}


void CRenderSDLSystem::Update(float fDelta)
{

}
