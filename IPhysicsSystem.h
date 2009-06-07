#pragma once

#include "Settings.h"

struct SPhysicsDescription
{
	bool bActive;       // Am I affected by world physics?
	bool bCollidable;   // Can things collide with me?
	float fDensity;     // My density
	float fMass;        // My mass
	float fRadius;	     // A bounding radius
	Vec2 vvelocity?;    //
	Vec2 vImpulse;	    	// Accumulated impulse requests
}


// Can be both global and local?
struct SPhysicsContext
{
	bool bActive;       // Is this context enabled?
	Vec2 vGravity;      // Gravity or analogue thereof
	float fDensity;     // My density
	float fMass;        // My mass
	float fRadius;	     // A bounding radius
	Vec2 vvelocity?;    //
	Vec2 vImpulse;	    	// Accumulated impulse requests
}

// Local physics contexts can be layered over the world
struct SLocalPhysicsContext : public SPhysicsContext;
{
	bool bAdditive;     // Acculumate the effect of this context on others, rather than overide
	

};

// The global physics context
struct SGlobalPhysicsContext : public SPhysicsContext
{

};


struct IPhysics
{
	PhysicsType GetType() const = 0;					// Physics type

	const SPhysicsDescription &GetDescription() const = 0;
	void SetDescription(SPhysicsDescription &description) = 0;

	void CustomUpdate() = 0;;     // Any customised update code, run before the main physics update pass
}


struct IPhysicsSystem
{
	void Update(float fDelta) = 0;

};
