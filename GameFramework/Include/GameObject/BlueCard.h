#pragma once

#include "Card.h"

class CBlueCard :
    public CCard
{
	friend class CScene;

protected:
	CBlueCard();
	CBlueCard(const CBlueCard& Obj);
	virtual ~CBlueCard();

private:
	ECard_Number			m_HitNumber;
	bool					m_Hit;

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

