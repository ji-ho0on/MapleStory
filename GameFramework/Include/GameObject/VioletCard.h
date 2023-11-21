#pragma once

#include "Card.h"

class CVioletCard :
    public CCard
{
	friend class CScene;

protected:
	CVioletCard();
	CVioletCard(const CVioletCard& Obj);
	virtual ~CVioletCard();

private:
	ECard_Color		m_HitColor;
	bool			m_Hit;

public:
	void SetHitColor(ECard_Color HitColor)
	{
		m_HitColor = HitColor;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void CardHitEnd();
};

