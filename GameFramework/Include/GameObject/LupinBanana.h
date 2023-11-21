#pragma once

#include "GameObject.h"

class CLupinBanana :
    public CGameObject
{
	friend class CScene;

protected:
	CLupinBanana();
	CLupinBanana(const CLupinBanana& Obj);
	virtual ~CLupinBanana();

private:
	Vector2	m_Dir;
	float	m_Distance;
	float	m_Damage;

public:
	void SetDamage(float Damage)
	{
		m_Damage = Damage;
	}

	void SetDistance(float Dist)
	{
		m_Distance = Dist;
	}

	void SetDir(const Vector2 Dir)
	{
		m_Dir = Dir;
	}

	void SetDir(float x, float y)
	{
		m_Dir = Vector2(x, y);
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