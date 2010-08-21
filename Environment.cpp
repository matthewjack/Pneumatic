#include "Environment.h"

#include "LogSystem.h"
#include "TimeSystem.h"
#include "EntitySystem.h"

// A few pinciples:
// For each system it should be possible to create and unit test multiple instances
// It should be possible to swap in a different implementation with only changes to this file

CEnvironment gEnv;


SSystemsTable::SSystemsTable() : 
		pEntitySystem(0),
		pTimeSystem(0),
		pLogSystem(0)
		{}

CEnvironment::CEnvironment()
{}

SErrorDescriptor CEnvironment::Init(SConfiguration &config)
{
	SErrorDescriptor err;

	// Create log system and start log file
	CLogSystem *pLog = new CLogSystem();
	if (config.sLogFilename)
		pLog->SetLogPath(config.sLogFilename);
	pLog->Log(eLV_EVENTS,"Pneumata log file started\n");
	sys.pLogSystem = pLog;
		
	pLog->Log(eLV_EVENTS,"Environment: initialising systems\n");

	// Time system
	sys.pTimeSystem = new CTimeSystem();

	// Entity system
	sys.pEntitySystem = new CEntitySystem();


	sys.pLogSystem->Log(eLV_EVENTS,"Environment: systems OK\n");
	return PN_NO_ERROR;
}

CEnvironment::~CEnvironment(void)
{
	sys.pLogSystem->Log(eLV_EVENTS,"Environment Shutting down systems\n");

	delete sys.pEntitySystem;
	delete sys.pTimeSystem;

	sys.pLogSystem->Log(eLV_EVENTS,"Ending Pneumata log file\n");
	delete sys.pLogSystem;
}

