#pragma once

#include "Scene.h"

struct MeteorInfo
{
	bool	Create;
	float	PosX;
};

class CTheSeed50F :
    public CScene
{
	friend class CSceneManager;

protected:
	CTheSeed50F();
	virtual ~CTheSeed50F();

private:
	float		m_MeteorRegenTime;
	MeteorInfo	m_MeteorInfo[21];

	CSharedPtr<class CDorothy>		m_Dorothy;
	CSharedPtr<class CWidgetWindow>	m_DorothyHP;

public:
	bool Init();
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);


private:
	void CreateMeteor();

public:
	void DorothyDie();
	class CDorothy* GetDorothy();

private:
	void CreateAnimationSequence();
	void PlayerAnimationSequence();
	void PlayerEffectAnimationSequence();
	void MonsterAnimationSequence();
};

