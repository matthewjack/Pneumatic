#pragma once

#include "Settings.h"

struct IPhysicsSystem;
struct IRenderSystem;
struct IEntitySystem;
struct IPersonalitySystem;
struct ITimeSystem;
struct ILogSystem;

struct SSystemsTable
{
	IEntitySystem *pEntitySystem;
	IPersonalitySystem *pPersonalitySystem;
	IPhysicsSystem *pPhysicsSystem;
	IRenderSystem *pRenderSystem;
  ITimeSystem *pTimeSystem;
	ILogSystem *pLogSystem;
};



class CEnvironment
{
public:
	SSystemsTable sys;



	CEnvironment(void);
	~CEnvironment(void);
};

CEnvironment gEnv;
