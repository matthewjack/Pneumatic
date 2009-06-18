#include "TimeSystem.h"
#include "LogSystem.h"

#include "Environment.h"

#include "UnitTests.h"

#include "conio.h"

void main( int argc, char *argv[ ], char *envp[ ] )
{
	CUnitTests tests;
	tests.Execute();

	
	CEnvironment::SConfiguration config;
	config.sLogFilename = "pneumata_log.txt";
	gEnv.Init(config);


	PN_LOG(eLV_WARNINGS,"%d foo %s", 45, "myFoot");

	PN_LOG_EXT(eLV_ERRORS, int b = 5+4, "%d foo %s",b, "myFoot");

	_getch();
}
