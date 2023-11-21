
#include "Player.h"
#include "../Scene/Scene.h"
#include "../Input.h"
#include "../GameManager.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Widget/CharacterHUD.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/Text.h"
#include "../Widget/ProgressBar.h"
#include "Effect.h"
#include "../Widget/CharacterStatus.h"

CPlayer::CPlayer()
{
	SetTypeID<CPlayer>();
	m_RenderLayer = ERender_Layer::Player;
}

CPlayer::CPlayer(const CPlayer& Obj)	:
	CCharacter(Obj)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Start()
{
	m_Start = true;

	m_PrevPos = m_Pos;
}

bool CPlayer::Init()
{
	CGameObject::Init();

	m_MoveSpeed = 150.f;

	SetSize(85.f, 75.f);
	SetPivot(0.5f, 1.f);

	SkillCoolDownInfo	Info = {};

	Info.CoolDown = 5.f;
	m_vecCoolDown.push_back(Info);

	Info.CoolDown = 10.f;
	m_vecCoolDown.push_back(Info);

	CreateAnimation();

	AddAnimation("PlayerLeftAlert");
	AddAnimation("PlayerRightAlert");
	AddAnimation("PlayerLeftJump");
	AddAnimation("PlayerRightJump");
	AddAnimation("PlayerLeftProne");
	AddAnimation("PlayerRightProne");
	AddAnimation("PlayerLeftStand", true, 2.f);
	AddAnimation("PlayerRightStand", true, 2.f);
	AddAnimation("PlayerLeftSwing", false, 0.3f);
	AddAnimation("PlayerRightSwing", false, 0.3f);
	AddAnimation("PlayerLeftWalk");
	AddAnimation("PlayerRightWalk");
	AddAnimation("PlayerLeftProneStab", false, 0.2f);
	AddAnimation("PlayerRightProneStab", false, 0.2f);
	AddAnimation("PlayerLeftSwingT3", false, 0.3f);
	AddAnimation("PlayerRightSwingT3", false, 0.3f);
	AddAnimation("PlayerLeftSwingTF", false, 0.3f);
	AddAnimation("PlayerRightSwingTF", false, 0.3f);
	AddAnimation("PlayerRope");
	AddAnimation("PlayerRopeMove", true, 0.5f);
	AddAnimation("PlayerLeftAttacked");
	AddAnimation("PlayerRightAttacked");

	AddAnimation("SlashBlustLeft", false, 0.5f);
	AddAnimation("SlashBlustRight", false, 0.5f);
	AddAnimation("RaisingBlowLeft", false, 0.8f);
	AddAnimation("RaisingBlowRight", false, 0.8f);

	AddAnimation("Clear", false, 1.5f);

	SetEndFunction<CPlayer>("PlayerRightSwing", this, &CPlayer::AttackEnd);
	SetEndFunction<CPlayer>("PlayerLeftSwing", this, &CPlayer::AttackEnd);

	AddNotify<CPlayer>("PlayerRightSwing", 2, this, &CPlayer::Attack);
	AddNotify<CPlayer>("PlayerLeftSwing", 2, this, &CPlayer::Attack);

	SetEndFunction<CPlayer>("PlayerLeftProneStab", this, &CPlayer::AttackEnd);
	SetEndFunction<CPlayer>("PlayerRightProneStab", this, &CPlayer::AttackEnd);

	AddNotify<CPlayer>("PlayerLeftProneStab", 1, this, &CPlayer::Attack);
	AddNotify<CPlayer>("PlayerRightProneStab", 1, this, &CPlayer::Attack);


	// SlashBlust
	SetEndFunction<CPlayer>("PlayerLeftSwingT3", this, &CPlayer::SlashBlustAttackEnd);
	SetEndFunction<CPlayer>("PlayerRightSwingT3", this, &CPlayer::SlashBlustAttackEnd);

	AddNotify<CPlayer>("PlayerLeftSwingT3", 0, this, &CPlayer::SlashBlustAttack);
	AddNotify<CPlayer>("PlayerRightSwingT3", 0, this, &CPlayer::SlashBlustAttack);

	// RaisingBlow
	SetEndFunction<CPlayer>("PlayerLeftSwingTF", this, &CPlayer::RaisingBlowAttackEnd);
	SetEndFunction<CPlayer>("PlayerRightSwingTF", this, &CPlayer::RaisingBlowAttackEnd);

	AddNotify<CPlayer>("PlayerLeftSwingTF", 2, this, &CPlayer::RaisingBlowAttack);
	AddNotify<CPlayer>("PlayerRightSwingTF", 2, this, &CPlayer::RaisingBlowAttack);

	m_vecSequenceKey[0].push_back("PlayerRightStand");
	m_vecSequenceKey[0].push_back("PlayerRightWalk");
	m_vecSequenceKey[0].push_back("PlayerRightSwing");
	m_vecSequenceKey[0].push_back("PlayerRightJump");
	m_vecSequenceKey[0].push_back("PlayerRightProne");
	m_vecSequenceKey[0].push_back("PlayerRightProneStab");
	m_vecSequenceKey[0].push_back("PlayerRope");
	m_vecSequenceKey[0].push_back("PlayerRopeMove");
	m_vecSequenceKey[0].push_back("PlayerRightAlert");
	m_vecSequenceKey[0].push_back("PlayerRightAttacked");
	m_vecSequenceKey[0].push_back("PlayerRightSwingT3");
	m_vecSequenceKey[0].push_back("PlayerRightSwingTF");

	m_vecSequenceKey[1].push_back("PlayerLeftStand");
	m_vecSequenceKey[1].push_back("PlayerLeftWalk");
	m_vecSequenceKey[1].push_back("PlayerLeftSwing");
	m_vecSequenceKey[1].push_back("PlayerLeftJump");
	m_vecSequenceKey[1].push_back("PlayerLeftProne");
	m_vecSequenceKey[1].push_back("PlayerLeftProneStab");
	m_vecSequenceKey[1].push_back("PlayerRope");
	m_vecSequenceKey[1].push_back("PlayerRopeMove");
	m_vecSequenceKey[1].push_back("PlayerLeftAlert");
	m_vecSequenceKey[1].push_back("PlayerLeftAttacked");
	m_vecSequenceKey[1].push_back("PlayerLeftSwingT3");
	m_vecSequenceKey[1].push_back("PlayerLeftSwingTF");


	// 스킬 이펙트


	m_UpKey = false;
	m_DownKey = false;
	m_RightKey = false;
	m_LeftKey = false;
	m_JumpKey = false;

	m_PickUpKey = false;

	// 오른쪽 보고 있음.
	m_PlayerDir = 1;

	// 공격중이 아닐때.
	m_Attack = false;
	m_ProneAttack = false;
	m_SlashBlust = false;
	m_RaisingBlow = false;

	m_AttackDamage = 10;
	m_SlashBlustDamage = 20;
	m_RaisingBlowDamage = 30;

	// 공격후 대기 시간
	m_Alert = false;
	m_AlertTime = 0.f;
	m_AlertTimeMax = 3.f;


	// 공격당하는 중이 아님
	m_Attacked = false;
	m_AttackedTime = 0.f;
	m_AttackedTimeMax = 0.5f;

	m_Invincibility = false;
	m_InvincibilityTime = 0.f;

	m_UnalbeToMove = false;
	m_UnalbeToMoveTime = 0.f;

	// 엎드리는중이 아님
	m_Prone = false;

	// 밧줄을 타는중이 아님
	m_RopeState = false;
	m_Rope = false;
	m_RopeMove = false;

	m_PotalState = false;
	m_Potal = false;

	// 더블점프
	m_DoubleJump = false;
	m_JumpCount = 0;

	// 충돌체 추가
	CColliderBox* PlayerBody = AddCollider<CColliderBox>("Player");

	PlayerBody->SetExtent(30.f, 70.f);
	PlayerBody->SetOffset(0.f, -35.f);
	PlayerBody->SetCollisionProfile("Player");

	PlayerBody->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBegin);
	PlayerBody->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEnd);

	CInput::GetInst()->AddBindFunction<CPlayer>("UpKey", Input_Type::Push, this, &CPlayer::MoveUp);
	CInput::GetInst()->AddBindFunction<CPlayer>("UpKey", Input_Type::Up, this, &CPlayer::MoveUpCancel);
	CInput::GetInst()->AddBindFunction<CPlayer>("DownKey", Input_Type::Push, this, &CPlayer::MoveDown);
	CInput::GetInst()->AddBindFunction<CPlayer>("DownKey", Input_Type::Up, this, &CPlayer::ProneCancel);
	CInput::GetInst()->AddBindFunction<CPlayer>("RightKey", Input_Type::Push, this, &CPlayer::MoveRight);
	CInput::GetInst()->AddBindFunction<CPlayer>("RightKey", Input_Type::Up, this, &CPlayer::MoveRightCancel);
	CInput::GetInst()->AddBindFunction<CPlayer>("LeftKey", Input_Type::Push, this, &CPlayer::MoveLeft);
	CInput::GetInst()->AddBindFunction<CPlayer>("LeftKey", Input_Type::Up, this, &CPlayer::MoveLeftCancel);
	CInput::GetInst()->AddBindFunction<CPlayer>("Space", Input_Type::Down, this, &CPlayer::JumpKey);
	CInput::GetInst()->AddBindFunction<CPlayer>("Space", Input_Type::Up, this, &CPlayer::JumpKeyUp);
	CInput::GetInst()->AddBindFunction<CPlayer>("1", Input_Type::Down, this, &CPlayer::Fire);
	CInput::GetInst()->AddBindFunction<CPlayer>("2", Input_Type::Down, this, &CPlayer::SlashBlust);
	CInput::GetInst()->AddBindFunction<CPlayer>("3", Input_Type::Down, this, &CPlayer::RasingBlow);
	CInput::GetInst()->AddBindFunction<CPlayer>("Z", Input_Type::Push, this, &CPlayer::PickUp);
	CInput::GetInst()->AddBindFunction<CPlayer>("Z", Input_Type::Up, this, &CPlayer::PickUpCancel);


	m_HP = 100;
	m_HPMax = 100;

	m_MP = 100;
	m_MPMax = 100;

	m_Level = 1;
	m_EXP = 0;
	m_EXPMax[0] = 100;
	m_EXPMax[1] = 200;
	m_EXPMax[2] = 300;
	m_EXPMax[3] = 400;
	m_EXPMax[4] = 500;
	m_EXPMax[5] = 600;
	m_EXPMax[6] = 700;
	m_EXPMax[7] = 800;
	m_EXPMax[8] = 900;
	m_EXPMax[9] = 1000;


	m_NameBar = CreateWidgetComponent<CText>("NameBar");

	m_NameBar->GetWidget<CText>()->SetText(TEXT("최지훈"));
	m_NameBar->GetWidget<CText>()->EnableShadow(true);
	m_NameBar->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_NameBar->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	m_NameBar->SetPos(-25.f, 0.f);


	SetPhysicsSimulate(true);
	SetJumpVelocity(45.f);
	SetSideWallCheck(true);

	// 처음 씬에 생성 시 공중에서 떨어지므로 점프상태임
	m_Jump = true;

	return true;
}

