#include "LupinBanana.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderCircle.h"

CLupinBanana::CLupinBanana() :
	m_Damage(0.f)
{
	SetTypeID<CLupinBanana>();
}

CLupinBanana::CLupinBanana(const CLupinBanana& Obj) :
	CGameObject(Obj),
	m_Dir(Obj.m_Dir),
	m_Distance(Obj.m_Distance)
{
}

CLupinBanana::~CLupinBanana()
{
}

bool CLupinBanana::Init()
{
	m_MoveSpeed = 700.f;
	m_Distance = 260.f;
	m_Dir = Vector2(1.f, 0.f);
	m_Damage = 10.f;

	SetPos(900.f, 100.f);
	SetSize(50.f, 50.f);
	SetPivot(0.5f, 0.5f);

	CreateAnimation();

	AddAnimation("LupinLeftBanana", true, 0.4f);
	AddAnimation("LupinRightBanana", true, 0.4f);

	CColliderCircle* Circle = AddCollider<CColliderCircle>("Banana");

	Circle->SetRadius(15.f);
	Circle->SetCollisionProfile("MonsterAttack");

	Circle->SetCollisionBeginFunction<CLupinBanana>(this, &CLupinBanana::CollisionBegin);
	Circle->SetCollisionEndFunction<CLupinBanana>(this, &CLupinBanana::CollisionEnd);

	return true;
}

void CLupinBanana::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	MoveDir(m_Dir);

	m_Distance -= m_MoveSpeed * DeltaTime;

	if (m_Distance <= 0.f)
		SetActive(false);
}

void CLupinBanana::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CLupinBanana::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CLupinBanana::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	// Damage Ã³¸®
	Dest->GetOwner()->InflictDamage(m_Damage);

	m_Scene->GetSceneResource()->SoundPlay("LupinBananaDamage");

	SetActive(false);
}

void CLupinBanana::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}