#include "WhiteFang.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/Collider.h"
#include "../Collision/ColliderBox.h"
#include "HectorAttack.h"
#include "SealBreakCard.h"
#include "../Scene/TheSeed2F.h"
#include "Player.h"

CWhiteFang::CWhiteFang()
{
	SetTypeID<CWhiteFang>();
	m_RenderLayer = ERender_Layer::Monster;
}

CWhiteFang::CWhiteFang(const CWhiteFang& Obj) :
	CMonster(Obj),
	m_Dir(Obj.m_Dir)
{
}

CWhiteFang::~CWhiteFang()
{
}

bool CWhiteFang::Init()
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

	CColliderBox* WhiteFangBody = AddCollider<CColliderBox>("WhiteFangBody");
	WhiteFangBody->SetExtent(70.f, 50.f);
	WhiteFangBody->SetOffset(-15.f, -25.f);
	WhiteFangBody->SetCollisionProfile("Monster");
	WhiteFangBody->SetCollisionBeginFunction<CWhiteFang>(this, &CWhiteFang::CollisionBegin);
	WhiteFangBody->SetCollisionEndFunction<CWhiteFang>(this, &CWhiteFang::CollisionEnd);

	CColliderBox* WhiteFangAttackRange = AddCollider<CColliderBox>("WhiteFangAttackRange");
	WhiteFangAttackRange->SetExtent(120.f, 50.f);
	WhiteFangAttackRange->SetOffset(-40.f, -25.f);
	WhiteFangAttackRange->SetCollisionProfile("MonsterAttackRange");
	WhiteFangAttackRange->SetCollisionBeginFunction<CWhiteFang>(this, &CWhiteFang::AttackRangeCollisionBegin);
	WhiteFangAttackRange->SetCollisionEndFunction<CWhiteFang>(this, &CWhiteFang::AttackRangeCollisionEnd);

	CreateAnimation();

	AddAnimation("WhiteFangLeftStand", true, 0.7f);
	AddAnimation("WhiteFangRightStand", true, 0.7f);
	AddAnimation("WhiteFangLeftMove", true, 0.4f);
	AddAnimation("WhiteFangRightMove", true, 0.4f);
	AddAnimation("WhiteFangLeftAttack", true, 1.5f);
	AddAnimation("WhiteFangRightAttack", true, 1.5f);
	AddAnimation("WhiteFangLeftDie", false);
	AddAnimation("WhiteFangRightDie", false);
	AddAnimation("WhiteFangLeftHit");
	AddAnimation("WhiteFangRightHit");
	AddAnimation("WhiteFangLeftJump");
	AddAnimation("WhiteFangRightJump");

	SetEndFunction<CWhiteFang>("WhiteFangLeftAttack", this, &CWhiteFang::AttackEnd);
	SetEndFunction<CWhiteFang>("WhiteFangRightAttack", this, &CWhiteFang::AttackEnd);
	AddNotify<CWhiteFang>("WhiteFangLeftAttack", 3, this, &CWhiteFang::Attack);
	AddNotify<CWhiteFang>("WhiteFangRightAttack", 3, this, &CWhiteFang::Attack);

	SetEndFunction<CWhiteFang>("WhiteFangLeftDie", this, &CWhiteFang::DieEnd);
	SetEndFunction<CWhiteFang>("WhiteFangRightDie", this, &CWhiteFang::DieEnd);

	m_vecSequenceKey[0].push_back("WhiteFangRightStand");
	m_vecSequenceKey[0].push_back("WhiteFangRightMove");
	m_vecSequenceKey[0].push_back("WhiteFangRightJump");
	m_vecSequenceKey[0].push_back("WhiteFangRightAttack");
	m_vecSequenceKey[0].push_back("WhiteFangRightHit");
	m_vecSequenceKey[0].push_back("WhiteFangRightDie");

	m_vecSequenceKey[1].push_back("WhiteFangLeftStand");
	m_vecSequenceKey[1].push_back("WhiteFangLeftMove");
	m_vecSequenceKey[1].push_back("WhiteFangLeftJump");
	m_vecSequenceKey[1].push_back("WhiteFangLeftAttack");
	m_vecSequenceKey[1].push_back("WhiteFangLeftHit");
	m_vecSequenceKey[1].push_back("WhiteFangLeftDie");

	SetPhysicsSimulate(true);
	SetSideWallCheck(true);
	SetJumpVelocity(30.f);

	m_SpawnNumber = -1;


	srand((unsigned int)time(0));

	int Random = rand();

	return true;
}

void CWhiteFang::Update(float DeltaTime)
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


				int WhiteFangDir = rand() % (int)EWhiteFang_Dir::Max;

				if (WhiteFangDir == 0)
					m_Dir = Vector2(-1.f, 0.f);

				else if (WhiteFangDir == 1)
					m_Dir = Vector2(1.f, 0.f);

				int WhiteFangMotion = rand() % 3;

				if (WhiteFangMotion == (int)EWhiteFang_Motion::Move)
				{
					m_MoveMotion = true;
				}

				else if (WhiteFangMotion == (int)EWhiteFang_Motion::Jump)
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

void CWhiteFang::PostUpdate(float DeltaTime)
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


	CCollider* WhiteFangBody = FindCollider("WhiteFangBody");
	CCollider* WhiteFangAttackRange = FindCollider("WhiteFangAttackRange");

	if (AnimDirIndex == 1)
	{
		WhiteFangBody->SetOffset(-15.f, -25.f);
		WhiteFangAttackRange->SetOffset(-40.f, -25.f);
	}

	else
	{
		WhiteFangBody->SetOffset(15.f, -25.f);
		WhiteFangAttackRange->SetOffset(40.f, -25.f);
	}

	if (m_Die)
	{
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EWhiteFang_Motion::Die]);
	}

	else if (m_Attacked)
	{
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EWhiteFang_Motion::Hit]);
	}

	else if (m_Attack)
	{
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EWhiteFang_Motion::Attack]);
	}

	else if (m_Jump)
	{
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EWhiteFang_Motion::Jump]);
	}

	else if (m_MoveMotion)
	{
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EWhiteFang_Motion::Move]);
	}

	else
	{
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EWhiteFang_Motion::Stand]);
	}
}

void CWhiteFang::Render(HDC hDC, float DeltaTime)
{
	CMonster::Render(hDC, DeltaTime);
}

float CWhiteFang::InflictDamage(float Damage)
{
	CMonster::InflictDamage(Damage);

	m_HP -= (int)Damage;

	m_Attacked = true;

	return Damage;
}

void CWhiteFang::Attack()
{
	m_AttackTime = 0.f;

	CHectorAttack* WhiteFangAttack = m_Scene->CreateObject<CHectorAttack>("WhiteFangAttack");
	WhiteFangAttack->SetPos(m_Pos);

	if (m_Dir.x == -1.f)
		WhiteFangAttack->SetDir(-1);

	else
		WhiteFangAttack->SetDir(1);

	m_Scene->GetSceneResource()->SoundPlay("HectorAttack");
}

void CWhiteFang::AttackEnd()
{
	m_Attack = false;
}

void CWhiteFang::DieEnd()
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

void CWhiteFang::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	if (Dest->GetName() == "Player")
		Dest->GetOwner()->InflictDamage(m_BodyDamage);
}

void CWhiteFang::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}

void CWhiteFang::AttackRangeCollisionBegin(CCollider* Src, CCollider* Dest)
{
	m_AttackState = true;
}

void CWhiteFang::AttackRangeCollisionEnd(CCollider* Src, CCollider* Dest)
{
	m_AttackState = false;
}