void CPlayer::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);

	DeltaTime *= m_TimeScale;

	// 스킬 쿨타임
	size_t	Size = m_vecCoolDown.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecCoolDown[i].CoolDownEnable)
		{
			m_vecCoolDown[i].CoolDown -= DeltaTime;

			if (m_vecCoolDown[i].CoolDown <= 0.f)
				m_vecCoolDown[i].CoolDownEnable = false;
		}
	}

	if (m_HP <= 0)
	{
		m_HP = 0;
	}

	if (m_MP <= 0)
	{
		m_MP = 0;
	}

	if (m_EXP >= m_EXPMax[m_Level - 1])
	{
		if (m_Level <= 11)
		{
			// 레벨업
			m_EXP -= m_EXPMax[m_Level - 1];
			++m_Level;
			m_HPMax *= 2;
			m_MPMax *= 2;

			m_HP = m_HPMax;
			m_MP = m_MPMax;

			// 레벨 업 시 이펙트 애니메이션 동작
			CEffect* LevelUpEffect = m_Scene->CreateObject<CEffect>("LevelUpEffect");
			LevelUpEffect->SetPos(m_Pos);
			LevelUpEffect->AddAnimation("LevelUp", false, 1.5f);

			m_Scene->GetSceneResource()->SoundPlay("LevelUp");
		}
	}

	// 땅을 밟으면 점프카운트 초기화
	if (m_Ground)
	{
		m_JumpCount = 0;
		m_JumpVelocity = 45.f;
		m_MoveSpeed = 150.f;
	}

	if (!m_Attack)
	{
		CColliderBox* PlayerAttack = (CColliderBox*)FindCollider("PlayerAttack");

		if (PlayerAttack)
			PlayerAttack->SetActive(false);
	}

	if (m_Invincibility)
	{
		m_InvincibilityTime += DeltaTime;

		if (m_InvincibilityTime >= 1.5f)
		{
			m_InvincibilityTime = 0.f;
			m_Invincibility = false;
		}
	}

	
	// 공격 당한 후 대기시간
	if (m_Attacked)
	{
		m_AttackedTime += DeltaTime;
	}

	if (m_AttackedTime >= m_AttackedTimeMax)
	{
		m_Attacked = false;
		m_AttackedTime = m_AttackedTimeMax;
	}

	if (m_UnalbeToMove)
	{
		m_UnalbeToMoveTime += DeltaTime;

		if (m_UnalbeToMoveTime >= 0.3f)
		{
			m_UnalbeToMoveTime = 0.f;
			m_UnalbeToMove = false;
		}
	}

	// 공격 후 대기시간
	if (m_Alert)
		m_AlertTime += DeltaTime;

	if(m_AlertTime >= m_AlertTimeMax)
	{
		m_Alert = false;
		m_AlertTime = m_AlertTimeMax;
	}

	if (m_PotalState)
	{
		if (m_UpKey)
		{
			m_Potal = true;
		}
	}

	else
	{
		m_Potal = false;
	}

	if (m_RopeState)
	{
		if (m_UpKey || m_DownKey)
		{
			m_Rope = true;
			m_PhysicsSimulate = false;
		}
	}

	else
	{
		m_Rope = false;
		m_RopeMove = false;
	}

	// 로프에 매달린 상태에서 y방향 Move가 발생하면 RopeMove를 활성화
	if (m_Rope)
	{
		m_MoveSpeed = 150.f;

		// 로프에 매달린 상태에서 움직이면 움직이는 모션 활성화
		if (m_Move.y != 0.f)
			m_RopeMove = true;

		else
			m_RopeMove = false;


		// 로프에 매달린상태에서 왼쪽이나 오른쪽으로 점프시 로프 캔슬
		if ((m_LeftKey && m_JumpKey) || (m_RightKey && m_JumpKey))
		{
			m_Rope = false;
			m_RopeMove = false;
		}
	}

	else
	{
		m_PhysicsSimulate = true;
	}
}

