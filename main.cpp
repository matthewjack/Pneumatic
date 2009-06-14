#include "TimeSystem.h"
#include "LogSystem.h"

#include "Environment.h"

#include "conio.h"

void main( int argc, char *argv[ ], char *envp[ ] )
{
	ITimeSystem *pTimeSystem = new CTimeSystem;
	pTimeSystem->UnitTest();
	pTimeSystem->Destroy();

	CLogSystem *pLogSystem = new CLogSystem;
	pLogSystem->SetLogPath("test_log.txt");
	pLogSystem->Log(eLV_EVENTS, "%d foo %s", 45, "myToe");
	pLogSystem->Destroy();

	CEnvironment::SConfiguration config;
	config.sLogFilename = "pneumata_log.txt";
	gEnv.Init(config);

	PN_LOG(eLV_WARNINGS,"%d foo %s", 45, "myFoot");

	PN_LOG_EXT(eLV_ERRORS, int b = 5+4, "%d foo %s",b, "myFoot");

	_getch();
}
