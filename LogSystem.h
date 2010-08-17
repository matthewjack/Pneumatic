#pragma once

#include "ILogSystem.h"

#include <string>
#include <stdio.h>

// Should be called LogFileSystem!

// This implementation logs to files only
// When created, it has no files to log to, it must be set

class CLogSystem : public ILogSystem
{
public:
	//// ILogSystem interface
	SErrorDescriptor UnitTest(ILogSystem *) 
		{ return SErrorDescriptor(); }                         // Very awkward to unit test this implementation
	
	//// Unique to this implementation
	
	// Could become Init(...) ?
	bool SetLogPath( const char * sPath, bool bTest = false );  // Set path of file to use for logging. bTest = true will cause it to try to create and delete the file.
	
	CLogSystem(void);
	~CLogSystem(void);
	
	ELogVerbosity GetVerbosity() const;
	void SetVerbosity(ELogVerbosity eVerbosity); 
	TVerbosityPeeker GetVerbosityPeeker() const;

	void Log(ELogVerbosity eVerbosity, const char * format, ...);

                                                           // Returns false iff a test was attempted and failed.


protected:
	bool OpenFile();
	bool CloseFile();

	static const unsigned BUFF_LENGTH = 1024;
	std::string m_sPath;
	ELogVerbosity m_eVerbosity;
	FILE *m_fp;
	char m_buff[BUFF_LENGTH];
};
