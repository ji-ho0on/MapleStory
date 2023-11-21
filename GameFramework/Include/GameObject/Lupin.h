#pragma once

#include "Monster.h"

class CLupin :
    public CMonster
{
	friend class CScene;

protected:
	CLupin();
	CLupin(const CLupin& Obj);
	virtual ~CLupin();

private:
	Vector2	m_Dir;
	float	m_FireTime;
	bool	m_Fire;

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

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void Attack();
	void AttackEnd();
};

