#include "MeteorPink.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderCircle.h"

CMeteorPink::CMeteorPink() :
	m_Damage(0.f)
{
	SetTypeID<CMeteorPink>();
	m_RenderLayer = ERender_Layer::Monster;
}

CMeteorPink::CMeteorPink(const CMeteorPink& Obj) :
	CGameObject(Obj)
{
}

CMeteorPink::~CMeteorPink()
{
}

bool CMeteorPink::Init()
{
	m_Damage = 20.f;

	//SetPos(900.f, 100.f);
	//SetSize(50.f, 50.f);
	//SetPivot(0.5f, 0.5f);

	CreateAnimation();

	AddAnimation("MeteorPink", true, 2.f);

	CColliderCircle* Circle = AddCollider<CColliderCircle>("MeteorPinkAttack");

	Circle->SetRadius(25.f);
	Circle->SetOffset(28.f, -23.f);
	Circle->SetCollisionProfile("MonsterAttack");

	Circle->SetCollisionBeginFunction<CMeteorPink>(this, &CMeteorPink::CollisionBegin);
	Circle->SetCollisionEndFunction<CMeteorPink>(this, &CMeteorPink::CollisionEnd);

	return true;
}

void CMeteorPink::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_Pos.y >= 650.f)
	{
		SetActive(false);
	}

	Move(135.f);
}

void CMeteorPink::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CMeteorPink::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CMeteorPink::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	// 面倒 矫 单固瘤 贸府
	Dest->GetOwner()->InflictDamage(m_Damage);

	SetActive(false);
}

void CMeteorPink::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}