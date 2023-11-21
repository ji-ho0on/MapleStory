#include "BlueCard.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"

CBlueCard::CBlueCard()
{
	SetTypeID<CBlueCard>();
}

CBlueCard::CBlueCard(const CBlueCard& Obj) :
	CCard(Obj)
{
}

CBlueCard::~CBlueCard()
{
}

bool CBlueCard::Init()
{
	CCard::Init();

	CreateAnimation();

	AddAnimation("BlueCard1", true, 0.5f);
	AddAnimation("BlueCard2", true, 0.5f);
	AddAnimation("BlueCard3", true, 0.5f);
	AddAnimation("BlueCard4", true, 0.5f);
	AddAnimation("BlueCard5", true, 0.5f);
	AddAnimation("BlueCard6", true, 0.5f);
	AddAnimation("BlueCard7", true, 0.5f);
	AddAnimation("BlueCardHit", false, 0.5f);
	AddAnimation("VioletCard", true, 0.5f);
	AddAnimation("VioletCardHit", false, 0.5f);

	SetEndFunction<CBlueCard>("BlueCardHit", this, &CBlueCard::CardHitEnd);

	SetCardColor(ECard_Color::Blue);

	m_HitNumber = ECard_Number::Number1;
	m_Hit = false;

	return true;
}

void CBlueCard::Update(float DeltaTime)
{
	CCard::Update(DeltaTime);

	if (!m_Hit)
	{
		if (m_HitNumber == ECard_Number::Number1)
		{
			switch (GetCardNumber())
			{
			case ECard_Number::Number1:
				ChangeAnimation("BlueCard1");
				break;
			case ECard_Number::Number2:
				ChangeAnimation("BlueCard2");
				break;
			case ECard_Number::Number3:
				ChangeAnimation("BlueCard3");
				break;
			case ECard_Number::Number4:
				ChangeAnimation("BlueCard4");
				break;
			case ECard_Number::Number5:
				ChangeAnimation("BlueCard5");
				break;
			case ECard_Number::Number6:
				ChangeAnimation("BlueCard6");
				break;
			case ECard_Number::Number7:
				ChangeAnimation("BlueCard7");
				break;
			case ECard_Number::Max:
				ChangeAnimation("VioletCard");
				break;
			}
		}

		else if ((int)m_HitNumber > (int)GetCardNumber())
		{
			m_Hit = true;
			ChangeAnimation("BlueCardHit");
		}
	}
}

void CBlueCard::PostUpdate(float DeltaTime)
{
	CCard::PostUpdate(DeltaTime);
}

void CBlueCard::Render(HDC hDC, float DeltaTime)
{
	CCard::Render(hDC, DeltaTime);
}

void CBlueCard::CardHitEnd()
{
	switch (m_HitNumber)
	{
	case ECard_Number::Number1:
		ChangeAnimation("BlueCard1");
		break;
	case ECard_Number::Number2:
		ChangeAnimation("BlueCard2");
		break;
	case ECard_Number::Number3:
		ChangeAnimation("BlueCard3");
		break;
	case ECard_Number::Number4:
		ChangeAnimation("BlueCard4");
		break;
	case ECard_Number::Number5:
		ChangeAnimation("BlueCard5");
		break;
	case ECard_Number::Number6:
		ChangeAnimation("BlueCard6");
		break;
	case ECard_Number::Number7:
		ChangeAnimation("BlueCard7");
		break;
	case ECard_Number::Max:
		ChangeAnimation("VioletCard");
		break;
	}
}