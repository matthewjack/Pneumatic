// Implementation 

// Apply salts and buffer reuse later

#include "EntitySystem.h"
#include "IPhysics.h"
#include "IPersonalitySystem.h"
#include "IRenderSystem.h"

//#include physics etc proxies for delete



void CEntitySystem::SEntity::SetName(const char * _sName) 
{
	if (_sName && _sName[0])
	{
		strncpy(sName, _sName, PN_ENTITY_NAME_LENGTH);
		sName[PN_ENTITY_NAME_LENGTH-1] = '\0';
		// Could re length warn here
	}
	else
	{
		sName[0] = '\0';
		// And here
	}
}

void CEntitySystem::SEntity::SetPhysics(IPhysics *_pPhysics) { delete(pPhysics); pPhysics = _pPhysics; }
void CEntitySystem::SEntity::SetPersonality(IPersonality *_pPersonality) { delete(pPersonality); pPersonality = _pPersonality; }
void CEntitySystem::SEntity::SetRender(IRender *_pRender) { delete(pRender); pRender = _pRender; }

EntityId CEntitySystem::Create(EEntityType eType, const char * sName)
{
	EntityId newID = (EntityId) m_Entities.size();
	SEntity entity(newID,eET_Invalid);
	entity.SetName(sName);
	m_Entities.push_back(entity);
	return newID;
}

bool CEntitySystem::Destroy(EntityId nId)
{
	return true;
}

bool CEntitySystem::Find(const SEntityQuery &query, TEntities &result) const
{
	return true;
}

CEntitySystem::CEntitySystem(void)
{
	SEntity invalid(0,eET_Invalid);
	m_Entities.push_back(invalid);
}

CEntitySystem::~CEntitySystem(void)
{
}


