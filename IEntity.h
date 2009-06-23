
#define PN_ENTITY_NAME_LENGTH 32


// For now, assume that proxies are owned by their entities
// In future though, perhaps proxiy sharing will make sense


struct IEntity
{
		virtual EntityId GetId() const = 0;

		virtual const char * GetName() const = 0;                      // May return empty string, never NULL
		virtual void SetName(const char * sName) = 0;                  // Up to PN_ENTITY_NAME_LENGTH - 1 bytes plus null terminator, or NULL

		virtual const IPhysics * GetPhysics() const = 0;
		virtual IPhysics * GetPhysics() = 0;
		virtual void SetPhysics(IPhysics *pPhysics) = 0;

		virtual const IPersonality * GetPersonality() const = 0;
		virtual IPersonality * GetPersonality() = 0;
		virtual void SetPersonality(IPersonality *pPersonality) = 0;

		virtual const IRender * GetRender() const = 0;
		virtual IRender * GetRender() = 0;
		virtual void SetRender(IRender *pRender) = 0;

		virtual Vec2 GetPosition() const = 0;
		virtual void SetPosition(Vec2 vPos) = 0;
};
