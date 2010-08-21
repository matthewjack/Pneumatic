#pragma once

#ifndef NULL
	#define NULL 0
#endif

// Lets have all defines and macros start PN_ to avoid conflicts
#define PN_INVALID_TYPE ((int)-1)

typedef unsigned char byte;

typedef int PhysicsType;
typedef int PersonalityType;
typedef int RenderType;

typedef int EntityId;           // Salted id for uniquely identifying entities
typedef int GeometryId;             // (unsalted?) id of a piece of geometry 
typedef int TextureId;
typedef int UserDataId;

struct IPhysics;
struct IPersonality;
struct IRender;
struct IGeometry;

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


// Header structure that wraps a void * block as a simple object
// Used internally as well as externally
// What about deleting this? Different ownership possiblities? Reference counting?
struct SUserData
{
	unsigned nUserId;                                      // If you want to distinguish different blocks, can use your own ids here
	unsigned nUserType;                                    // If you want to distinguish different kinds of block, can use your own type identifiers here
	const char * pSDescription;                            // For debugging, put a null-terminated string in your block and point to it here

	const void * GetData() const { return this + sizeof(SUserData); } // Get pointer to the user data itself
	void * GetData() { return this + sizeof(SUserData); } 
	unsigned GetDataSize() const { return nBlockSize; }    // Get size of user data itself in bytes 
	unsigned GetSystemId() const { return nSystemId; }     // Get the system id of this block

private:
	SUserData() {};                                        // Only the userdata system can create these
	unsigned nBlockSize;                                   // Size of the user data (excluding this header struct)
	UserDataId nSystemId;                                  // Id assigned by the system. Internal and external id ranges are distinct.
};