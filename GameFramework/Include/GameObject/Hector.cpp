#include "Hector.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/Collider.h"
#include "../Collision/ColliderBox.h"
#include "HectorAttack.h"
#include "SealBreakCard.h"
#include "../Scene/TheSeed2F.h"
#include "Player.h"

CHector::CHector()
{
	SetTypeID<CHector>();
	m_RenderLayer = ERender_Layer::Monster;
}

CHector::CHector(const CHector& Obj) :
	CMonster(Obj),
	m_Dir(Obj.m_Dir)
{
}

CHector::~CHector()
{
}

bool CHector::Init()
{
	CMonster::Init();

	m_MoveSpeed = 100.f;

	m_SelectTime = 0.f;

	m_MoveMotion = false;

	m_JumpMotion = false;
	m_JumpCount = 0;

	m_BodyDamage = 5.f;

	m_Attacked = false;
	m_AttackedTime = 0.f;

	m_AttackTime = 0.f;
	m_AttackState = false;
	m_Attack = false;
	m_AttackCount = 0;

	m_EXP = 50;

	m_HP = 100;
	m_HPMax = 100;

	m_Dir = Vector2(-1.f, 0.f);

	//SetPos(900.f, 100.f);
	SetSize(49.f, 54.f);
	SetPivot(0.5f, 1.f);

	CColliderBox* HectorBody = AddCollider<CColliderBox>("HectorBody");
	HectorBody->SetExtent(70.f, 50.f);
	HectorBody->SetOffset(-15.f, -25.f);
	HectorBody->SetCollisionProfile("Monster");
	HectorBody->SetCollisionBeginFunction<CHector>(this, &CHector::CollisionBegin);
	HectorBody->SetCollisionEndFunction<CHector>(this, &CHector::CollisionEnd);

	CColliderBox* HectorAttackRange = AddCollider<CColliderBox>("HectorAttackRange");
	HectorAttackRange->SetExtent(120.f, 50.f);
	HectorAttackRange->SetOffset(-40.f, -25.f);
	HectorAttackRange->SetCollisionProfile("MonsterAttackRange");
	HectorAttackRange->SetCollisionBeginFunction<CHector>(this, &CHector::AttackRangeCollisionBegin);
	HectorAttackRange->SetCollisionEndFunction<CHector>(this, &CHector::AttackRangeCollisionEnd);

	CreateAnimation();

	AddAnimation("HectorLeftStand", true, 0.7f);
	AddAnimation("HectorRightStand", true, 0.7f);
	AddAnimation("HectorLeftMove", true, 0.4f);
	AddAnimation("HectorRightMove", true, 0.4f);
	AddAnimation("HectorLeftAttack", true, 1.5f);
	AddAnimation("HectorRightAttack", true, 1.5f);
	AddAnimation("HectorLeftDie", false);
	AddAnimation("HectorRightDie", false);
	AddAnimation("HectorLeftHit");
	AddAnimation("HectorRightHit");
	AddAnimation("HectorLeftJump");
	AddAnimation("HectorRightJump");

	SetEndFunction<CHector>("HectorLeftAttack", this, &CHector::AttackEnd);
	SetEndFunction<CHector>("HectorRightAttack", this, &CHector::AttackEnd);
	AddNotify<CHector>("HectorLeftAttack", 3, this, &CHector::Attack);
	AddNotify<CHector>("HectorRightAttack", 3, this, &CHector::Attack);

	SetEndFunction<CHector>("HectorLeftDie", this, &CHector::DieEnd);
	SetEndFunction<CHector>("HectorRightDie", this, &CHector::DieEnd);

	m_vecSequenceKey[0].push_back("HectorRightStand");
	m_vecSequenceKey[0].push_back("HectorRightMove");
	m_vecSequenceKey[0].push_back("HectorRightJump");
	m_vecSequenceKey[0].push_back("HectorRightAttack");
	m_vecSequenceKey[0].push_back("HectorRightHit");
	m_vecSequenceKey[0].push_back("HectorRightDie");

	m_vecSequenceKey[1].push_back("HectorLeftStand");
	m_vecSequenceKey[1].push_back("HectorLeftMove");
	m_vecSequenceKey[1].push_back("HectorLeftJump");
	m_vecSequenceKey[1].push_back("HectorLeftAttack");
	m_vecSequenceKey[1].push_back("HectorLeftHit");
	m_vecSequenceKey[1].push_back("HectorLeftDie");

	SetPhysicsSimulate(true);
	SetSideWallCheck(true);
	SetJumpVelocity(30.f);

	m_SpawnNumber = -1;


	srand((unsigned int)time(0));

	int Random = rand();

	return true;
}