void CPlayer::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);

	int	AnimDirIndex = 0;

	if (m_PlayerDir == -1)
		AnimDirIndex = 1;


	CColliderBox* PlayerBody = (CColliderBox*)FindCollider("Player");

	if (m_PlayerDir == 1)
	{
		if (m_Prone && !m_Rope)
		{
			PlayerBody->SetExtent(70.f, 30.f);
			PlayerBody->SetOffset(10.f, -15.f);
		}

		else
		{
			PlayerBody->SetExtent(30.f, 70.f);
			PlayerBody->SetOffset(0.f, -35.f);
		}
	}

	else
	{
		if (m_Prone && !m_Rope)
		{
			PlayerBody->SetExtent(70.f, 30.f);
			PlayerBody->SetOffset(-10.f, -15.f);
		}

		else
		{
			PlayerBody->SetExtent(30.f, 70.f);
			PlayerBody->SetOffset(0.f, -35.f);
		}
	}

	if (m_Rope)
	{
		if (m_RopeMove)
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EPlayer_Motion::RopeMove]);

		else
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EPlayer_Motion::Rope]);
	}

	else
	{
		if (m_SlashBlust && !m_Prone)
		{
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EPlayer_Motion::SlashBlust]);
		}

		else if (m_RaisingBlow && !m_Prone)
		{
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EPlayer_Motion::RaisingBlow]);
		}

		else if (m_Attacked)
		{
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EPlayer_Motion::Attacked]);
		}

		else if (m_Attack && !m_Prone)
		{
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EPlayer_Motion::Swing]);

			m_Alert = true;
			m_AlertTime = 0.f;
		}

		else if (m_ProneAttack && m_Prone)
		{
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EPlayer_Motion::ProneAttack]);

			m_Alert = true;
			m_AlertTime = 0.f;
		}

		else if (!m_Ground)
		{
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EPlayer_Motion::Jump]);
		}

		else if (m_Prone)
		{
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EPlayer_Motion::Prone]);

			if (m_JumpKey)
			{
				MoveDir(Vector2(0.f, 1.f));
			}
		}

		else if (m_Ground && (m_Move.x != 0.f || m_Move.y != 0.f))
		{
			// 이동을 할 경우 공격중이더라도 공격을 취소한다.
			m_Attack = false;
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EPlayer_Motion::Walk]);
		}

		else if (m_Ground && m_Alert)
		{
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EPlayer_Motion::Alert]);
		}

		else if (!m_Attack)
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][(int)EPlayer_Motion::Stand]);
	}
}

