#pragma once

#include "Scene.h"

class CTheSeed7F :
    public CScene
{
	friend class CSceneManager;

protected:
	CTheSeed7F();
	virtual ~CTheSeed7F();

public:
	bool Init();
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);

private:
	void CreateAnimationSequence();
	void PlayerAnimationSequence();
	void PlayerEffectAnimationSequence();
	void MonsterAnimationSequence();

private:
	void Clear(CCollider* Src, CCollider* Dest);
};

