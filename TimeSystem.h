#pragma once

#include "ITimeSystem.h"


class CTimeSystem : public ITimeSystem
{
public:
	static ITimeSystem * Create();

	CTimeSystem();
	~CTimeSystem();

	void Destroy();

	void StartSession(); 
	void EndSession();	

	void StartFrame();
	void EndFrame();            

	bool IsPaused() const;            
	void Pause(bool bPause);    

	double GetFramePlayTime() const;  
	double GetFrameSessionTime() const; 

	double GetPlayTimeNow() const;    
	double GetSessionTimeNow() const;   

	double GetLastFrameDuration() const;  
	double GetSmoothFrameDuration() const;

private:
	typedef __int64 INT64;

	void Reset();
	double GetRawTime() const;

	// All refer to the start of the current frame. The _current_ time values are obviously not worth storing.
	double m_dSessionStartRaw; // The the "real" time that the session started
	double m_dFramePlayTime;    // How much unpaused time had elapsed when we started the frame?
	double m_dFrameSessionTime;   // How much total time had elapsed...
	double m_dPausedSince;			// 
	double m_dSessionPausedTime;// Accumulated paused time this session, up to the last time we unpaused. Is this too unhygenic?
	double m_dLastFrameDuration;    // How long did the last frame actually take?
	double m_dSmoothFrameDuration;  // How long do we guess this frame will take?

	bool m_bWithinSession, m_bWithinFrame;
	bool m_bPaused, m_bPausedNextFrame;

	INT64 m_iPerformanceFreq;   // Divisor for performance frequency values
};