void CPlayer::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);
}

float CPlayer::InflictDamage(float Damage)
{
	Damage = CCharacter::InflictDamage(Damage);

	// 무적 상태가 아닐 떄 데미지 처리
	if (!m_Invincibility)
	{
		m_HP -= (int)Damage;
	}

	return Damage;
}

void CPlayer::Jump()
{
	if (!m_DoubleJump || m_JumpCount == 0)
	{
		if (!m_Jump)
		{
			m_Jump = true;
			m_Ground = false;

			m_FallTime = 0.f;
			m_FallStartY = m_Pos.y;

			m_DoubleJump = true;
			++m_JumpCount;
		}
	}

	else if (m_DoubleJump && m_JumpCount == 1)
	{
		// 점프를 한 상태에서 윗키를 누르고있는데 점프를 다시 했다면 위로 점프
		// 윗키를 누르고 있지 않았다면 보고 있는 방향으로 더블점프
		if (m_UpKey)
		{
			m_FallTime = 0.f;
			m_FallStartY = m_Pos.y;
			m_JumpVelocity = 60.f;
		}

		else
		{
			m_FallTime = 0.f;
			m_FallStartY = m_Pos.y;
			m_JumpVelocity = 15.f;

			m_MoveSpeed = 350.f;
			MoveDir(Vector2((float)m_PlayerDir, 0.f));
		}

		++m_JumpCount;
	}
}

