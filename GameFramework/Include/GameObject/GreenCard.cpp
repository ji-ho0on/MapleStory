#include "GreenCard.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"

CGreenCard::CGreenCard()
{
	SetTypeID<CGreenCard>();
}

CGreenCard::CGreenCard(const CGreenCard& Obj) :
	CCard(Obj)
{
}

CGreenCard::~CGreenCard()
{
}

bool CGreenCard::Init()
{
	CCard::Init();

	CreateAnimation();

	AddAnimation("GreenCard1", true, 0.5f);
	AddAnimation("GreenCard2", true, 0.5f);
	AddAnimation("GreenCard3", true, 0.5f);
	AddAnimation("GreenCard4", true, 0.5f);
	AddAnimation("GreenCard5", true, 0.5f);
	AddAnimation("GreenCard6", true, 0.5f);
	AddAnimation("GreenCard7", true, 0.5f);
	AddAnimation("GreenCardHit", false, 0.5f);
	AddAnimation("VioletCard", true, 0.5f);
	AddAnimation("VioletCardHit", false, 0.5f);

	SetEndFunction<CGreenCard>("GreenCardHit", this, &CGreenCard::CardHitEnd);

	SetCardColor(ECard_Color::Green);

	m_HitNumber = ECard_Number::Number1;
	m_Hit = false;

	return true;
}

void CGreenCard::Update(float DeltaTime)
{
	CCard::Update(DeltaTime);

	if (!m_Hit)
	{
		if (m_HitNumber == ECard_Number::Number1)
		{
			switch (GetCardNumber())
			{
			case ECard_Number::Number1:
				ChangeAnimation("GreenCard1");
				break;
			case ECard_Number::Number2:
				ChangeAnimation("GreenCard2");
				break;
			case ECard_Number::Number3:
				ChangeAnimation("GreenCard3");
				break;
			case ECard_Number::Number4:
				ChangeAnimation("GreenCard4");
				break;
			case ECard_Number::Number5:
				ChangeAnimation("GreenCard5");
				break;
			case ECard_Number::Number6:
				ChangeAnimation("GreenCard6");
				break;
			case ECard_Number::Number7:
				ChangeAnimation("GreenCard7");
				break;
			case ECard_Number::Max:
				ChangeAnimation("VioletCard");
				break;
			}
		}

		else if ((int)m_HitNumber > (int)GetCardNumber())
		{
			m_Hit = true;
			ChangeAnimation("GreenCardHit");
		}
	}
}

void CGreenCard::PostUpdate(float DeltaTime)
{
	CCard::PostUpdate(DeltaTime);
}

void CGreenCard::Render(HDC hDC, float DeltaTime)
{
	CCard::Render(hDC, DeltaTime);
}

void CGreenCard::CardHitEnd()
{
	switch (m_HitNumber)
	{
	case ECard_Number::Number1:
		ChangeAnimation("GreenCard1");
		break;
	case ECard_Number::Number2:
		ChangeAnimation("GreenCard2");
		break;
	case ECard_Number::Number3:
		ChangeAnimation("GreenCard3");
		break;
	case ECard_Number::Number4:
		ChangeAnimation("GreenCard4");
		break;
	case ECard_Number::Number5:
		ChangeAnimation("GreenCard5");
		break;
	case ECard_Number::Number6:
		ChangeAnimation("GreenCard6");
		break;
	case ECard_Number::Number7:
		ChangeAnimation("GreenCard7");
		break;
	case ECard_Number::Max:
		ChangeAnimation("VioletCard");
		break;
	}
}