#pragma once

#include "Monster.h"

enum class EDorothy_Attack_Type
{
	Attack,
	Skill1,
	Skill2,
	Max
};

struct AreaWarningInfo
{
	bool	Create;
	float	PosX;
};

class CDorothy :
    public CMonster
{
	friend class CScene;

protected:
	CDorothy();
	CDorothy(const CDorothy& Obj);
	virtual ~CDorothy();

private:
	Vector2	m_Dir;

	float	m_SelectTime;

	int		m_BodyDamage;

	float	m_AttackTime;
	bool	m_Attack;
	bool	m_DorothyAttack;
	int		m_AttackCount;

	bool	m_Skill1;

	bool	m_Skill2;
	float	m_Skill2Damage;

	AreaWarningInfo	m_AreaInfo[4];

public:
	const Vector2& GetDir()	const
	{
		return m_Dir;
	}

	void SetDir(const Vector2 Dir)
	{
		m_Dir = Dir;
	}

	void SetDir(float x, float y)
	{
		m_Dir = Vector2(x, y);
	}

	void SetWarningArea(int Index, bool Create)
	{
		m_AreaInfo[Index].Create = Create;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);

private:
	void CreateAreaWarning();
	void CreateEnergyBall();

private:
	void Attack();
	void AttackEnd();
	void Skill1End();
	void Skill2();
	void Skill2AttackEnd();
	void Skill2End();
	void DieEnd();

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
	void Skill2CollisionBegin(CCollider* Src, CCollider* Dest);
	void Skill2CollisionEnd(CCollider* Src, CCollider* Dest);
};