void CPlayer::MoveUp()
{
	if (!m_UnalbeToMove)
	{
		// 만약 밧줄에 매달릴경우
		if (m_Rope)
			MoveDir(Vector2(0.f, -1.f));
	}

	m_UpKey = true;
}

void CPlayer::MoveUpCancel()
{
	m_UpKey = false;
}

void CPlayer::MoveDown()
{
	if (!m_UnalbeToMove)
	{
		// 만약 밧줄에 매달릴경우
		if (m_Rope)
			MoveDir(Vector2(0.f, 1.f));

		// 점프중이거나 로프에 매달린 상태에서는 엎드리기가 아님
		if ((!m_Jump && m_Ground) || m_Rope)
			m_Prone = true;
	}

	m_DownKey = true;
}

void CPlayer::ProneCancel()
{
	if (m_Prone)
		m_Prone = false;


	m_DownKey = false;
}

void CPlayer::MoveRight()
{
	if (!m_UnalbeToMove)
	{
		if (!m_Prone)
		{
			if (!m_Rope)
			{
				MoveDir(Vector2(1.f, 0.f));
				m_PlayerDir = 1;
			}
		}
	}

	m_RightKey = true;
}

void CPlayer::MoveRightCancel()
{
	m_RightKey = false;
}

void CPlayer::MoveLeft()
{
	if (!m_UnalbeToMove)
	{
		if (!m_Prone)
		{
			if (!m_Rope)
			{
				MoveDir(Vector2(-1.f, 0.f));
				m_PlayerDir = -1;
			}
		}
	}

	m_LeftKey = true;
}

void CPlayer::MoveLeftCancel()
{
	m_LeftKey = false;
}

void CPlayer::Fire()
{
	if (!m_Rope)
	{
		if (m_Attack)
			return;

		else if (m_ProneAttack)
			return;

		if (m_Prone)
			m_ProneAttack = true;

		m_Attack = true;
	}
}

void CPlayer::JumpKey()
{
	m_JumpKey = true;

	if (!m_Prone)
	{
		Jump();

		m_Scene->GetSceneResource()->SoundPlay("Jump");
	}
}

