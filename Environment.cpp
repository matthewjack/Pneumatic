#include "Environment.h"

#include "TimeSystem.h"
#include "LogSystem.h"

// A few pinciples:
// For each system it should be possible to create and unit test multiple instances
// It should be possible to swap in a different implementation with only changes to this file

CEnvironment gEnv;


SSystemsTable::SSystemsTable() : 
		pEntitySystem(0),
		pPersonalitySystem(0),
		pPhysicsSystem(0),
		pRenderSystem(0),
		pTimeSystem(0),
		pLogSystem(0)
		{}

CEnvironment::CEnvironment()
{}

void CEnvironment::Init(SConfiguration &config)
{
	//sys.pEntitySystem = new CEntitySystem();
	//sys.pPersonalitySystem = new CPersonalitySystem();
	//sys.pPhysicsSystem = new CPhysicsSystem();
	//sys.pRenderSystem = new CRenderSystem();
	sys.pTimeSystem = CTimeSystem::Create();

	// Create log system and start log file
	CLogSystem *pLog = (CLogSystem *) CLogSystem::Create();
	if (config.sLogFilename)
		pLog->SetLogPath(config.sLogFilename);
	pLog->Log(eLV_EVENTS,"Pneumata log file started");
	sys.pLogSystem = pLog;

	
}

CEnvironment::~CEnvironment(void)
{
	//delete sys.pEntitySystem;
	//delete sys.pPersonalitySystem;
	//delete sys.pPhysicsSystem;
	//delete sys.pRenderSystem;
	sys.pTimeSystem->Destroy();
	sys.pLogSystem->Destroy();
}

