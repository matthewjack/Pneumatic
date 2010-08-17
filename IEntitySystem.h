#pragma once

// What is an entity?
// I define it to be the glue that holds all the useful components that might be present together
// Position seems somehow special. Lots of things care about positions and positions without physics can make sense.
// Entities include static geometry, Pneumata, some interface elements? 

// Hang on! I must use a physics engine - and then where will my positions come from?


#include "Settings.h"
#include "Definitions.h"
#include "Vec2.h"
#include "ISystem.h"
#include "IEntity.h"
#include "IPhysics.h"
#include "IPersonalitySystem.h"

#include <vector>

typedef std::vector <EntityId> TEntities;


// Very high level type description
// This does not define the type of each component proxy

// Perhaps there are some basic checks that could be applied though - e.g. pneumata always have physics

enum EEntityType
{
	eET_Invalid = 0,                              // No entity, or empty.. check semantics
	eET_Pneumata,
	eET_Static,
	eET_Dynamic,

};



// A fairly powerful search grab-bag
// Yes, it's possible to create nonsense queries, but it should assert
// Maybe this doesn't actually belong in the entity system itself, we'll see
// It's ugly
// Specifying kinds of resutls _might_ be useful - I'm thinking bare pointers avoiding the indirection

struct SEntityQuery
{
	EPhysicsType physicsType;              // If set, must be this type
	EPersonalityType personalityType;      // If set, must be this type
	ERenderType renderType;                // If set, must be this type
	
	Vec2 vTLBound,vBRBound;               // Set either or both to set 2D world bounds
	
	Vec2 vCentre;                         // Set to give a focal point for the query. Always use with maxRadius.
	float maxRadius;                      // Set to exclude entities further away from vCentre than this. Always use with vCentre.

	Vec2 vSortCentre;                     // Sort the results by distance from this point

	SEntityQuery()
		: physicsType(EPhysicsType(0))
		, personalityType(EPersonalityType(0))
		, renderType(ERenderType(0))
		, maxRadius(.0f)
	{}
};



struct IEntitySystem : public ISystem
{
	//// ISystem interface
	SErrorDescriptor UnitTest(ILogSystem *pLog);         // Giving a logger is optional

	//// New methods
	virtual ~IEntitySystem() {};

	virtual EntityId Create(EEntityType eType, const char * sName = NULL) = 0;  // Create a new, empty entity of this type
	virtual bool Destroy(EntityId nId) = 0;              // Cleanup and destroy an existing entity. Returns false iff no such id.

	virtual bool Find(const SEntityQuery &query, TEntities &result) const = 0; 
	virtual const IEntity * GetEntity(EntityId entityId) const = 0;
	virtual IEntity * GetEntity(EntityId entityId) = 0;
};
