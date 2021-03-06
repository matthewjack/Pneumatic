#include "Environment.h"

#include "LogSystem.h"
#include "TimeSystem.h"
#include "EntitySystem.h"
#include "RenderSDLSystem.h"

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

	// Render system
	sys.pRenderSystem = new CRenderSDLSystem();
	err = sys.pRenderSystem->Init();
	if (err)
		return err;


	//sys.pPersonalitySystem = new CPersonalitySystem();
	//sys.pPhysicsSystem = new CPhysicsSystem();

	sys.pLogSystem->Log(eLV_EVENTS,"Environment: systems OK\n");
	return PN_NO_ERROR;
}

CEnvironment::~CEnvironment(void)
{
	sys.pLogSystem->Log(eLV_EVENTS,"Environment Shutting down systems\n");

	//delete sys.pPersonalitySystem;
	//delete sys.pPhysicsSystem;
	
	delete sys.pRenderSystem;
	delete sys.pEntitySystem;
	delete sys.pTimeSystem;

	sys.pLogSystem->Log(eLV_EVENTS,"Ending Pneumata log file\n");
	delete sys.pLogSystem;
}

