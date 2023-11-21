#pragma once

#include "Character.h"

struct SkillCoolDownInfo
{
	float	CoolDown;
	bool	CoolDownEnable;
};

class CPlayer :
    public CCharacter
{
	friend class CScene;

protected:
	CPlayer();
	CPlayer(const CPlayer& Obj);
	virtual ~CPlayer();

private:
	int		m_PlayerDir;
	std::vector<std::string>	m_vecSequenceKey[2];

	bool	m_Attack;
	int		m_AttackDamage;

	bool	m_SlashBlust;
	int		m_SlashBlustDamage;

	bool	m_RaisingBlow;
	int		m_RaisingBlowDamage;


	bool	m_Alert;
	float	m_AlertTime;
	float	m_AlertTimeMax;

	bool	m_Attacked;
	float	m_AttackedTime;
	float	m_AttackedTimeMax;

	bool	m_Invincibility; // 무적
	float	m_InvincibilityTime;

	bool	m_UnalbeToMove;	// 피격후 경직
	float	m_UnalbeToMoveTime;

	bool	m_ProneAttack;
	bool	m_Prone;

	bool	m_RopeState;
	bool	m_Rope;
	bool	m_RopeMove;

	bool	m_PotalState;
	bool	m_Potal;

	// KeyState
	bool	m_UpKey;
	bool	m_DownKey;
	bool	m_RightKey;
	bool	m_LeftKey;
	bool	m_JumpKey;

	bool	m_PickUpKey;

	// 더블점프
	bool	m_DoubleJump;
	int		m_JumpCount;	// 최대 2번까지 점프가 가능하고 땅에 착지하면 0으로 초기화

	std::vector<SkillCoolDownInfo>	m_vecCoolDown;

	int		m_HP;
	int		m_HPMax;

	int		m_MP;
	int		m_MPMax;

	int		m_Level;
	int		m_EXP;
	int		m_EXPMax[10];

	CSharedPtr<class CWidgetComponent>	m_NameBar;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);
	virtual void Jump();

public:
	bool GetSlashBlust()	const
	{
		return m_SlashBlust;
	}

	bool GetRaisingBlow()	const
	{
		return m_RaisingBlow;
	}

	int GetHP()	const
	{
		return m_HP;
	}

	int GetHPMax()	const
	{
		return m_HPMax;
	}

	int GetMP()	const
	{
		return m_MP;
	}

	int GetMPMax()	const
	{
		return m_MPMax;
	}

	void AddEXP(int EXP)
	{
		m_EXP += EXP;
	}

	int GetEXP()	const
	{
		return m_EXP;
	}

	int GetEXPMax()	const
	{
		return m_EXPMax[m_Level - 1];
	}

	int GetLevel()	const
	{
		return m_Level;
	}

	bool GetPickUpKey()	const
	{
		return m_PickUpKey;
	}

	bool GetUpKey()	const
	{
		return m_UpKey;
	}

	int	GetPlayerDir()	const
	{
		return m_PlayerDir;
	}

	bool GetRope()	const
	{
		return m_Rope;
	}

	bool GetPotal()	const
	{
		return m_Potal;
	}

public:
	void SetHP(int HP)
	{
		m_HP = HP;
	}

	void SetHPMax(int HPMax)
	{
		m_HPMax = HPMax;
	}

	void SetMP(int MP)
	{
		m_MP = MP;
	}

	void SetMPMax(int MPMax)
	{
		m_MPMax = MPMax;
	}

	void SetLevel(int Level)
	{
		m_Level = Level;
	}

	void SetEXP(int EXP)
	{
		m_EXP = EXP;
	}


private:
	void MoveUp();
	void MoveUpCancel();
	void MoveDown();
	void ProneCancel();
	void MoveRight();
	void MoveRightCancel();
	void MoveLeft();
	void MoveLeftCancel();
	void Fire();
	void JumpKey();
	void JumpKeyUp();
	void SlashBlust();
	void RasingBlow();
	void PickUp();
	void PickUpCancel();

private:
	void AttackEnd();
	void Attack();

	void SlashBlustAttack();
	void SlashBlustAttackEnd();

	void RaisingBlowAttack();
	void RaisingBlowAttackEnd();

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
	void AttackCollisionBegin(CCollider* Src, CCollider* Dest);
	void AttackCollisionEnd(CCollider* Src, CCollider* Dest);
	void SlashBlustCollisionBegin(CCollider* Src, CCollider* Dest);
	void SlashBlustCollisionEnd(CCollider* Src, CCollider* Dest);
	void RaisingBlowCollisionBegin(CCollider* Src, CCollider* Dest);
	void RaisingBlowCollisionEnd(CCollider* Src, CCollider* Dest);
};

