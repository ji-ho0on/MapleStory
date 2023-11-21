#pragma once

#include "GameObject.h"

class CAreaWarning :
    public CGameObject
{
	friend class CScene;

protected:
	CAreaWarning();
	CAreaWarning(const CAreaWarning& Obj);
	virtual ~CAreaWarning();

private:
	float	m_Damage;

public:
	void SetDamage(float Damage)
	{
		m_Damage = Damage;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void AreaWarningEnd();

private:
	void Attack();
	void AttackEnd();

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};

