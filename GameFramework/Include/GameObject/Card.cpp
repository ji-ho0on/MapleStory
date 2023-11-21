#include "Card.h"
#include "../Collision/ColliderBox.h"
#include "../GameObject/Player.h"
#include "../Scene/TheSeed2F.h"

CCard::CCard()
{
	SetTypeID<CCard>();
}

CCard::CCard(const CCard& Obj) :
	CGameObject(Obj)
{
}

CCard::~CCard()
{
}

bool CCard::Init()
{
	CColliderBox* CardCollider = AddCollider<CColliderBox>("CardCollider");
	CardCollider->SetExtent(30.f, 1.f);
	CardCollider->SetCollisionProfile("CardInteraction");

	CardCollider->SetCollisionBeginFunction<CCard>(this, &CCard::CollisionBegin);
	CardCollider->SetCollisionEndFunction<CCard>(this, &CCard::CollisionEnd);

	CardCollider->SetEnable(false);

	m_CardInteractionState = false;

	return true;
}

void CCard::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	CColliderBox* CardCollider = (CColliderBox*)FindCollider("CardCollider");

	if (!m_Owner)
		CardCollider->SetEnable(true);

	else
		CardCollider->SetEnable(false);
}

void CCard::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	if (m_CardInteractionState)
	{
		CPlayer* Player = (CPlayer*)m_Scene->GetPlayer();

		if (Player->GetUpKey())
		{
			CTheSeed2F* Scene = (CTheSeed2F*)m_Scene;

			Scene->ChangeCard(this);
		}
	}
}

void CCard::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CCard::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	m_CardInteractionState = true;
}

void CCard::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	m_CardInteractionState = false;
}
