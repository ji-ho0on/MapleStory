#include "HectorAttack.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"

CHectorAttack::CHectorAttack() :
	m_Damage(0.f)
{
	SetTypeID<CHectorAttack>();
	m_RenderLayer = ERender_Layer::Monster;
}

CHectorAttack::CHectorAttack(const CHectorAttack& Obj) :
	CGameObject(Obj)
{
}

CHectorAttack::~CHectorAttack()
{
}

bool CHectorAttack::Init()
{
	m_Damage = 10.f;
	m_Dir = -1;

	//SetPos(900.f, 100.f);
	//SetSize(50.f, 50.f);
	//SetPivot(0.5f, 0.5f);

	CreateAnimation();

	AddAnimation("HectorLeftAttackEffect", false, 0.5f);
	AddAnimation("HectorRightAttackEffect", false, 0.5f);

	SetEndFunction<CHectorAttack>("HectorLeftAttackEffect", this, &CHectorAttack::AttackEnd);
	SetEndFunction<CHectorAttack>("HectorRightAttackEffect", this, &CHectorAttack::AttackEnd);

	AddNotify<CHectorAttack>("HectorLeftAttackEffect", 0, this, &CHectorAttack::Attack0);
	AddNotify<CHectorAttack>("HectorLeftAttackEffect", 1, this, &CHectorAttack::Attack1);
	AddNotify<CHectorAttack>("HectorLeftAttackEffect", 2, this, &CHectorAttack::Attack2);

	AddNotify<CHectorAttack>("HectorRightAttackEffect", 0, this, &CHectorAttack::Attack0);
	AddNotify<CHectorAttack>("HectorRightAttackEffect", 1, this, &CHectorAttack::Attack1);
	AddNotify<CHectorAttack>("HectorRightAttackEffect", 2, this, &CHectorAttack::Attack2);

	CColliderBox* Box = AddCollider<CColliderBox>("HectorAttackeEffect");

	Box->SetExtent(70.f, 50.f);
	Box->SetOffset(-15.f, -25.f);
	Box->SetCollisionProfile("MonsterAttack");

	Box->SetCollisionBeginFunction<CHectorAttack>(this, &CHectorAttack::CollisionBegin);
	Box->SetCollisionEndFunction<CHectorAttack>(this, &CHectorAttack::CollisionEnd);

	return true;
}

void CHectorAttack::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	//CCollider* Box = FindCollider("HectorAttackeEffect");

	//if (m_Dir == -1)
	//	Box->SetOffset(-15.f, -25.f);

	//else
	//	Box->SetOffset(15.f, -25.f);

}

void CHectorAttack::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	if (m_Dir == -1)
		ChangeAnimation("HectorLeftAttackEffect");

	else
		ChangeAnimation("HectorRightAttackEffect");
}

void CHectorAttack::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CHectorAttack::AttackEnd()
{
	SetActive(false);
}

void CHectorAttack::Attack0()
{
	CCollider* Box = FindCollider("HectorAttackeEffect");

	if (Box)
	{
		if (m_Dir == -1)
			Box->SetOffset(-45.f, -25.f);

		else
			Box->SetOffset(45.f, -25.f);
	}
}

void CHectorAttack::Attack1()
{
	CCollider* Box = FindCollider("HectorAttackeEffect");

	if (Box)
	{
		if (m_Dir == -1)
			Box->SetOffset(-75.f, -25.f);

		else
			Box->SetOffset(75.f, -25.f);
	}
}

void CHectorAttack::Attack2()
{
	CCollider* Box = FindCollider("HectorAttackeEffect");

	if (Box)
	{
		if (m_Dir == -1)
			Box->SetOffset(-110.f, -25.f);

		else
			Box->SetOffset(110.f, -25.f);
	}
}

void CHectorAttack::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	// 面倒 矫 单固瘤 贸府
	Dest->GetOwner()->InflictDamage(m_Damage);

	CCollider* Box = FindCollider("HectorAttackEffect");

	if (Box)
	{
		Dest->DeleteCollisionList(Box);
		Box->SetActive(false);
	}
}

void CHectorAttack::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}