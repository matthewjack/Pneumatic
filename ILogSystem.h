#pragma once

// I'm not sure if testing the log system makes much sense
// Might be room for a super-verbose debugging log level
// This might genuinely be worth multithreaded
// Differing file/console later. Console buffer later.
// note that eLV_ is probably the thing to grep for, if we insist it must be specified.

// Add a way to set a callback function that can be used to generate prefixes - in this case frame and time
// a flush might be a useful addition, or two modes, one of which will always flush, and some catch on exit() that will ensure it gets output?

#include "Settings.h"

enum ELogVerbosity
{
	eLV_NEVER,       // Never output, always ignore
	eLV_ERRORS,      // Only output when broken
	eLV_WARNINGS,    // ... and output when suspicious
	eLV_EVENTS,      // ... and output events considered "highest-level" for this system
	eLV_COMMENTS,     // ... and output everything else that we're doing
};

struct ILogSystem
{
public:
	typedef const ELogVerbosity * const TVerbosityPeeker;

	virtual void Destroy() = 0;                              // Cleanup and delete

	virtual ELogVerbosity GetVerbosity() const = 0;                // Get currently set verbosity level 
	virtual void SetVerbosity(ELogVerbosity eVerbosity) = 0;       // Set verbosity level. Defaults to eLV_EVENTS
	virtual TVerbosityPeeker GetVerbosityPeeker() const = 0;       // Get a pointer to the current verbosity level to store and use for fast "peek" with no function call
	                                                         // Remains valid for the lifetime of the log instance
	virtual void Log(ELogVerbosity eVerbosity, const char * format, ...) = 0;

	// No unit test?
};






// Allow avoiding debug code, allow compiling it out, etc.
// Note there are apparently some variations for varaiadic macros - GCC etc.

#ifndef PN_LOG_LEVEL
	#define PN_LOG_LEVEL eLV_COMMENTS
#endif

#define PN_LOG(level,format,...) \
	if ( (level) <= PN_LOG_LEVEL ) {gEnv->pLog->Log((level),(format),__VA_ARGS__);}

#define PN_LOG_EXT(level,format,code_block,...) \
	if ( (level) <= PN_LOG_LEVEL ) \
	{ \
		code_block \
		gEnv->pLog->Log((level),(format),__VA_ARGS__); \
	} 





