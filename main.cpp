#include "ITimeSystem.h"
#include "ILogSystem.h"

#include "Environment.h"

#include "UnitTests.h"

#include "Documentation.h"

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



	_getch();
}
