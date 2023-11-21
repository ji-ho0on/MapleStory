#include "AreaWarning.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"

CAreaWarning::CAreaWarning() :
	m_Damage(0.f)
{
	SetTypeID<CAreaWarning>();
	m_RenderLayer = ERender_Layer::Monster;
}

CAreaWarning::CAreaWarning(const CAreaWarning& Obj) :
	CGameObject(Obj)
{
}

CAreaWarning::~CAreaWarning()
{
}

bool CAreaWarning::Init()
{
	m_Damage = 20.f;
	

	CreateAnimation();

	AddAnimation("AreaWarning", false, 4.f);

	SetEndFunction<CAreaWarning>("AreaWarning", this, &CAreaWarning::AreaWarningEnd);

	AddNotify<CAreaWarning>("AreaWarning", 18, this, &CAreaWarning::Attack);

	AddNotify<CAreaWarning>("AreaWarning", 20, this, &CAreaWarning::AttackEnd);


	CColliderBox* Box = AddCollider<CColliderBox>("AreaWarningAttack");

	Box->SetExtent(220.f, 130.f);
	Box->SetOffset(0.f, -65.f);
	Box->SetCollisionProfile("MonsterAttack");

	Box->SetCollisionBeginFunction<CAreaWarning>(this, &CAreaWarning::CollisionBegin);
	Box->SetCollisionEndFunction<CAreaWarning>(this, &CAreaWarning::CollisionEnd);

	Box->SetEnable(false);

	//CColliderCircle* Circle = AddCollider<CColliderCircle>("Banana");

	//Circle->SetRadius(15.f);
	//Circle->SetCollisionProfile("MonsterAttack");

	//Circle->SetCollisionBeginFunction<CAreaWarning>(this, &CAreaWarning::CollisionBegin);
	//Circle->SetCollisionEndFunction<CAreaWarning>(this, &CAreaWarning::CollisionEnd);

	return true;
}

void CAreaWarning::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CAreaWarning::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CAreaWarning::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CAreaWarning::AreaWarningEnd()
{
	SetActive(false);
}

void CAreaWarning::Attack()
{
	CColliderBox* Box = (CColliderBox*)FindCollider("AreaWarningAttack");

	Box->SetEnable(true);
}

void CAreaWarning::AttackEnd()
{
	CColliderBox* Box = (CColliderBox*)FindCollider("AreaWarningAttack");

	if (Box)
	{
		Box->SetEnable(false);
	}
}

void CAreaWarning::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	//
	Dest->GetOwner()->InflictDamage(m_Damage);

	CCollider* Box = FindCollider("AreaWarningAttack");

	Box->SetActive(false);

	Dest->DeleteCollisionList(Box);
}

void CAreaWarning::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}