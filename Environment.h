#pragma once

#include "Settings.h"
#include "Definitions.h"

struct IEntitySystem;
struct ITimeSystem;
struct ILogSystem;


struct SSystemsTable
{
	IEntitySystem *pEntitySystem;
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
	~CEnvironment(void);                                     // Clean up and destroy environment

	SErrorDescriptor Init(SConfiguration &config);           // Initialise environment, given configuration
};

extern CEnvironment gEnv;
