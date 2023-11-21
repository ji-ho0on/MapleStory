#include "MeteorPurple.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderCircle.h"

CMeteorPurple::CMeteorPurple() :
	m_Damage(0.f)
{
	SetTypeID<CMeteorPurple>();
	m_RenderLayer = ERender_Layer::Monster;
}

CMeteorPurple::CMeteorPurple(const CMeteorPurple& Obj) :
	CGameObject(Obj)
{
}

CMeteorPurple::~CMeteorPurple()
{
}

bool CMeteorPurple::Init()
{
	m_Damage = 20.f;

	//SetPos(900.f, 100.f);
	//SetSize(50.f, 50.f);
	//SetPivot(0.5f, 0.5f);

	CreateAnimation();

	AddAnimation("MeteorPurple", true, 2.f);

	CColliderCircle* Circle = AddCollider<CColliderCircle>("MeteorPurpleAttack");

	Circle->SetRadius(20.f);
	Circle->SetOffset(20.f, -15.f);
	Circle->SetCollisionProfile("MonsterAttack");

	Circle->SetCollisionBeginFunction<CMeteorPurple>(this, &CMeteorPurple::CollisionBegin);
	Circle->SetCollisionEndFunction<CMeteorPurple>(this, &CMeteorPurple::CollisionEnd);

	return true;
}

void CMeteorPurple::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_Pos.y >= 650.f)
	{
		SetActive(false);
	}

	Move(135.f);
}

void CMeteorPurple::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CMeteorPurple::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CMeteorPurple::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	// 面倒 矫 单固瘤 贸府
	Dest->GetOwner()->InflictDamage(m_Damage);

	SetActive(false);
}

void CMeteorPurple::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}