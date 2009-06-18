#pragma once

#ifndef NULL
	#define NULL 0
#endif

// Lets have all defines and macros start PM_ to avoid conflicts
#define PN_INVALID_TYPE ((int)-1)

typedef unsigned char byte;

typedef int PhysicsType;
typedef int PersonalityType;
typedef int RenderType;

typedef int EntityId;


enum EErrorType
{
	eET_None,
};

enum ESystemImplementation
{
	eSI_Time = 1,
	eSI_PhysicsVerlet,
	eSI_LogFile,
	eSI_LogBuffer,
};


//typedef std::vector <EntityId> TEntities;

// Used as a structured errno, intended to be given as hex
// Type = { } - might be unused, but left with f.p. exceptions in mind, other broad descriptions across all systems
// System = { ESystemImplementation }
// Subsystem = { Collisions... } - defined by the System implementation, unique within that system
// Location - just a number, unique to the subsystem, identifying which check failed
// Perhaps a string should be added to this, or perhaps we're jsut as well without

enum epn_no_error { PN_NO_ERROR };

struct SErrorDescriptor
{
	byte type, system, subsystem, location;

	SErrorDescriptor()                                       // Denotes no error
		: type(0), system(0), subsystem(0), location(0) {}

	SErrorDescriptor (epn_no_error)
		: type(0), system(0), subsystem(0), location(0) {}

	SErrorDescriptor(byte _type, byte _system, byte _subsystem, byte _location)
		: type(_type), system(_system), subsystem(_subsystem), location(_location)
	{}

	operator unsigned int() const { return location & (subsystem << 8) &  (system << 16) &  (type << 24); }
};