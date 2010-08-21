#pragma once

// What is an entity?
// I define it to be the glue that holds all the useful components that might be present together
// Entities should include (next to) no information themselves - rather metadata.
// Exceptions are:
// - position: various subsystems might have their own idea of position, but the entity position can unify
//             physics, sound, rendering, they all use positions, but all or none may be present
// - just that?


#define PN_ENTITY_NAME_LENGTH 32


// For now, assume that proxies are owned by their entities
// In future though, perhaps proxy sharing will make sense


// Maybe this actually isn't pure virtual. Maybe it calls systems to retrive data and so has a simple implementation.
// COuld be either way, possibly compile switched.

struct IEntity
{
	virtual EntityId GetId() const = 0;

	virtual const char * GetName() const = 0;                      // May return empty string, never NULL
	virtual void SetName(const char * sName) = 0;                  // Up to PN_ENTITY_NAME_LENGTH - 1 bytes plus null terminator, or NULL

//	virtual const IPhysics * GetPhysics() const = 0;
//	virtual IPhysics * GetPhysics() = 0;
//	virtual void SetPhysics(IPhysics *pPhysics) = 0;

//	virtual const IRender * GetRender() const = 0;
//	virtual IRender * GetRender() = 0;
//	virtual void SetRender(IRender *pRender) = 0;

//	virtual Vec2 GetPosition() const = 0;
//	virtual void SetPosition(Vec2 vPos) = 0;

  // Bitfield keeping track of which of these it has
  // Avoid keeping all the pointers!
};
