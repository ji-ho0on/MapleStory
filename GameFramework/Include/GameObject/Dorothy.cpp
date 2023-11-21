#include "Dorothy.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/Camera.h"
#include "AreaWarning.h"
#include "EnergyBall.h"
#include "../Collision/Collider.h"
#include "../Collision/ColliderBox.h"
#include "../Scene/TheSeed50F.h"
#include "Effect.h"

CDorothy::CDorothy()
{
	SetTypeID<CDorothy>();
	m_RenderLayer = ERender_Layer::Monster;
}

CDorothy::CDorothy(const CDorothy& Obj) :
	CMonster(Obj),
	m_Dir(Obj.m_Dir)
{
}

CDorothy::~CDorothy()
{
}

bool CDorothy::Init()
{
	CMonster::Init();

	m_MoveSpeed = 0.f;

	m_SelectTime = 0.f;

	m_BodyDamage = 10;


	m_AttackTime = 0.f;
	m_Attack = false;
	m_DorothyAttack = false;
	m_AttackCount = 0;


	m_Skill1 = false;


	m_Skill2 = false;
	m_Skill2Damage = 50.f;


	m_Dir = Vector2(-1.f, 0.f);

	//SetPos(900.f, 100.f);
	SetSize(49.f, 54.f);
	SetPivot(0.5f, 1.f);

	CColliderBox* Dorothy = AddCollider<CColliderBox>("DorothyBody");
	Dorothy->SetExtent(40.f, 106.f);
	Dorothy->SetOffset(3.f, -83.f);
	Dorothy->SetCollisionProfile("Monster");
	Dorothy->SetCollisionBeginFunction<CDorothy>(this, &CDorothy::CollisionBegin);
	Dorothy->SetCollisionEndFunction<CDorothy>(this, &CDorothy::CollisionEnd);

	m_AreaInfo[0].PosX = -500.f;
	m_AreaInfo[1].PosX = -300.f;
	m_AreaInfo[2].PosX = -100.f;
	m_AreaInfo[3].PosX = 100.f;

	m_AreaInfo[0].Create = false;
	m_AreaInfo[1].Create = false;
	m_AreaInfo[2].Create = false;
	m_AreaInfo[3].Create = false;

	CreateAnimation();

	AddAnimation("DorothyStand", true, 1.f);
	AddAnimation("DorothyAttack", false, 2.f);
	AddAnimation("DorothySkill1", false, 2.f);
	AddAnimation("DorothySkill2", false, 4.f);
	AddAnimation("DorothyDie", false, 3.f);

	SetEndFunction<CDorothy>("DorothyAttack", this, &CDorothy::AttackEnd);
	AddNotify<CDorothy>("DorothyAttack", 13, this, &CDorothy::Attack);


	SetEndFunction<CDorothy>("DorothySkill1", this, &CDorothy::Skill1End);
	AddNotify<CDorothy>("DorothySkill1", 9, this, &CDorothy::CreateEnergyBall);


	SetEndFunction<CDorothy>("DorothySkill2", this, &CDorothy::Skill2End);
	AddNotify<CDorothy>("DorothySkill2", 24, this, &CDorothy::Skill2);
	AddNotify<CDorothy>("DorothySkill2", 25, this, &CDorothy::Skill2AttackEnd);


	SetEndFunction<CDorothy>("DorothyDie", this, &CDorothy::DieEnd);



	m_HP = 300;
	m_HPMax = 300;

	m_EXP = 500;

	srand((unsigned int)time(0));

	int Random = rand();

	return true;
}

void CDorothy::Update(float DeltaTime)
{
	CMonster::Update(DeltaTime);

	m_SelectTime += DeltaTime;

	// 랜덤으로 5초에 한 번 Attack, Skill1, Skill2 중 하나를 선택해서 공격함
	if (m_SelectTime >= 5.f)
	{
		m_SelectTime -= 5.f;

		int AttackType = rand() % (int)EDorothy_Attack_Type::Max;

		if (AttackType == (int)EDorothy_Attack_Type::Attack)
		{
			m_Attack = true;
			m_Scene->GetSceneResource()->SoundPlay("DorothyAttack");
		}

		else if (AttackType == (int)EDorothy_Attack_Type::Skill1)
		{
			m_Skill1 = true;
			m_Scene->GetSceneResource()->SoundPlay("DorothySkill1");
		}

		else if (AttackType == (int)EDorothy_Attack_Type::Skill2)
		{
			m_Skill2 = true;
			m_Scene->GetSceneResource()->SoundPlay("DorothySkill2");
		}
	}

	// AreaWarning을 3번 생성하면 공격 종료
	if (m_AttackCount >= 3)
	{
		m_DorothyAttack = false;
		m_AttackCount = 0;

		for (int i = 0; i < 4; ++i)
		{
			m_AreaInfo[i].Create = false;
		}
	}

	if (m_DorothyAttack)
	{
		m_AttackTime += DeltaTime;

		if (m_AttackTime >= 0.3f)
		{
			m_AttackTime -= 0.3f;
			++m_AttackCount;

			// AreaWarning 생성
			CreateAreaWarning();
		}
	}
}

