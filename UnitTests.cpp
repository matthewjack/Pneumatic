#include "UnitTests.h"

#include "TimeSystem.h"
#include "LogSystem.h"
#include "EntitySystem.h"

// Create, test and destroy each implementation of each subsystem


CUnitTests::CUnitTests(void)
{
}

CUnitTests::~CUnitTests(void)
{
}

SErrorDescriptor CUnitTests::Execute()
{
	// Can feed in string log here later for full reports
	SErrorDescriptor error;
	{
		CTimeSystem time;
		error = time.UnitTest(NULL);
		if (error)
			return Fail(error);
	}	

	{
		CLogSystem log;
		log.SetLogPath("test_log.txt");
		log.Log(eLV_EVENTS, "%d foo %s", 45, "myToe");
	}

	{
		CEntitySystem entity;
		error = entity.UnitTest(NULL);
		if (error)
			return Fail(error);
	}


	return error;
}


SErrorDescriptor CUnitTests::Fail(SErrorDescriptor error) const
{
	// Call a central error-decoding function, log the result

	return error;
}