#pragma once

// Could all systems share an core interface?
// Some kind of virtual constructor... is perhaps the tricky bit. Best left out actually, to allow for multiple implementations
// Destructor, update, unit test, seem plausible. maybe other things?
// Could this help simplify some code?
// What happens to the time between frames? If it counts towards session time but not the time the last frame took, is that inconsistent?
// Is it more or less correct to call last frame time the time between frames?

#include "Settings.h"
#include "ISystem.h"

struct ITimeSystem : public ISystem
{
	/// ISystem methods
	SErrorDescriptor UnitTest(ILogSystem *pLog);

	/// New methods
	virtual void StartSession() = 0;                         // Universe begins. Nothing that happened before matters.
	virtual void EndSession() = 0;				                   // Universe ends. Time ceases to exist.

	virtual void StartFrame() = 0;                           // We're starting a new frame. Our integration of time in finite steps started a step here.
	virtual void EndFrame() = 0;                             // We're ending a frame. A step is complete. No effect on behaviour except that StartFrame may be called.

	virtual bool IsPaused() const = 0;                       // Are we paused for our current frame? 
	virtual void Pause(bool bPause) = 0;                     // Set whether this frame should be considered a paused one.
																	                         // Do this between frames to avoid terrible confusion and indeed assertions.

	virtual double GetFramePlayTime() const = 0;             // How much unpaused time had elapsed when we started the frame?
	virtual double GetFrameSessionTime() const = 0;          // How much total time had elapsed when we started the frame?

	// Rename Frame/Now?
	virtual double GetPlayTimeNow() const = 0;               // Get unpaused time elapsed this very moment
	virtual double GetSessionTimeNow() const = 0;            // Get total time elapsed this very moment

	virtual double GetLastFrameDuration() const = 0;         // How long did the last frame actually take?
	virtual double GetSmoothFrameDuration() const = 0;       // How long do we guess this frame will take?


};
