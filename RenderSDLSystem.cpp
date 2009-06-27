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

	gEnv.sys.pLogSystem->Log(eLV_EVENTS, "RenderSDL: Initialising\n");

	if((SDL_Init(SDL_INIT_VIDEO)==-1)) 
	{ 
		gEnv.sys.pLogSystem->Log(eLV_ERRORS, "RenderSDL: Could not initialize SDL: %s\n", SDL_GetError());
		err.type = eET_External; err.location = 1;
    return err;
	}

	// Set OpenGL attributes. AFAICS this will accept garbage without error :/
	int attrErr = 0;
	attrErr |= SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	attrErr |= SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	attrErr |= SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	attrErr |= SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 32 );
	attrErr |= SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	if (attrErr)
	{
		gEnv.sys.pLogSystem->Log(eLV_ERRORS, "RenderSDL: Couldn't set OpenGL attribute: %s\n", SDL_GetError());
		err.type = eET_External; err.location = 3;
		return err;
	}

	SDL_Surface *screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_HWPALETTE | SDL_DOUBLEBUF | SDL_OPENGL );
	if ( screen == NULL ) 
	{
		gEnv.sys.pLogSystem->Log(eLV_ERRORS, "RenderSDL: Couldn't set video mode: %s\n", SDL_GetError());
		err.type = eET_External; err.location = 2;
		return err;
	}

	return PN_NO_ERROR;
}  

SErrorDescriptor CRenderSDLSystem::Shutdown()
{
	//SErrorDescriptor err(0, eSI_RenderSDL, 0, 2);
	gEnv.sys.pLogSystem->Log(eLV_EVENTS, "RenderSDL: Shutting down\n");
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
