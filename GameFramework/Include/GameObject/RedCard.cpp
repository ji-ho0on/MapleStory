#include "RedCard.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"

CRedCard::CRedCard()
{
	SetTypeID<CRedCard>();
}

CRedCard::CRedCard(const CRedCard& Obj) :
	CCard(Obj)
{
}

CRedCard::~CRedCard()
{
}

bool CRedCard::Init()
{
	CCard::Init();

	CreateAnimation();

	AddAnimation("RedCard1", true, 0.5f);
	AddAnimation("RedCard2", true, 0.5f);
	AddAnimation("RedCard3", true, 0.5f);
	AddAnimation("RedCard4", true, 0.5f);
	AddAnimation("RedCard5", true, 0.5f);
	AddAnimation("RedCard6", true, 0.5f);
	AddAnimation("RedCard7", true, 0.5f);
	AddAnimation("RedCardHit", false, 0.5f);
	AddAnimation("VioletCard", true, 0.5f);
	AddAnimation("VioletCardHit", false, 0.5f);

	SetEndFunction<CRedCard>("RedCardHit", this, &CRedCard::CardHitEnd);

	SetCardColor(ECard_Color::Red);

	m_HitNumber = ECard_Number::Number1;
	m_Hit = false;

	SetCardColor(ECard_Color::Red);

	return true;
}

void CRedCard::Update(float DeltaTime)
{
	CCard::Update(DeltaTime);

	if (!m_Hit)
	{
		if (m_HitNumber == ECard_Number::Number1)
		{
			switch (GetCardNumber())
			{
			case ECard_Number::Number1:
				ChangeAnimation("RedCard1");
				break;
			case ECard_Number::Number2:
				ChangeAnimation("RedCard2");
				break;
			case ECard_Number::Number3:
				ChangeAnimation("RedCard3");
				break;
			case ECard_Number::Number4:
				ChangeAnimation("RedCard4");
				break;
			case ECard_Number::Number5:
				ChangeAnimation("RedCard5");
				break;
			case ECard_Number::Number6:
				ChangeAnimation("RedCard6");
				break;
			case ECard_Number::Number7:
				ChangeAnimation("RedCard7");
				break;
			case ECard_Number::Max:
				ChangeAnimation("VioletCard");
				break;
			}
		}

		else if ((int)m_HitNumber > (int)GetCardNumber())
		{
			m_Hit = true;
			ChangeAnimation("RedCardHit");
		}
	}
}

void CRedCard::PostUpdate(float DeltaTime)
{
	CCard::PostUpdate(DeltaTime);
}

void CRedCard::Render(HDC hDC, float DeltaTime)
{
	CCard::Render(hDC, DeltaTime);
}

void CRedCard::CardHitEnd()
{
	switch (m_HitNumber)
	{
	case ECard_Number::Number1:
		ChangeAnimation("RedCard1");
		break;
	case ECard_Number::Number2:
		ChangeAnimation("RedCard2");
		break;
	case ECard_Number::Number3:
		ChangeAnimation("RedCard3");
		break;
	case ECard_Number::Number4:
		ChangeAnimation("RedCard4");
		break;
	case ECard_Number::Number5:
		ChangeAnimation("RedCard5");
		break;
	case ECard_Number::Number6:
		ChangeAnimation("RedCard6");
		break;
	case ECard_Number::Number7:
		ChangeAnimation("RedCard7");
		break;
	case ECard_Number::Max:
		ChangeAnimation("VioletCard");
		break;
	}
}