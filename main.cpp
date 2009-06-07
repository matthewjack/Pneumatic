#include "TimeSystem.h"
#include "LogSystem.h"

#include "conio.h"

void main( int argc, char *argv[ ], char *envp[ ] )
{
	ITimeSystem *pTimeSystem = new CTimeSystem;
	pTimeSystem->UnitTest();

	CLogSystem *pLogSystem = new CLogSystem;
	pLogSystem->SetLogPath("pneumata_log.txt");
	pLogSystem->Log(eLV_EVENTS, "%d foo %s", 45, "myToe");


	_getch();
}
