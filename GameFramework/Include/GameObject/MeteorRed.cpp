#include "MeteorRed.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderCircle.h"

CMeteorRed::CMeteorRed() :
	m_Damage(0.f)
{
	SetTypeID<CMeteorRed>();
	m_RenderLayer = ERender_Layer::Monster;
}

CMeteorRed::CMeteorRed(const CMeteorRed& Obj) :
	CGameObject(Obj)
{
}

CMeteorRed::~CMeteorRed()
{
}

bool CMeteorRed::Init()
{
	m_Damage = 20.f;

	//SetPos(900.f, 100.f);
	//SetSize(50.f, 50.f);
	//SetPivot(0.5f, 0.5f);

	CreateAnimation();

	AddAnimation("MeteorRed", true, 2.f);

	CColliderCircle* Circle = AddCollider<CColliderCircle>("MeteorRedAttack");

	Circle->SetRadius(14.f);
	Circle->SetOffset(15.f, -9.f);
	Circle->SetCollisionProfile("MonsterAttack");

	Circle->SetCollisionBeginFunction<CMeteorRed>(this, &CMeteorRed::CollisionBegin);
	Circle->SetCollisionEndFunction<CMeteorRed>(this, &CMeteorRed::CollisionEnd);

	return true;
}

void CMeteorRed::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_Pos.y >= 650.f)
	{
		SetActive(false);
	}

	Move(135.f);
}

void CMeteorRed::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CMeteorRed::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CMeteorRed::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	// 面倒 矫 单固瘤 贸府
	Dest->GetOwner()->InflictDamage(m_Damage);

	SetActive(false);
}

void CMeteorRed::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}