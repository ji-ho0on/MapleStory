#pragma once

#include "Character.h"

class CMonster :
    public CCharacter
{
	friend class CScene;

protected:
	CMonster();
	CMonster(const CMonster& Obj);
	virtual ~CMonster();

protected:
	int		m_HP;
	int		m_HPMax;
	int		m_EXP;

public:
	int	GetMaxHP()	const
	{
		return m_HPMax;
	}

	int GetHP()	const
	{
		return m_HP;
	}

public:
	void SetMaxHP(int HPMax)
	{
		m_HPMax = HPMax;
	}

	void SetHP(int HP)
	{
		m_HP = HP;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);
};

