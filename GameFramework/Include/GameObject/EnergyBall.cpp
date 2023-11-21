#include "EnergyBall.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderCircle.h"

CEnergyBall::CEnergyBall() :
	m_Damage(0.f)
{
	SetTypeID<CEnergyBall>();
	m_RenderLayer = ERender_Layer::Monster;
}

CEnergyBall::CEnergyBall(const CEnergyBall& Obj) :
	CGameObject(Obj)
{
}

CEnergyBall::~CEnergyBall()
{
}

bool CEnergyBall::Init()
{
	m_Damage = 30.f;

	CreateAnimation();

	AddAnimation("EnergyBall", true, 1.f);

	CColliderCircle* Circle = AddCollider<CColliderCircle>("EnergyBallAttack");

	Circle->SetRadius(40.f);
	Circle->SetOffset(0.f, -67.f);
	Circle->SetCollisionProfile("MonsterAttack");

	Circle->SetCollisionBeginFunction<CEnergyBall>(this, &CEnergyBall::CollisionBegin);
	Circle->SetCollisionEndFunction<CEnergyBall>(this, &CEnergyBall::CollisionEnd);

	SetPhysicsSimulate(true);
	
	m_Init = false;

	return true;
}

void CEnergyBall::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (!m_Init)
	{
		Jump();

		m_Init = true;
	}

	MoveDir(Vector2(-1.f, 0.f));


	if (m_Pos.x + (1.f - m_Pivot.x) * m_Size.x <= 0.f)
	{
		SetActive(false);
	}

	if (m_JumpVelocity <= 0.f)
	{
		SetActive(false);
	}
}

void CEnergyBall::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	if (m_Pos.y + (1.f - m_Pivot.y) * m_Size.y >= 650.f)
	{
		Jump();

		m_JumpVelocity -= 5.f;
	}
}

void CEnergyBall::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CEnergyBall::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	// 面倒 矫 单固瘤 贸府
	Dest->GetOwner()->InflictDamage(m_Damage);

	SetActive(false);
}

void CEnergyBall::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}