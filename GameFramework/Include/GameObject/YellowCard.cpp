#include "YellowCard.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"

CYellowCard::CYellowCard()
{
	SetTypeID<CYellowCard>();
}

CYellowCard::CYellowCard(const CYellowCard& Obj) :
	CCard(Obj)
{
}

CYellowCard::~CYellowCard()
{
}

bool CYellowCard::Init()
{
	CCard::Init();

	CreateAnimation();

	AddAnimation("YellowCard1", true, 0.5f);
	AddAnimation("YellowCard2", true, 0.5f);
	AddAnimation("YellowCard3", true, 0.5f);
	AddAnimation("YellowCard4", true, 0.5f);
	AddAnimation("YellowCard5", true, 0.5f);
	AddAnimation("YellowCard6", true, 0.5f);
	AddAnimation("YellowCard7", true, 0.5f);
	AddAnimation("YellowCardHit", false, 0.5f);
	AddAnimation("VioletCard", true, 0.5f);
	AddAnimation("VioletCardHit", false, 0.5f);

	SetEndFunction<CYellowCard>("YellowCardHit", this, &CYellowCard::CardHitEnd);

	SetCardColor(ECard_Color::Yellow);

	m_HitNumber = ECard_Number::Number1;
	m_Hit = false;

	SetCardColor(ECard_Color::Yellow);

	return true;
}

void CYellowCard::Update(float DeltaTime)
{
	CCard::Update(DeltaTime);

	if (!m_Hit)
	{
		if (m_HitNumber == ECard_Number::Number1)
		{
			switch (GetCardNumber())
			{
			case ECard_Number::Number1:
				ChangeAnimation("YellowCard1");
				break;
			case ECard_Number::Number2:
				ChangeAnimation("YellowCard2");
				break;
			case ECard_Number::Number3:
				ChangeAnimation("YellowCard3");
				break;
			case ECard_Number::Number4:
				ChangeAnimation("YellowCard4");
				break;
			case ECard_Number::Number5:
				ChangeAnimation("YellowCard5");
				break;
			case ECard_Number::Number6:
				ChangeAnimation("YellowCard6");
				break;
			case ECard_Number::Number7:
				ChangeAnimation("YellowCard7");
				break;
			case ECard_Number::Max:
				ChangeAnimation("VioletCard");
				break;
			}
		}

		else if ((int)m_HitNumber > (int)GetCardNumber())
		{
			m_Hit = true;
			ChangeAnimation("YellowCardHit");
		}
	}
}

void CYellowCard::PostUpdate(float DeltaTime)
{
	CCard::PostUpdate(DeltaTime);
}

void CYellowCard::Render(HDC hDC, float DeltaTime)
{
	CCard::Render(hDC, DeltaTime);
}

void CYellowCard::CardHitEnd()
{
	switch (m_HitNumber)
	{
	case ECard_Number::Number1:
		ChangeAnimation("YellowCard1");
		break;
	case ECard_Number::Number2:
		ChangeAnimation("YellowCard2");
		break;
	case ECard_Number::Number3:
		ChangeAnimation("YellowCard3");
		break;
	case ECard_Number::Number4:
		ChangeAnimation("YellowCard4");
		break;
	case ECard_Number::Number5:
		ChangeAnimation("YellowCard5");
		break;
	case ECard_Number::Number6:
		ChangeAnimation("YellowCard6");
		break;
	case ECard_Number::Number7:
		ChangeAnimation("YellowCard7");
		break;
	case ECard_Number::Max:
		ChangeAnimation("VioletCard");
		break;
	}
}