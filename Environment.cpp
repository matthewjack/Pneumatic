#include "Environment.h"

#include "TimeSystem.h"
#include "LogSystem.h"

// A few pinciples:
// For each system it should be possible to create and unit test multiple instances
// It should be possible to swap in a different implementation with only changes to this file

CEnvironment::CEnvironment(void)
{
	//sys.pEntitySystem = new CEntitySystem();
	//sys.pPersonalitySystem = new CPersonalitySystem();
	//sys.pPhysicsSystem = new CPhysicsSystem();
	//sys.pRenderSystem = new CRenderSystem();
	sys.pTimeSystem = CTimeSystem::Create();
	sys.pLogSystem = CLogSystem::Create();
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

