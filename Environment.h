#pragma once

#include "Settings.h"

struct IPhysicsSystem;
struct IRenderSystem;
struct IEntitySystem;
struct IPersonalitySystem;
struct ITimeSystem;
struct ILogSystem;


struct SSystemsTable
{
	IEntitySystem *pEntitySystem;
	IPersonalitySystem *pPersonalitySystem;
	IPhysicsSystem *pPhysicsSystem;
	IRenderSystem *pRenderSystem;
	ITimeSystem *pTimeSystem;
	ILogSystem *pLogSystem;
	
	SSystemsTable();
};

class CEnvironment
{
public:
	struct SConfiguration
	{
		const char * sLogFilename;

		SConfiguration() :
			sLogFilename(0)
			{}
	};

	SSystemsTable sys;


	CEnvironment();                                          // Create empty environment
	void Init(SConfiguration &config);                       // Initialise environment, given configuration
	~CEnvironment(void);                                     // Clean up and destroy environment
};

extern CEnvironment gEnv;
