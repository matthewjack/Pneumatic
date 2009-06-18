#pragma once

#include "Settings.h"
#include "Definitions.h"
#include "Vec2.h"

struct IPhysics;
struct IPersonality;
struct IRender;

struct IEntity
{
		IPhysics * GetPhysics() = 0;
		void SetPhysics(IPhysics *pPhysics) = 0;

		IPersonality * GetPersonality() = 0;
		void SetPersonality(IPersonality *pPersonality) = 0;

		IRender * GetRender() = 0;
		void SetRender(IRender *pRender) = 0;

		Vec2 GetPosition() const = 0;
		void SetPosition(Vec2 vPos);
}

// A fairly powerful search grab-bag
// Yes, it's possible to create nonsense queries, but it should assert
struct SEntityQuery
{
	PhysicsType physicsType;              // If set, must be this type
	PersonalityType personalityType;      // If set, must be this type
	RenderType renderType;                // If set, must be this type
	
	Vec2 vTLBound,vBRBound;               // Set either or both to set 2D world bounds
	
	Vec2 vCentre;                         // Set to give a focal point for the query. Always use with maxRadius.
	float maxRadius;                      // Set to exclude entities further away from vCentre than this. Always use with vCentre.

	Vec2 vSortCentre;                     // Sort the results by distance from this point
}



struct IEntitySystem : public ISystem
{
	virtual EntityId Register(IEntity *pEntity) = 0;
	virtual bool Deregister(EntityId nId) = 0;
	virtual TEntities & Find(const SEntityQuery &query);

};
