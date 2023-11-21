#pragma once

#include "GameObject.h"

enum class ECard_Color
{
	Red,
	Blue,
	Green,
	Yellow,
	Violet,
	Max
};

enum class ECard_Number
{
	Number1,
	Number2,
	Number3,
	Number4,
	Number5,
	Number6,
	Number7,
	Max
};

class CCard :
    public CGameObject
{
	friend class CScene;

protected:
	CCard();
	CCard(const CCard& Obj);
	virtual ~CCard();

private:
	ECard_Color		m_CardColor;
	ECard_Number	m_CardNumber;
	CGameObject*	m_Owner;

	bool			m_CardInteractionState;

public:
	void SetOwner(CGameObject* Owner)
	{
		m_Owner = Owner;
	}

	void SetCardColor(ECard_Color Color)
	{
		m_CardColor = Color;
	}

	void SetCardNumber(ECard_Number Number)
	{
		m_CardNumber = Number;
	}

	ECard_Color GetCardColor()	const
	{
		return m_CardColor;
	}

	ECard_Number GetCardNumber()	const
	{
		return m_CardNumber;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void CollisionBegin(class CCollider* Src, class CCollider* Dest);
	void CollisionEnd(class CCollider* Src, class CCollider* Dest);
};

