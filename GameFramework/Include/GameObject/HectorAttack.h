#pragma once

#include "GameObject.h"

class CHectorAttack :
    public CGameObject
{
	friend class CScene;

protected:
	CHectorAttack();
	CHectorAttack(const CHectorAttack& Obj);
	virtual ~CHectorAttack();

private:
	float	m_Damage;
	int		m_Dir;

public:
	void SetDamage(float Damage)
	{
		m_Damage = Damage;
	}

	void SetDir(int Dir)
	{
		m_Dir = Dir;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void AttackEnd();

private:
	void Attack0();
	void Attack1();
	void Attack2();

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};

