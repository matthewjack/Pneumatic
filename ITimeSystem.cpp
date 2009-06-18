#include "ITimeSystem.h"

#include "Windows.h"
#include "stdio.h"

// There should really be two separate testing concepts?
// One is unit test: try and establish through the interface that the implementation behaves as documented
// Other is debugging: if unit test has failed, in a human-readable way, output the observed behaviour
// These might be possible to combine: run a unit test with no logging. If it fails, run it again with logging to explain where it broke.
// Perhaps the latter happens automatically if "devmode" is enabled

// Invariants under unit test:
// PlayTime <= SessionTime
// LastFrame, SmoothedFrame, that latter is smoother and converges
// Accuracy after extremes (can that be simulated somehow, without sleep(forever)?)




SErrorDescriptor ITimeSystem::UnitTest(ILogSystem *pLog)
{
	double a,b,c,d,e,f;

	StartSession();

	a = GetSessionTimeNow();
	b = GetPlayTimeNow();
	
	printf("A %d, %d\n", a,b);

	Sleep(10);

	a = GetSessionTimeNow();
	b = GetPlayTimeNow();
	printf("B %f, %f\n", a,b);

	Sleep(10);

	a = GetSessionTimeNow();
	b = GetPlayTimeNow();
	printf("C %f, %f\n", a,b);

	StartFrame();
	Sleep(10);

	a = GetSessionTimeNow();
	b = GetPlayTimeNow();
	c = GetFrameSessionTime();
	d = GetFramePlayTime();

	printf("D %f, %f, %f, %f\n", a,b,c,d);

	Sleep(10);
	EndFrame();

	a = GetSessionTimeNow();
	b = GetPlayTimeNow();
	c = GetFrameSessionTime();
	d = GetFramePlayTime();
	printf("E %f, %f, %f, %f\n", a,b,c,d);

	Sleep(10);

	a = GetSessionTimeNow();
	b = GetPlayTimeNow();
	c = GetFrameSessionTime();
	d = GetFramePlayTime();
	printf("F %f, %f, %f, %f\n", a,b,c,d);

	StartFrame();
	Sleep(10);

	a = GetSessionTimeNow();
	b = GetPlayTimeNow();
	c = GetFrameSessionTime();
	d = GetFramePlayTime();
	printf("f %f, %f, %f, %f\n", a,b,c,d);

	EndFrame();

	Pause(true);

	a = GetSessionTimeNow();
	b = GetPlayTimeNow();
	c = GetFrameSessionTime();
	d = GetFramePlayTime();
	printf("G %f, %f, %f, %f\n", a,b,c,d);

	StartFrame();
	Sleep(10);

	a = GetSessionTimeNow();
	b = GetPlayTimeNow();
	c = GetFrameSessionTime();
	d = GetFramePlayTime();
	e = GetLastFrameDuration();
	f = GetSmoothFrameDuration();
	printf("I %f, %f, %f, %f, %f, %f\n", a,b,c,d,e,f);

	EndFrame();

	a = GetSessionTimeNow();
	b = GetPlayTimeNow();
	c = GetFrameSessionTime();
	d = GetFramePlayTime();
	e = GetLastFrameDuration();
	f = GetSmoothFrameDuration();
	printf("J %f, %f, %f, %f, %f, %f\n", a,b,c,d,e,f);

	StartFrame();
	Sleep(10);

	a = GetSessionTimeNow();
	b = GetPlayTimeNow();
	c = GetFrameSessionTime();
	d = GetFramePlayTime();
	e = GetLastFrameDuration();
	f = GetSmoothFrameDuration();
	printf("J %f, %f, %f, %f, %f, %f\n", a,b,c,d,e,f);

	EndFrame();
	Pause(false);
	StartFrame();
	Sleep(10);

	a = GetSessionTimeNow();
	b = GetPlayTimeNow();
	c = GetFrameSessionTime();
	d = GetFramePlayTime();
	e = GetLastFrameDuration();
	f = GetSmoothFrameDuration();
	printf("K %f, %f, %f, %f, %f, %f\n", a,b,c,d,e,f);



/*
	virtual void StartSession() = 0;              // Universe begins. Nothing that happened before matters.
	virtual void EndSession() = 0;				        // Universe ends. Time ceases to exist.

	virtual void StartFrame() = 0;                // We're starting a new frame. Our integration of time in finite steps started a step here.
	virtual void EndFrame() = 0;                  // We're ending a frame. A step is complete.

	virtual bool IsPaused() const = 0;            // Are we paused for our current frame? 
	virtual void Pause(bool bPause) = 0;          // Set whether this frame should be considered a paused one.
	// Do this between frames to avoid terrible confusion and indeed assertions.

	virtual double GetFramePlayTime() const = 0;  // How much unpaused time had elapsed when we started the frame?
	virtual double GetFrameSessionTime() const = 0; // How much total time had elapsed when we started the frame?

	virtual double GetPlayTimeNow() const = 0;    // Get unpaused time elapsed this very moment
	virtual double GetSessionTimeNow() const = 0;   // Get total time elapsed this very moment

	virtual double GetLastFrameTime() const = 0;  // How long did the last frame actually take?
	virtual double GetSmoothFrameTime() const = 0;// How long do we guess this frame will take?
*/
	return PN_NO_ERROR;
}