void CPlayer::JumpKeyUp()
{
	m_JumpKey = false;
}

void CPlayer::SlashBlust()
{
	if (m_MP >= 10)
	{
		m_MP -= 10;

		// 이펙트 설정
		CEffect* Effect = m_Scene->CreateObject<CEffect>("SlashBlust");

		if (m_PlayerDir == 1)
		{
			Effect->SetPivot(0.f, 0.5f);
			Effect->SetPos(m_Pos.x + 25.f, m_Pos.y - 35.f);
			Effect->AddAnimation("SlashBlustRight", false, 0.5f);
		}

		else if (m_PlayerDir == -1)
		{
			Effect->SetPivot(1.f, 0.5f);
			Effect->SetPos(m_Pos.x - 25.f, m_Pos.y - 35.f);
			Effect->AddAnimation("SlashBlustLeft", false, 0.5f);
		}

		m_Scene->GetSceneResource()->SoundPlay("SlashBlust");

		m_SlashBlust = true;

		m_Alert = true;
		m_AlertTime = 0.f;
	}
}

void CPlayer::RasingBlow()
{
	if (m_MP >= 20)
	{
		m_MP -= 20;

		// 이펙트 설정
		CEffect* Effect = m_Scene->CreateObject<CEffect>("RaisingBlow");

		if (m_PlayerDir == 1)
		{
			Effect->SetPos(m_Pos.x + 25.f, m_Pos.y - 35.f);
			Effect->AddAnimation("RaisingBlowRight", false, 0.8f);
		}

		else if (m_PlayerDir == -1)
		{
			Effect->SetPos(m_Pos.x - 25.f, m_Pos.y - 35.f);
			Effect->AddAnimation("RaisingBlowLeft", false, 0.8f);
		}

		m_Scene->GetSceneResource()->SoundPlay("RaisingBlow");

		m_RaisingBlow = true;

		m_Alert = true;
		m_AlertTime = 0.f;
	}
}

void CPlayer::PickUp()
{
	m_PickUpKey = true;
}

void CPlayer::PickUpCancel()
{
	m_PickUpKey = false;
}

void CPlayer::AttackEnd()
{
	CColliderBox* PlayerAttack = (CColliderBox*)FindCollider("PlayerAttack");

	if (PlayerAttack)
		PlayerAttack->SetActive(false);

	m_Attack = false;
	m_ProneAttack = false;
}

void CPlayer::Attack()
{
	// 기본 공격시 캐릭터 앞쪽에 일정 범위를 지정해서 Box로 Collider 생성
	CColliderBox* PlayerAttack = AddCollider<CColliderBox>("PlayerAttack");
	PlayerAttack->SetCollisionProfile("PlayerAttack");
	PlayerAttack->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::AttackCollisionBegin);
	PlayerAttack->SetCollisionEndFunction<CPlayer>(this, &CPlayer::AttackCollisionEnd);

	if (m_PlayerDir == 1)
	{
		if (m_Prone)
		{
			PlayerAttack->SetExtent(130.f, 30.f);
			PlayerAttack->SetOffset(40.f, -15.f);
		}

		else
		{
			PlayerAttack->SetExtent(100.f, 70.f);
			PlayerAttack->SetOffset(35.f, -35.f);
		}
	}

	else if(m_PlayerDir == -1)
	{
		if (m_Prone)
		{
			PlayerAttack->SetExtent(130.f, 30.f);
			PlayerAttack->SetOffset(-40.f, -15.f);
		}

		else
		{
			PlayerAttack->SetExtent(100.f, 70.f);
			PlayerAttack->SetOffset(-35.f, -35.f);
		}
	}
}

void CPlayer::SlashBlustAttack()
{
	CColliderBox* SlashBlustAttack = AddCollider<CColliderBox>("SlashBlustAttack");
	SlashBlustAttack->SetCollisionProfile("PlayerAttack");
	SlashBlustAttack->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::SlashBlustCollisionBegin);
	SlashBlustAttack->SetCollisionEndFunction<CPlayer>(this, &CPlayer::SlashBlustCollisionEnd);

	SlashBlustAttack->SetExtent(400.f, 200.f);

	if (m_PlayerDir == 1)
	{
		SlashBlustAttack->SetOffset(225.f, - 35.f);
	}
	
	else
	{
		SlashBlustAttack->SetOffset(- 225.f, - 35.f);
	}
}

