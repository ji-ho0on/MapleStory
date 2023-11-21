#include "VioletCard.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"

CVioletCard::CVioletCard()
{
	SetTypeID<CVioletCard>();
}

CVioletCard::CVioletCard(const CVioletCard& Obj) :
	CCard(Obj)
{
}

CVioletCard::~CVioletCard()
{
}

bool CVioletCard::Init()
{
	CCard::Init();

	CreateAnimation();

	AddAnimation("VioletCard", true, 0.5f);
	AddAnimation("VioletCardHit", false, 0.5f);

	SetEndFunction<CVioletCard>("VioletCardHit", this, &CVioletCard::CardHitEnd);

	SetCardColor(ECard_Color::Violet);

	m_Hit = false;

	return true;
}

void CVioletCard::Update(float DeltaTime)
{
	CCard::Update(DeltaTime);

	if (!m_Hit)
	{
		if (m_HitColor != ECard_Color::Violet)
		{
			ChangeAnimation("VioletCard");
		}

		else
		{
			m_Hit = true;
			ChangeAnimation("VioletCardHit");
		}
	}
}

void CVioletCard::PostUpdate(float DeltaTime)
{
	CCard::PostUpdate(DeltaTime);
}

void CVioletCard::Render(HDC hDC, float DeltaTime)
{
	CCard::Render(hDC, DeltaTime);
}

void CVioletCard::CardHitEnd()
{
	ChangeAnimation("VioletCard");
}