#pragma once

// Entity system is responsible for managing these little blobs of glue and their unique ids
// It should also provide position-based search functionality and type-based filtering
// The individual systems shoudl provide their own kinds of domain-spcific search (e.g. for volume)
// Perhaps results from one can be fed into another.
// I fear that iterators are required to do this properly.

#include "Settings.h"
#include "Definitions.h"
#include "Vec2.h"
#include "ISystem.h"
#include "IEntity.h"

#include <vector>

typedef std::vector <EntityId> TEntities;


// No such thing as an entity "type" - just matching against all the components an entity might have
// Hence any entity might become any other type of entity dynamically by adding components. (Is this wise?)


struct IEntitySystem : public ISystem
{
	//// ISystem interface
	SErrorDescriptor UnitTest(ILogSystem *pLog);         // Giving a logger is optional

	//// New methods
	virtual ~IEntitySystem() {};

	virtual EntityId Create(const char * sName = NULL) = 0;  // Create a new, empty entity of this type
	virtual bool Destroy(EntityId nId) = 0;              // Cleanup and destroy an existing entity. Returns false iff no such id.

//	virtual bool Find(const SEntityQuery &query, TEntities &result) const = 0; 
	virtual const IEntity * GetEntity(EntityId entityId) const = 0;
	virtual IEntity * GetEntity(EntityId entityId) = 0;
};
