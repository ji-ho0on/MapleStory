#pragma once

#include "Card.h"

class CYellowCard :
    public CCard
{
	friend class CScene;

protected:
	CYellowCard();
	CYellowCard(const CYellowCard& Obj);
	virtual ~CYellowCard();

private:
	ECard_Number	m_HitNumber;
	bool			m_Hit;

public:
	void SetHitNumber(ECard_Number HitNumber)
	{
		m_HitNumber = HitNumber;
	}

public:
	ECard_Number GetHitNumber()	const
	{
		return m_HitNumber;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void CardHitEnd();
};

