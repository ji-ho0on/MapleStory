#include "SealBreakCard.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "Player.h"
#include "../Scene/TheSeed2F.h"

CSealBreakCard::CSealBreakCard()
{
	SetTypeID<CSealBreakCard>();
}

CSealBreakCard::CSealBreakCard(const CSealBreakCard& Obj) :
	CGameObject(Obj)
{
}

CSealBreakCard::~CSealBreakCard()
{
}

bool CSealBreakCard::Init()
{

	CreateAnimation();

	AddAnimation("SealBreakCard");
	AddAnimation("SealBreakCardGround");

	CColliderBox* Box = AddCollider<CColliderBox>("SealBreakCard");
	Box->SetExtent(36.f, 36.f);
	Box->SetOffset(0.f, -18.f);
	Box->SetCollisionProfile("Item");

	Box->SetCollisionBeginFunction<CSealBreakCard>(this, &CSealBreakCard::CollisionBegin);
	Box->SetCollisionEndFunction<CSealBreakCard>(this, &CSealBreakCard::CollisionEnd);

	m_PickUpState = false;
	m_ItemOwner = nullptr;

	SetPhysicsSimulate(true);
	SetJumpVelocity(30.f);

	Jump();

	return true;
}

void CSealBreakCard::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_Ground)
	{
		ChangeAnimation("SealBreakCardGround");
	}

	if (m_PickUpState)
	{
		if (m_ItemOwner->GetPickUpKey())
		{
			SetActive(false);
			CTheSeed2F* Scene = (CTheSeed2F*)m_Scene;

			Scene->SelectCard();
		}
	}
}

void CSealBreakCard::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CSealBreakCard::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CSealBreakCard::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	m_PickUpState = true;

	m_ItemOwner = (CPlayer*)Dest->GetOwner();
}

void CSealBreakCard::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	m_PickUpState = false;

	m_ItemOwner = nullptr;
}