void CPlayer::SlashBlustAttackEnd()
{
	CCollider* SlashBlustAttack = FindCollider("SlashBlustAttack");

	if (SlashBlustAttack)
		SlashBlustAttack->SetActive(false);

	m_SlashBlust = false;
}

void CPlayer::RaisingBlowAttack()
{
	CColliderBox* RaisingBlowAttack = AddCollider<CColliderBox>("RaisingBlowAttack");
	RaisingBlowAttack->SetCollisionProfile("PlayerAttack");
	RaisingBlowAttack->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::RaisingBlowCollisionBegin);
	RaisingBlowAttack->SetCollisionEndFunction<CPlayer>(this, &CPlayer::RaisingBlowCollisionEnd);

	RaisingBlowAttack->SetExtent(500.f, 200.f);

	if (m_PlayerDir == 1)
	{
		RaisingBlowAttack->SetOffset(125.f, -35.f);
	}

	else
	{
		RaisingBlowAttack->SetOffset(-125.f, -35.f);
	}
}

void CPlayer::RaisingBlowAttackEnd()
{
	CCollider* RaisingBlowAttack = FindCollider("RaisingBlowAttack");

	if (RaisingBlowAttack)
		RaisingBlowAttack->SetActive(false);

	m_RaisingBlow = false;
}

void CPlayer::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	if (!m_Invincibility)
	{
		if (Dest->GetProfile()->Channel == ECollision_Channel::Monster ||
			Dest->GetProfile()->Channel == ECollision_Channel::MonsterAttack)
		{
			// 공격당하면 뒤로 밀림, 로프에 매달린 상태였다면 로프에서 떨어짐
			if (m_Rope)
			{
				m_Rope = false;
			}

			MoveDir(Vector2((float)(m_PlayerDir * -50), -40.f));
			m_Attacked = true;
			m_AttackedTime = 0.f;

			m_UnalbeToMove = true;
			m_UnalbeToMoveTime = 0.f;


			m_Invincibility = true;
			m_InvincibilityTime = 0.f;

			SetRenderState(false);
		}
	}

	if (Dest->GetProfile()->Channel == ECollision_Channel::Rope)
	{
		m_RopeState = true;
	}

	if (Dest->GetProfile()->Channel == ECollision_Channel::Potal)
	{
		m_PotalState = true;
	}
}

void CPlayer::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	if (Dest->GetProfile()->Channel == ECollision_Channel::Rope)
	{
		m_RopeState = false;
	}

	if (Dest->GetProfile()->Channel == ECollision_Channel::Potal)
	{
		m_PotalState = false;
	}
}

void CPlayer::AttackCollisionBegin(CCollider* Src, CCollider* Dest)
{
	Dest->GetOwner()->InflictDamage((float)m_AttackDamage);

	CCollider* AttackCollider = FindCollider("PlayerAttack");

	if (AttackCollider)
	{
		AttackCollider->SetActive(false);
		Dest->DeleteCollisionList(AttackCollider);
	}
}

void CPlayer::AttackCollisionEnd(CCollider* Src, CCollider* Dest)
{
}

void CPlayer::SlashBlustCollisionBegin(CCollider* Src, CCollider* Dest)
{
	Dest->GetOwner()->InflictDamage((float)m_SlashBlustDamage);

	CCollider* SlashBlustAttack = FindCollider("SlashBlustAttack");

	if (SlashBlustAttack)
	{
		SlashBlustAttack->SetActive(false);
		Dest->DeleteCollisionList(SlashBlustAttack);
	}
}

void CPlayer::SlashBlustCollisionEnd(CCollider* Src, CCollider* Dest)
{
}

void CPlayer::RaisingBlowCollisionBegin(CCollider* Src, CCollider* Dest)
{
	Dest->GetOwner()->InflictDamage((float)m_RaisingBlowDamage);

	CCollider* RaisingBlowAttack = FindCollider("RaisingBlowAttack");

	if (RaisingBlowAttack)
	{
		RaisingBlowAttack->SetActive(false);
		Dest->DeleteCollisionList(RaisingBlowAttack);
	}
}

void CPlayer::RaisingBlowCollisionEnd(CCollider* Src, CCollider* Dest)
{
}