void CDorothy::PostUpdate(float DeltaTime)
{
	CMonster::PostUpdate(DeltaTime);

	if (m_HP <= 0)
	{
		ChangeAnimation("DorothyDie");

		CCollider* Dorothy = FindCollider("DorothyBody");

		if (Dorothy)
		{
			Dorothy->SetActive(false);

			CTheSeed50F* TheSeed50F = (CTheSeed50F*)m_Scene;

			TheSeed50F->DorothyDie();

			m_Scene->GetSceneResource()->SoundPlay("DorothyDie");
		}
	}

	else if (m_Attack)
	{
		ChangeAnimation("DorothyAttack");
	}

	else if (m_Skill1)
	{
		ChangeAnimation("DorothySkill1");
	}

	else if (m_Skill2)
	{
		ChangeAnimation("DorothySkill2");
	}

	else
	{
		ChangeAnimation("DorothyStand");
	}
}

void CDorothy::Render(HDC hDC, float DeltaTime)
{
	CMonster::Render(hDC, DeltaTime);
}

float CDorothy::InflictDamage(float Damage)
{
	CMonster::InflictDamage(Damage);

	m_HP -= (int)Damage;

	return Damage;
}

void CDorothy::CreateAreaWarning()
{
	// 4군데 중 한 곳에 랜덤으로 생성
	int Index = rand() % 4;

	if (m_AreaInfo[Index].Create == false)
	{
		// 생성되어 있지 않다면 AreaWarning 생성
		CAreaWarning* AreaWarning = m_Scene->CreateObject<CAreaWarning>("AreaWarning");

		AreaWarning->SetPos(m_Pos.x + m_AreaInfo[Index].PosX, m_Pos.y);

		m_AreaInfo[Index].Create = true;
	}
}

void CDorothy::CreateEnergyBall()
{

	for (int i = 0; i < 4; ++i)
	{
		float EnergyBallSpeed = (rand() % 10 + 1) * 50.f;

		float EnergyBallJumpVelocity = (rand() % 11) * 5.f + 50.f;

		CEnergyBall* EnergyBall = m_Scene->CreateObject<CEnergyBall>("EnergyBall");

		EnergyBall->SetPos(m_Pos.x - 92.f, m_Pos.y - 27.f);

		EnergyBall->SetFallStartY(m_Pos.y - 27.f);

		EnergyBall->SetMoveSpeed(EnergyBallSpeed);

		EnergyBall->SetJumpVelocity(EnergyBallJumpVelocity);
	}
}

void CDorothy::Attack()
{
	m_DorothyAttack = true;
	m_AttackTime = 0.f;
	m_Scene->GetSceneResource()->SoundPlay("DorothyAttack");
}

void CDorothy::AttackEnd()
{
	m_Attack = false;
}

void CDorothy::Skill1End()
{
	m_Skill1 = false;
}

void CDorothy::Skill2()
{
	CColliderBox* Skill2 = AddCollider<CColliderBox>("Skill2");

	Skill2->SetExtent(1500.f, 160.f);
	Skill2->SetOffset(-780.f, -80.f);
	Skill2->SetCollisionProfile("MonsterAttack");

	Skill2->SetCollisionBeginFunction<CDorothy>(this, &CDorothy::Skill2CollisionBegin);
	Skill2->SetCollisionEndFunction<CDorothy>(this, &CDorothy::Skill2CollisionEnd);
}

void CDorothy::Skill2AttackEnd()
{
	CCollider* Skill2 = FindCollider("Skill2");

	if (Skill2)
	{
		Skill2->SetActive(false);
	}
}

void CDorothy::Skill2End()
{
	m_Skill2 = false;
}

void CDorothy::DieEnd()
{
	SetActive(false);
}

void CDorothy::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	if (Dest->GetName() == "Player")
		Dest->GetOwner()->InflictDamage((float)m_BodyDamage);

	if (Dest->GetProfile()->Channel == ECollision_Channel::PlayerAttack)
	{
		m_Scene->GetSceneResource()->SoundPlay("DorothyHit");
	}
}

void CDorothy::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}

void CDorothy::Skill2CollisionBegin(CCollider* Src, CCollider* Dest)
{
	Dest->GetOwner()->InflictDamage(m_Skill2Damage);

	CCollider* Skill2 = FindCollider("Skill2");

	if (Skill2)
	{
		Skill2->SetActive(false);
		Dest->DeleteCollisionList(Skill2);
	}
}

void CDorothy::Skill2CollisionEnd(CCollider* Src, CCollider* Dest)
{
	//CColliderBox* Skill2 = (CColliderBox*)FindCollider("Skill2");

	//Dest->DeleteCollisionList((CCollider*)Skill2);

	//if (Skill2)
	//{
	//	Skill2->SetActive(false);
	//}
}
