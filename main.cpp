#include "ITimeSystem.h"
#include "ILogSystem.h"
#include "IRenderSystem.h"

#include "Environment.h"

#include "UnitTests.h"

#include "conio.h"

void main( int argc, char *argv[ ], char *envp[ ] )
{
	// What would make most sense is:
	// Optionally test the logger, then create just the logger in the environment
	// Then proceed with the other unit tests

	CUnitTests tests;
	tests.Execute();

	
	CEnvironment::SConfiguration config;
	config.sLogFilename = "pneumata_log.txt";
	gEnv.Init(config);


	PN_LOG(eLV_WARNINGS,"%d foo %s", 45, "myFoot");

	PN_LOG_EXT(eLV_ERRORS, int b = 5+4, "%d foo %s",b, "myFoot");

	for (int i=0; i<360; i++)
		gEnv.sys.pRenderSystem->Update(0.1f);
	

	// Associate data files with objects
	// Load SVG files for objects
	// Each one involves creating a mesh
	// Potential for tesselation
	// Rendering

	


	_getch();
}
