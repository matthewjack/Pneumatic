#pragma once

#include "Settings.h"

enum EPersonalityType
{
	ePerT_None = 0,
};

struct IPersonality
{
};

struct IPersonalitySystem
{
	void Update(float fDelta);
};
