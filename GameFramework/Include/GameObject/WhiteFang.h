#pragma once

#include "Monster.h"

enum class EWhiteFang_Motion
{
	Stand, // 아무것도 아니면 Stand임
	Move,
	Jump,
	Attack,
	Hit,
	Die
};

enum class EWhiteFang_Dir
{
	Left,
	Right,
	Max
};

class CWhiteFang :
    public CMonster
{
	friend class CScene;

protected:
	CWhiteFang();
	CWhiteFang(const CWhiteFang& Obj);
	virtual ~CWhiteFang();

private:
	Vector2	m_Dir;

	std::vector<std::string>	m_vecSequenceKey[2];

	float	m_SelectTime;

	bool	m_MoveMotion;

	bool	m_JumpMotion;
	int		m_JumpCount;


	float	m_BodyDamage;

	bool	m_Attacked;
	float	m_AttackedTime;

	bool	m_AttackState;
	bool	m_Attack;
	float	m_AttackTime;
	int		m_AttackCount;
	
	bool	m_Die;

	int		m_SpawnNumber;

public:
	int	GetSpawnNumber()	const
	{
		return m_SpawnNumber;
	}

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

	void SetSpawnNumber(int SpawnNumber)
	{
		m_SpawnNumber = SpawnNumber;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);

private:
	void Attack();
	void AttackEnd();
	void DieEnd();

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
	void AttackRangeCollisionBegin(CCollider* Src, CCollider* Dest);
	void AttackRangeCollisionEnd(CCollider* Src, CCollider* Dest);
};

