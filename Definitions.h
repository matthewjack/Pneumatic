#pragma once

#ifndef NULL
	#define NULL 0
#endif

// Lets have all defines and macros start PM_ to avoid conflicts
#define PN_INVALID_TYPE ((int)-1)

typedef unsigned char byte;

typedef int EPhysicsType;
typedef int EPersonalityType;
typedef int ERenderType;

typedef int EntityId;

struct IPhysics;
struct IPersonality;
struct IRender;

enum EErrorType
{
	eET_General = 0,                                         // Something broke :-)
	eET_External,                                            // A third-party component reported the error
};

// Try and maintain these values after any release - they are intended to be usefully reported
enum ESystemImplementation
{
	eSI_Time = 1,

	eSI_PhysicsVerlet = 8,

	eSI_LogFile = 16,
	eSI_LogBuffer,

	eSI_RenderSDL = 24,
};

// Used as a structured errno, intended to be given as hex
// Type = { } - might be unused, but left with f.p. exceptions in mind, other broad descriptions across all systems
// System = { ESystemImplementation }
// Subsystem = { Collisions... } - defined by the System implementation, unique within that system
// Location - just a number, unique within the subsystem, identifying which check failed
// Perhaps a string should be added to this, or perhaps we're jsut as well without

// Actually, I'm quite tempted to just use this where needed but just pass it around as a plain int32

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

	operator unsigned int() const { return location | (subsystem << 8) | (system << 16) | (type << 24); }
};