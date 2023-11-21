#pragma once

#include "GameObject.h"

class CMeteorRed :
    public CGameObject
{
	friend class CScene;

protected:
	CMeteorRed();
	CMeteorRed(const CMeteorRed& Obj);
	virtual ~CMeteorRed();

private:
	float	m_Damage;

public:
	void SetDamage(float Damage)
	{
		m_Damage = Damage;
	}

	void SetMoveSpeed(float Speed)
	{
		m_MoveSpeed = Speed;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};

