#include "UnitTests.h"

#include "TimeSystem.h"
#include "LogSystem.h"

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
		time.UnitTest(NULL);
		//if (error)
		//	{ Fail("CTimeSystem", error); }
	}	

	{
		CLogSystem log;
		log.SetLogPath("test_log.txt");
		log.Log(eLV_EVENTS, "%d foo %s", 45, "myToe");
	}

	return error;
}