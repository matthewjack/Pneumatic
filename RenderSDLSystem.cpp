#include "RenderSDLSystem.h"

#include "../Libraries/SDL-1.2.13/include/SDL.h"

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Environment.h"
#include "ILogSystem.h"
#include "IEntitySystem.h"
#include "IGeometrySystem.h"

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

	// Create SDL surface with correct video mode
	int iWidth = 640;
	int iHeight = 480;
	SDL_Surface *screen = SDL_SetVideoMode( iWidth, iHeight, 32, SDL_HWSURFACE | SDL_HWPALETTE | SDL_OPENGL );
	if ( screen == NULL ) 
	{
		gEnv.sys.pLogSystem->Log(eLV_ERRORS, "RenderSDL: Couldn't set video mode: %s\n", SDL_GetError());
		err.type = eET_External; err.location = 2;
		return err;
	}

	float ratio = (float) iWidth / (float) iHeight;

	/* Our shading model--Gouraud (smooth). */
	glShadeModel( GL_SMOOTH );

	/* Culling. */
	glCullFace( GL_BACK );
	glFrontFace( GL_CCW );
	glEnable( GL_CULL_FACE );

	/* Set the clear color. */
	glClearColor( 0, 0, 0, 0 );

	/* Setup our viewport. */
	glViewport( 0, 0, iWidth, iHeight );

	/*
	 * Change to the projection matrix and set
	 * our viewing volume.
	 */
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	
	/*
	 * EXERCISE:
	 * Replace this with a call to glFrustum.
	 */
  gluPerspective( 60.0, ratio, 1.0, 1024.0 );


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
	FrameSetup();
	
	// We need to fetch all renderable objects
	// For now, all at once, but an iterator is the way to go
	TEntities renderableEntities;
	SEntityQuery query;
	query.renderType = //Hmm.
	gEnv.sys.pEntitySystem->Find(query, renderableEntities);

	for (TEntities::const_iterator it = renderableEntities.begin(); it != renderableEntities.end(); ++it)
	{
		EntityId id = *it;
		IEntity *pEntity = gEnv.sys.pEntitySystem->GetEntity(id);
		assert(pEntity);

    ERenderType renderType = pEntity->GetIRender->GetType();
		switch (renderType)
		{
		case eRT_SVG:
			RenderSVGObject();


			break;
		default:
			assert(false);
		}
	}



//glClear(GL_COLOR_BUFFER_BIT); // no depth buffer

			glColor3f(1.0f, 1.0f, 1.0);
			glBegin(GL_LINE_STRIP);
			glVertex2f(100.0f,100.0f);
			glVertex2f(200.0f,200.0f);
			glEnd();

			gEnv.sys.pLogSystem->Log(eLV_ERRORS, "Any error?: %s\n", SDL_GetError());

		// Load
		static struct SVGPath* plist = 0;
		if (!plist)
			plist = svgParseFromFile("test.svg");
		// Use...
		for (SVGPath* it = plist; it; it = it->next)
		{
			glColor3f(1.0f, 1.0f, 1.0);
			glBegin(GL_LINE_STRIP);
			for (int i=0; i<it->npts; i++)
			{
				Vec2 vPoint(it->pts[i*2], it->pts[i*2+1]);
				glVertex2f(vPoint.x,vPoint.y);
			}
			glEnd();
		// Delete
		//svgDelete(plist);
		}
		


	SDL_GL_SwapBuffers();

	
}


void CRenderSDLSystem::FrameSetup(void)
{
	lMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (0, XSize, YSize, 0, 0, 1);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();

	glDisable(GL_DEPTH_TEST);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}