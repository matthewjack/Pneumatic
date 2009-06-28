#include "RenderSDLSystem.h"

#include "../Sources/SDL-1.2.13/include/SDL.h"

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Environment.h"
#include "ILogSystem.h"

#include "nanosvg/nanosvg.h"
#include "Vec2.h"

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
	static float angle = 0.0f;
	if (angle < 360.0f)
	{
    static GLfloat v0[] = { -1.0f, -1.0f,  1.0f };
    static GLfloat v1[] = {  1.0f, -1.0f,  1.0f };
    static GLfloat v2[] = {  1.0f,  1.0f,  1.0f };
    static GLfloat v3[] = { -1.0f,  1.0f,  1.0f };
    static GLfloat v4[] = { -1.0f, -1.0f, -1.0f };
    static GLfloat v5[] = {  1.0f, -1.0f, -1.0f };
    static GLfloat v6[] = {  1.0f,  1.0f, -1.0f };
    static GLfloat v7[] = { -1.0f,  1.0f, -1.0f };
    static GLubyte red[]    = { 255,   0,   0, 255 };
    static GLubyte green[]  = {   0, 255,   0, 255 };
    static GLubyte blue[]   = {   0,   0, 255, 255 };
    static GLubyte white[]  = { 255, 255, 255, 255 };
    static GLubyte yellow[] = {   0, 255, 255, 255 };
    static GLubyte black[]  = {   0,   0,   0, 255 };
    static GLubyte orange[] = { 255, 255,   0, 255 };
    static GLubyte purple[] = { 255,   0, 255,   0 };

    /* Clear the color and depth buffers. */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* We don't want to modify the projection matrix. */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    /* Move down the z-axis. */
    glTranslatef( 0.0, 0.0, -5.0 );

    /* Rotate. */
    glRotatef( angle, 0.0, 1.0, 0.0 );
		angle++;

    /* Send our triangle data to the pipeline. */
    glBegin( GL_TRIANGLES );

    glColor4ubv( red );
    glVertex3fv( v0 );
    glColor4ubv( green );
    glVertex3fv( v1 );
    glColor4ubv( blue );
    glVertex3fv( v2 );

    glColor4ubv( red );
    glVertex3fv( v0 );
    glColor4ubv( blue );
    glVertex3fv( v2 );
    glColor4ubv( white );
    glVertex3fv( v3 );

    glColor4ubv( green );
    glVertex3fv( v1 );
    glColor4ubv( black );
    glVertex3fv( v5 );
    glColor4ubv( orange );
    glVertex3fv( v6 );

    glColor4ubv( green );
    glVertex3fv( v1 );
    glColor4ubv( orange );
    glVertex3fv( v6 );
    glColor4ubv( blue );
    glVertex3fv( v2 );

    glColor4ubv( black );
    glVertex3fv( v5 );
    glColor4ubv( yellow );
    glVertex3fv( v4 );
    glColor4ubv( purple );
    glVertex3fv( v7 );

    glColor4ubv( black );
    glVertex3fv( v5 );
    glColor4ubv( purple );
    glVertex3fv( v7 );
    glColor4ubv( orange );
    glVertex3fv( v6 );

    glColor4ubv( yellow );
    glVertex3fv( v4 );
    glColor4ubv( red );
    glVertex3fv( v0 );
    glColor4ubv( white );
    glVertex3fv( v3 );

    glColor4ubv( yellow );
    glVertex3fv( v4 );
    glColor4ubv( white );
    glVertex3fv( v3 );
    glColor4ubv( purple );
    glVertex3fv( v7 );

    glColor4ubv( white );
    glVertex3fv( v3 );
    glColor4ubv( blue );
    glVertex3fv( v2 );
    glColor4ubv( orange );
    glVertex3fv( v6 );

    glColor4ubv( white );
    glVertex3fv( v3 );
    glColor4ubv( orange );
    glVertex3fv( v6 );
    glColor4ubv( purple );
    glVertex3fv( v7 );

    glColor4ubv( green );
    glVertex3fv( v1 );
    glColor4ubv( red );
    glVertex3fv( v0 );
    glColor4ubv( yellow );
    glVertex3fv( v4 );

    glColor4ubv( green );
    glVertex3fv( v1 );
    glColor4ubv( yellow );
    glVertex3fv( v4 );
    glColor4ubv( black );
    glVertex3fv( v5 );

    glEnd( );

	SDL_GL_SwapBuffers();
	}
	else
	{
const float XSize = 640, YSize = 480;
glMatrixMode (GL_PROJECTION);
glLoadIdentity ();
glOrtho (0, XSize, YSize, 0, 0, 1);
glMatrixMode (GL_MODELVIEW);
glLoadIdentity ();

glDisable(GL_DEPTH_TEST);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
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
				//float* pts;
				//int npts;
				//unsigned int fillColor;
				//unsigned int strokeColor;
				//float strokeWidth;
				//char hasFill;
				//char hasStroke;
				//char closed;
				//struct SVGPath* next;
			}
			glEnd();
		// Delete
		//svgDelete(plist);
		}
		


	SDL_GL_SwapBuffers();
	}

}
