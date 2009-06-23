#pragma once

#include "Settings.h"


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


struct IPhysicsSystem
{
	void Update(float fDelta) = 0;

};
