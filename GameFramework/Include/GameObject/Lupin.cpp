#include "Lupin.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "LupinBanana.h"
#include "../Collision/Collider.h"

CLupin::CLupin()
{
	SetTypeID<CLupin>();
	m_RenderLayer = ERender_Layer::Monster;
}

CLupin::CLupin(const CLupin& Obj) :
	CMonster(Obj),
	m_Dir(Obj.m_Dir)
{
}

CLupin::~CLupin()
{
}

bool CLupin::Init()
{
	CMonster::Init();

	m_MoveSpeed = 0.f;
	m_FireTime = 0.f;
	m_Fire = false;
	m_Dir = Vector2(-1.f, 0.f);

	//SetPos(900.f, 100.f);
	SetSize(49.f, 54.f);
	SetPivot(0.5f, 1.f);

	CreateAnimation();

	AddAnimation("LupinLeftStand");
	AddAnimation("LupinRightStand");
	AddAnimation("LupinLeftAttack", false);
	AddAnimation("LupinRightAttack", false);

	SetEndFunction<CLupin>("LupinLeftAttack", this, &CLupin::AttackEnd);
	SetEndFunction<CLupin>("LupinRightAttack", this, &CLupin::AttackEnd);

	AddNotify<CLupin>("LupinLeftAttack", 5, this, &CLupin::Attack);
	AddNotify<CLupin>("LupinRightAttack", 5, this, &CLupin::Attack);

	return true;
}

void CLupin::Update(float DeltaTime)
{
	CMonster::Update(DeltaTime);

	m_FireTime += DeltaTime;

	if (m_FireTime >= 2.f)
	{
		m_FireTime -= 2.f;

		m_Fire = true;

		m_Scene->GetSceneResource()->SoundPlay("LupinAttack");
	}
}

void CLupin::PostUpdate(float DeltaTime)
{
	CMonster::PostUpdate(DeltaTime);

	if (m_Fire)
	{
		if (m_Dir.x == -1.f)
			ChangeAnimation("LupinLeftAttack");

		else
			ChangeAnimation("LupinRightAttack");
	}

	else
	{
		if (m_Dir.x == -1.f)
			ChangeAnimation("LupinLeftStand");

		else
			ChangeAnimation("LupinRightStand");
	}
}

void CLupin::Render(HDC hDC, float DeltaTime)
{
	CMonster::Render(hDC, DeltaTime);
}

void CLupin::Attack()
{
	CLupinBanana* Banana = m_Scene->CreateObject<CLupinBanana>("Banana");

	CCollider* BananaCollider = Banana->FindCollider("Banana");

	BananaCollider->SetCollisionProfile("MonsterAttack");

	float	BananaX = m_Pos.x;

	if (m_Dir.x == -1.f)
	{
		BananaX = m_Pos.x - m_Pivot.x * m_Size.x -
			(1.f - Banana->GetPivot().x) * Banana->GetSize().x;
	}

	else if (m_Dir.x == 1.f)
	{
		BananaX = m_Pos.x + (1.f - m_Pivot.x) * m_Size.x +
			Banana->GetPivot().x * Banana->GetSize().x;
	}

	Banana->SetPos(BananaX, m_Pos.y - m_Size.y / 2.f);
	Banana->SetDir(m_Dir);
	Banana->SetDamage(10.f);
}

void CLupin::AttackEnd()
{
	m_Fire = false;
}
