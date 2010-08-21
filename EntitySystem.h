#pragma once

// In this implementation, entity pointers can be invalidated by a call to Create()
// However, they shouldn't be stored anyway. Can probably get by with this.

#include "IEntitySystem.h"

#include <vector>

class CEntitySystem : public IEntitySystem
{
public:
	//// IEntitySystem methods
	EntityId Create(const char * sName);
	bool Destroy(EntityId nId);

//	bool Find(const SEntityQuery &query, TEntities &result) const;
	const IEntity * GetEntity(EntityId entityId) const;
	IEntity * GetEntity(EntityId entityId);

	//// New methods
	CEntitySystem(void);
	~CEntitySystem(void);

protected:
	struct SEntity : public IEntity
	{
		EntityId id;

    // Oh, I gave it pointers. That's so damn lazy.
		Vec2 vPos;
		
		char sName[PN_ENTITY_NAME_LENGTH];

		//// IEntity methods

		EntityId GetId() const { return id; }

		const char * GetName() const { return sName; }
		void SetName(const char * _sName);

//		const IPhysics * GetPhysics() const { return pPhysics; }
//		IPhysics * GetPhysics() { return pPhysics; }
//		void SetPhysics(IPhysics *_pPhysics);

//		const IRender * GetRender() const { return pRender; }
//		IRender * GetRender() { return pRender; }
//		void SetRender(IRender *_pRender);

		Vec2 GetPosition() const { return vPos; }
		void SetPosition(Vec2 _vPos) { vPos = _vPos; }

		//// New methods

		SEntity(EntityId _id) : 
			id(_id)
 			{	sName[0] = '\n'; }
	};

	typedef std::vector<SEntity> TCESEntities;
	TCESEntities m_Entities;
};