#include "TimeSystem.h"

#include "Windows.h"      // For QueryPerformanceCounter
#include "assert.h"

/*
	I'm not certain if I'm using the best datatype here for storing the time, and I suspect the divisions could be put off.
	However, it should be more than accurate enough and it is all hidden behind an interface that just presents seconds as doubles.
	Later, this might be worth a rewrite to be really hygenic. For now it may not be worth the thought.
	Some duplication around pausing
*/


ITimeSystem * CTimeSystem::Create()
{	return new CTimeSystem(); }

CTimeSystem::CTimeSystem(void)
{
	m_dSmoothFrameDuration = 0.01f; // Assume 100Hz to start with
	QueryPerformanceFrequency( (LARGE_INTEGER*) &m_iPerformanceFreq );
	assert(m_iPerformanceFreq); // Consider quitting with error
	Reset();
}

CTimeSystem::~CTimeSystem(void)
{}

void CTimeSystem::Destroy()
{ delete this; }

void CTimeSystem::StartSession()
{
	assert(!m_bWithinSession);
	Reset(); // Reset the universe
	m_dSessionStartRaw = GetRawTime();
	m_bWithinSession = true;
}

void CTimeSystem::EndSession()
{
	assert(m_bWithinSession);
	Reset(); // Reset the universe
	m_bWithinSession = false;
}

void CTimeSystem::StartFrame()
{
	assert(!m_bWithinFrame);

	double dSessionTime= GetSessionTimeNow();

	//Update last frame duration
	m_dLastFrameDuration = dSessionTime - m_dFrameSessionTime;
	m_dSmoothFrameDuration = (m_dSmoothFrameDuration * 0.9 + m_dLastFrameDuration * 0.1);
	

	// Update total time
	m_dFrameSessionTime = dSessionTime;
	
	//Update unpaused time
	double dTotalPausedTime = m_dSessionPausedTime; // A "small" number
	if (m_bPaused)
		dTotalPausedTime += (m_dFrameSessionTime - m_dPausedSince);   // small + (large - large)
	m_dFramePlayTime = m_dFrameSessionTime - dTotalPausedTime;

	// Handle pause status
	if (m_bPaused != m_bPausedNextFrame)
	{
		if (m_bPausedNextFrame)
		{
			m_dPausedSince = m_dFrameSessionTime;
		}
		else
		{
			m_dSessionPausedTime = dTotalPausedTime;
			m_dPausedSince = 0.0f; // Just for clarity
		}
		m_bPaused = m_bPausedNextFrame;
	}

	m_bWithinFrame = true;
}


void CTimeSystem::EndFrame()
{
	assert(m_bWithinFrame);
	
	m_bWithinFrame = false;
}

bool CTimeSystem::IsPaused() const
{ return m_bPaused; }

void CTimeSystem::Pause(bool bPause)
{
	assert(!m_bWithinFrame);

	// This is all we do here - we can't adjust timers because in principle, we don't know when the next frame will start.
	m_bPausedNextFrame = bPause;
}

double CTimeSystem::GetFramePlayTime() const
{ return m_dFramePlayTime; }

double CTimeSystem::GetFrameSessionTime() const
{	return m_dFrameSessionTime; }

double CTimeSystem::GetPlayTimeNow() const
{
	// Quite unhappy with this
	double dSessionTime = GetSessionTimeNow();
	double dTotalPausedTime = m_dSessionPausedTime; // A "small" number
	if (m_bPaused)
		dTotalPausedTime += (dSessionTime - m_dPausedSince);   // small + (large - large)
	return dSessionTime - dTotalPausedTime;
}

double CTimeSystem::GetSessionTimeNow() const
{
	return GetRawTime() - m_dSessionStartRaw;
}

double CTimeSystem::GetLastFrameDuration() const
{ return m_dLastFrameDuration; }

double CTimeSystem::GetSmoothFrameDuration() const
{ return m_dSmoothFrameDuration; }


double CTimeSystem::GetRawTime() const
{
	INT64 count;
	QueryPerformanceCounter( (LARGE_INTEGER *) & count );
	// This line fixes us at an accuracy of 1/10 millisecond, for which doubles should be up to the task
	double seconds = ((10000 * count) / m_iPerformanceFreq) / ((double)10000);
	return seconds;
}

void CTimeSystem::Reset()
{
	m_dSessionStartRaw = 0.0f;
	m_dFramePlayTime = 0.0f;
	m_dFrameSessionTime = 0.0f;
	m_dPausedSince = 0.0f;
	m_dSessionPausedTime = 0.0f;
	m_dLastFrameDuration = 0.0f;
	// Leave the smoothed time alone
	m_bWithinSession = false;
	m_bWithinFrame = false;
	m_bPaused = false;
	m_bPausedNextFrame = false;
}