#pragma once

// Physics proxy interface

#include "Definitions.h"

#include "Vec2.h"

struct SPhysicsDescription
{
	bool bActive;       // Am I affected by world physics?
	bool bCollidable;   // Can things collide with me?
	float fDensity;     // My density
	float fMass;        // My mass
	float fRadius;	     // A bounding radius
	Vec2 vVelocity;    //
	Vec2 vImpulse;	    	// Accumulated impulse requests
};

struct IPhysics
{
	virtual PhysicsType GetType() const = 0;					// Physics type

	virtual const SPhysicsDescription &GetDescription() const = 0;
	virtual void SetDescription(SPhysicsDescription &description) = 0;

	virtual void CustomUpdate() = 0;     // Any customised update code, run before the main physics update pass
};
