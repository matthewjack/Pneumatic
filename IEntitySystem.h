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

#include <vector>

typedef std::vector <EntityId> TEntities;


// Very high level type description
// This does not define the type of each component proxy

// Perhaps there are some basic checks that could be applied though - e.g. pneumata always have physics

enum EEntityType
{
	eET_Invalid = 0,
	eET_Pneumata,
	eET_Static,
	eET_Dynamic,

};



// A fairly powerful search grab-bag
// Yes, it's possible to create nonsense queries, but it should assert
// Maybe this doesn't actually belong in the entity system itself, we'll see
struct SEntityQuery
{
	PhysicsType physicsType;              // If set, must be this type
	PersonalityType personalityType;      // If set, must be this type
	RenderType renderType;                // If set, must be this type
	
	Vec2 vTLBound,vBRBound;               // Set either or both to set 2D world bounds
	
	Vec2 vCentre;                         // Set to give a focal point for the query. Always use with maxRadius.
	float maxRadius;                      // Set to exclude entities further away from vCentre than this. Always use with vCentre.

	Vec2 vSortCentre;                     // Sort the results by distance from this point
};



struct IEntitySystem : public ISystem
{
	/// ISystem interface
	SErrorDescriptor UnitTest(ILogSystem *pLog);         // Giving a logger is optional

	/// New methods
	virtual ~IEntitySystem() {};

	virtual EntityId Create(EEntityType eType, const char * sName = NULL) = 0;  // Create a new, empty entity of this type
	virtual bool Destroy(EntityId nId) = 0;              // Cleanup and destroy an existing entity. Returns false iff no such id.
	virtual TEntities & Find(const SEntityQuery &query) const = 0; 
};