void CHector::Update(float DeltaTime)
{
	CMonster::Update(DeltaTime);

	if (m_HP <= 0)
	{
		m_Die = true;
	}

	if (m_Ground)
	{
		m_JumpMotion = false;
	}

	if (m_Attacked)
	{
		m_AttackedTime += DeltaTime;

		if (m_AttackedTime >= 0.3f)
		{
			m_Attacked = false;
			m_AttackedTime = 0.f;
		}
	}

	if (m_AttackState)
	{
		m_Attack = true;
	}

	if (!m_Die)
	{
		// 공격상태가 되면 선택시간을 초기화 한다.
		if (m_Attack)
		{
			//m_SelectTime = 0.f;
			m_MoveMotion = false;
			m_JumpMotion = false;
		}

		// 공격상태나 공격당하는 상태가 아닐 때 다른 모션을 수행한다.
		else if (!m_Attack || !m_Attacked)
		{
			m_SelectTime += DeltaTime;

			// 랜덤으로 2초에 한 번 왼쪽 or 오른쪽으로 Stand, Move, Jump 세가지 모션중 하나를 선택한다.
			if (m_SelectTime >= 2.f)
			{
				m_SelectTime -= 2.f;

				// 새로운 Motion을 선택하기 전에 이전 모션들을 false로 바꿔준다.
				m_MoveMotion = false;
				m_JumpCount = 0;


				int HectorDir = rand() % (int)EHector_Dir::Max;

				if (HectorDir == 0)
					m_Dir = Vector2(-1.f, 0.f);

				else if (HectorDir == 1)
					m_Dir = Vector2(1.f, 0.f);

				int HectorMotion = rand() % 3;

				if (HectorMotion == (int)EHector_Motion::Move)
				{
					m_MoveMotion = true;
				}

				else if (HectorMotion == (int)EHector_Motion::Jump)
				{
					m_JumpMotion = true;
				}
			}
		}
	}

	else
	{
		m_Attacked = false;
		m_MoveMotion = false;
		m_JumpMotion = false;
		m_Attack = false;
	}

	if (m_MoveMotion && !m_Die && !m_Attacked)
	{
		MoveDir(m_Dir);
	}
}

void CHector::PostUpdate(float DeltaTime)
{
	CMonster::PostUpdate(DeltaTime);


	// 점프모션이면 점프를 수행
	if (m_JumpMotion && m_JumpCount < 1)
	{
		Jump();
		++m_JumpCount;
	}

	int	AnimDirIndex = 1;

	if (m_Dir.x == 1.f)
		AnimDirIndex = 0;


	CCollider* HectorBody = FindCollider("HectorBody");
	CCollider* HectorAttackRange = FindCollider("HectorAttackRange");

	if (AnimDirIndex == 1)
	{
		HectorBody->SetOffset(-15.f, -25.f);
		HectorAttackRange->SetOffset(-40.f, -25.f);
	}

	else
	{
		HectorBody->SetOffset(15.f, -25.f);
		HectorAttackRange->SetOffset(40.f, -25.f);
	}

	if (m_Die)
	{
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EHector_Motion::Die]);
	}

	else if (m_Attacked)
	{
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EHector_Motion::Hit]);
	}

	else if (m_Attack)
	{
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EHector_Motion::Attack]);
	}

	else if (m_Jump)
	{
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EHector_Motion::Jump]);
	}

	else if (m_MoveMotion)
	{
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EHector_Motion::Move]);
	}

	else
	{
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EHector_Motion::Stand]);
	}
}

void CHector::Render(HDC hDC, float DeltaTime)
{
	CMonster::Render(hDC, DeltaTime);
}

float CHector::InflictDamage(float Damage)
{
	CMonster::InflictDamage(Damage);

	m_HP -= (int)Damage;

	m_Attacked = true;

	return Damage;
}

void CHector::Attack()
{
	m_AttackTime = 0.f;

	CHectorAttack* HectorAttack = m_Scene->CreateObject<CHectorAttack>("HectorAttack");
	HectorAttack->SetPos(m_Pos);

	if (m_Dir.x == -1.f)
		HectorAttack->SetDir(-1);

	else
		HectorAttack->SetDir(1);

	m_Scene->GetSceneResource()->SoundPlay("HectorAttack");
}

void CHector::AttackEnd()
{
	m_Attack = false;
}

void CHector::DieEnd()
{
	SetActive(false);

	m_Scene->GetSceneResource()->SoundPlay("HectorDie");

	CSealBreakCard* SealBreakCard = m_Scene->CreateObject<CSealBreakCard>("SealBreakCard");
	SealBreakCard->SetPos(m_Pos);
	SealBreakCard->SetFallStartY(m_Pos.y);

	CTheSeed2F* Scene = (CTheSeed2F*)m_Scene;

	CPlayer* Player = (CPlayer*)Scene->GetPlayer();

	Player->AddEXP(m_EXP);

	Scene->ResetSpawn(m_SpawnNumber);
}

void CHector::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	if (Dest->GetName() == "Player")
		Dest->GetOwner()->InflictDamage(m_BodyDamage);
}

void CHector::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}

void CHector::AttackRangeCollisionBegin(CCollider* Src, CCollider* Dest)
{
	m_AttackState = true;
}

void CHector::AttackRangeCollisionEnd(CCollider* Src, CCollider* Dest)
{
	m_AttackState = false;
}
