#include "LogSystem.h"

// Currently we create the file on first real output, and only close it on shutdown

#include <stdarg.h>
#include <assert.h>

ILogSystem * CLogSystem::Create()
{ return new CLogSystem(); }

CLogSystem::CLogSystem(void)
{
	m_fp = NULL;
	m_eVerbosity = eLV_EVENTS;
	assert(BUFF_LENGTH > 0);
}

CLogSystem::~CLogSystem(void)
{
	CloseFile();
}

void CLogSystem::Destroy()
{
	delete this; 
}

bool CLogSystem::SetLogPath( const char * sPath, bool bTest )
{
	m_sPath = sPath;

	if (!bTest) return true;
	if (!OpenFile()) return false;
	if (!CloseFile()) return false;

	return true;
}

ELogVerbosity CLogSystem::GetVerbosity() const
{
	return m_eVerbosity;
}

void CLogSystem::SetVerbosity(ELogVerbosity eVerbosity)
{
	m_eVerbosity = eVerbosity;
}

CLogSystem::TVerbosityPeeker CLogSystem::GetVerbosityPeeker() const
{
	return (&m_eVerbosity);
}

void CLogSystem::Log(ELogVerbosity eVerbosity, const char * format, ...)
{
	if (eVerbosity > m_eVerbosity || eVerbosity == eLV_NEVER) return;
	
	if (!m_fp) OpenFile();
	if (!m_fp) return;

	va_list args;
	va_start(args, format);
	int result = vsnprintf(m_buff, BUFF_LENGTH, format, args);
	assert(result != -1);
	// Make sure there's a limit to the amount of rubbish we can output
	m_buff[BUFF_LENGTH-1] = '\0';
	fprintf(m_fp, "%s", m_buff);
	fflush(m_fp);
}

bool CLogSystem::OpenFile()
{
	m_fp = fopen(m_sPath.c_str(),"wt");
	return m_fp;
}

bool CLogSystem::CloseFile()
{
	if (!m_fp) return false;
	bool bResult = fclose(m_fp);
	m_fp = NULL;
	return bResult;
}