#include "TheSeed50F.h"
#include "../GameObject/Player.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "../GameObject/TileMap.h"
#include "../Resource/ResourceManager.h"
#include "../Collision/ColliderBox.h"
#include "../GameObject/GameObject.h"
#include "SceneManager.h"
#include "TheSeed2F.h"
#include "../GameObject/Dorothy.h"
#include "../GameObject/MeteorRed.h"
#include "../GameObject/MeteorPurple.h"
#include "../GameObject/MeteorPink.h"
#include "../Widget/CharacterStatus.h"
#include "../GameManager.h"
#include "../Widget/DorothyHP.h"
#include "../GameObject/Effect.h"

CTheSeed50F::CTheSeed50F()
{
}

CTheSeed50F::~CTheSeed50F()
{
}

bool CTheSeed50F::Init()
{
	if (!CScene::Init())
		return false;

	CreateAnimationSequence();

	// 맵 Sound 로딩
	GetSceneResource()->LoadSound("BGM", "TheSeed50F_BGM", true, "MapleStory/StrangeSortOfStory.mp3");
	GetSceneResource()->LoadSound("Map", "Portal", false, "MapleStory/Portal.mp3");
	GetSceneResource()->SoundPlay("TheSeed50F_BGM");
	GetSceneResource()->SetVolume(20);

	// 캐릭터용 Sound 로딩
	GetSceneResource()->LoadSound("Character", "Jump", false, "MapleStory/Jump.mp3");
	GetSceneResource()->LoadSound("Character", "SlashBlust", false, "MapleStory/SlashBlust.mp3");
	GetSceneResource()->LoadSound("Character", "RaisingBlow", false, "MapleStory/RaisingBlow.mp3");
	GetSceneResource()->LoadSound("Character", "LevelUp", false, "MapleStory/LevelUp.mp3");

	// 몬스터용 Sound 로딩
	GetSceneResource()->LoadSound("Monster", "DorothyAttack", false, "MapleStory/Dorothy_Attack.mp3");
	GetSceneResource()->LoadSound("Monster", "DorothyDie", false, "MapleStory/Dorothy_Die.mp3");
	GetSceneResource()->LoadSound("Monster", "DorothyHit", false, "MapleStory/Dorothy_Hit.mp3");
	GetSceneResource()->LoadSound("Monster", "DorothySkill1", false, "MapleStory/Dorothy_Skill1.mp3");
	GetSceneResource()->LoadSound("Monster", "DorothySkill2", false, "MapleStory/Dorothy_Skill2.mp3");
	GetSceneResource()->SetVolume("Monster", 30);

	// 카메라 설정
	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(2140.f, 750.f);
	GetCamera()->SetTargetPivot(0.5f, 0.7f);

	// 플레이어 세팅
	CPlayer* Player = CreateObject<CPlayer>("Player");
	SetPlayer(Player);
	Player->SetPos(1250.f, 600.f);
	Player->SetFallStartY(600.f);
	GetCamera()->SetTarget(Player);

	// 타일맵 세팅
	CTileMap* TheSeed50F = CreateObject<CTileMap>("TheSeed50F");
	TheSeed50F->LoadFileName("TheSeed50F.tmp", MAP_PATH);

	// 몬스터 세팅
	// 도로시 추가해야함
	m_Dorothy = CreateObject<CDorothy>("Dorothy");
	m_Dorothy->SetPos(1900.f, 650.f);
	m_Dorothy->SetPhysicsSimulate(false);

	// 도로시 HP용 UI
	m_DorothyHP = CreateWidgetWindow<CDorothyHP>("DorothyHP");


	// 포탈 상호작용 충돌체 설정
	CColliderBox* Potal = TheSeed50F->AddCollider<CColliderBox>("Potal");
	Potal->SetExtent(30.f, 1.f);
	Potal->SetOffset(100.f, 650.f);
	Potal->SetCollisionProfile("Potal");
	Potal->SetEnable(false); // 도로시 처치 시 활성화 필요

	m_MeteorRegenTime = 0.f;

	for (int i = 0; i < 21; ++i)
	{
		m_MeteorInfo[i].Create = false;
		m_MeteorInfo[i].PosX = 100.f * i + 650.f;
	}

	m_CharacterStatus = CreateWidgetWindow<CCharacterStatus>("CharacterStatus");

	srand((unsigned int)time(0));

	int Random = rand();

	return true;
}

void CTheSeed50F::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);

	// 5초마다 한번씩 운석 생성
	// 운석 종류와 운석의 속도는 랜덤하게
	m_MeteorRegenTime += DeltaTime;

	if (m_MeteorRegenTime >= 5.f)
	{
		m_MeteorRegenTime -= 5.f;

		CreateMeteor();
	}

	for (int i = 0; i < 21; ++i)
	{
		m_MeteorInfo[i].Create = false;
	}
}

void CTheSeed50F::PostUpdate(float DeltaTime)
{
	CScene::PostUpdate(DeltaTime);

	CPlayer* Player = (CPlayer*)m_Player.Get();

	if (Player->GetPotal())
	{
		CGameManager::GetInst()->Exit();
	}
}

void CTheSeed50F::CreateMeteor()
{
	// 21군데 중 한 곳에 랜덤으로 생성

	// 메테오는 3 ~ 10개
	int MeteorNumber = rand() % 8 + 3;

	for (int i = 0; i < MeteorNumber; ++i)
	{
		int MeteorInfoIndex = rand() % 21;

		int Meteor = rand() % 3;

		float MeteorSpeed = (rand() % 3 + 1) * 100.f;

		if (m_MeteorInfo[MeteorInfoIndex].Create == false)
		{
			// 생성되어 있지 않다면 Meteor 생성
			if (Meteor == 0)
			{
				CMeteorRed* MeteorRed = CreateObject<CMeteorRed>("MeteorRed");

				MeteorRed->SetPos(m_MeteorInfo[MeteorInfoIndex].PosX, 0.f);

				MeteorRed->SetMoveSpeed(MeteorSpeed);

				m_MeteorInfo[MeteorInfoIndex].Create = true;
			}

			else if (Meteor == 1)
			{
				CMeteorPurple* MeteorPurple = CreateObject<CMeteorPurple>("MeteorPurple");

				MeteorPurple->SetPos(m_MeteorInfo[MeteorInfoIndex].PosX, 0.f);

				MeteorPurple->SetMoveSpeed(MeteorSpeed);

				m_MeteorInfo[MeteorInfoIndex].Create = true;
			}

			else
			{
				CMeteorPink * MeteorPink = CreateObject<CMeteorPink>("MeteorPink");

				MeteorPink->SetPos(m_MeteorInfo[MeteorInfoIndex].PosX, 0.f);

				MeteorPink->SetMoveSpeed(MeteorSpeed);

				m_MeteorInfo[MeteorInfoIndex].Create = true;
			}
		}
	}
}

void CTheSeed50F::DorothyDie()
{
	CCollider* Potal = GetTileMap()->FindCollider("Potal");

	Potal->SetEnable(true);

	CEffect* ClearEffect = CreateObject<CEffect>("50FClearEffect");
	ClearEffect->AddAnimation("Clear", false, 1.5f);
	ClearEffect->SetPos(GetCamera()->GetPos() + Vector2(640.f, 200.f));
}

CDorothy* CTheSeed50F::GetDorothy()
{
	return m_Dorothy.Get();
}

void CTheSeed50F::CreateAnimationSequence()
{
	//PlayerAnimationSequence();
	
	//PlayerEffectAnimationSequence();

	MonsterAnimationSequence();


	//std::vector<std::wstring>	vecFileName;

	//for (int i = 0; i <= 11; ++i)
	//{
	//	TCHAR	FileName[MAX_PATH] = {};
	//	wsprintf(FileName, TEXT("MapleStory/UI/clear_%d.bmp"), i);
	//	vecFileName.push_back(FileName);
	//}

	//CResourceManager::GetInst()->CreateAnimationSequence("Clear",
	//	"Clear", vecFileName, TEXTURE_PATH);

	//CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 127.f, 149.f, 193 / 127.f, 122 / 149.f);
	//CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 200.f, 113.f, 163 / 200.f, 100 / 113.f);
	//CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 262.f, 112.f, 165 / 262.f, 99 / 112.f);
	//CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 331.f, 110.f, 164 / 331.f, 98 / 110.f);
	//CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 341.f, 138.f, 161 / 341.f, 113 / 138.f);
	//CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 349.f, 158.f, 161 / 349.f, 123 / 158.f);
	//CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 345.f, 151.f, 161 / 345.f, 119 / 151.f);
	//CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 323.f, 100.f, 161 / 323.f, 93 / 100.f);
	//CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 398.f, 119.f, 197 / 398.f, 108 / 119.f);
	//CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 418.f, 125.f, 207 / 418.f, 110 / 125.f);
	//CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 357.f, 102.f, 178 / 357.f, 94 / 102.f);
	//CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 347.f, 92.f, 173 / 347.f, 89 / 92.f);

	//CResourceManager::GetInst()->SetColorKey("Clear", 255, 0, 255);
}

void CTheSeed50F::PlayerAnimationSequence()
{
	std::vector<std::wstring>	vecFileName;

	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Left/Player_Alert_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerLeftAlert",
		"PlayerLeftAlert", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftAlert", 0.f, 0.f, 106.f, 66.f, 0.78f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftAlert", 0.f, 0.f, 106.f, 67.f, 0.78f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftAlert", 0.f, 0.f, 106.f, 68.f, 0.78f, 1.f);

	CResourceManager::GetInst()->SetColorKey("PlayerLeftAlert", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Right/Player_Alert_Right_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerRightAlert",
		"PlayerRightAlert", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightAlert", 0.f, 0.f, 106.f, 66.f, 0.22f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightAlert", 0.f, 0.f, 106.f, 67.f, 0.22f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightAlert", 0.f, 0.f, 106.f, 68.f, 0.22f, 1.f);

	CResourceManager::GetInst()->SetColorKey("PlayerRightAlert", 255, 0, 255);


	GetSceneResource()->CreateAnimationSequence("PlayerLeftJump",
		"PlayerLeftJump", TEXT("MapleStory/Player/Left/Player_Jump_0.bmp"), TEXTURE_PATH);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftJump", 0.f, 0.f, 60.f, 100.f, 0.33f, 1.f);
	CResourceManager::GetInst()->SetColorKey("PlayerLeftJump", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerRightJump",
		"PlayerRightJump", TEXT("MapleStory/Player/Right/Player_Jump_Right_0.bmp"), TEXTURE_PATH);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightJump", 0.f, 0.f, 60.f, 100.f, 0.66f, 1.f);
	CResourceManager::GetInst()->SetColorKey("PlayerRightJump", 255, 0, 255);



	GetSceneResource()->CreateAnimationSequence("PlayerLeftProne",
		"PlayerLeftProne", TEXT("MapleStory/Player/Left/Player_Prone_0.bmp"), TEXTURE_PATH);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftProne", 0.f, 0.f, 127.f, 52.f, 0.85f, 0.77f);
	CResourceManager::GetInst()->SetColorKey("PlayerLeftProne", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerRightProne",
		"PlayerRightProne", TEXT("MapleStory/Player/Right/Player_Prone_Right_0.bmp"), TEXTURE_PATH);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightProne", 0.f, 0.f, 127.f, 52.f, 0.15f, 0.77f);
	CResourceManager::GetInst()->SetColorKey("PlayerRightProne", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Left/Player_Stand_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerLeftStand",
		"PlayerLeftStand", vecFileName, TEXTURE_PATH);

	for (int i = 0; i <= 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerLeftStand", 0.f, 0.f, 72.f, 81.f, 0.54f, 0.83f);
	}

	GetSceneResource()->SetColorKey("PlayerLeftStand", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Right/Player_Stand_Right_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerRightStand",
		"PlayerRightStand", vecFileName, TEXTURE_PATH);

	for (int i = 0; i <= 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerRightStand", 0.f, 0.f, 72.f, 81.f, 0.46f, 0.83f);
	}

	GetSceneResource()->SetColorKey("PlayerRightStand", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Left/Player_SwingT1_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerLeftSwing",
		"PlayerLeftSwing", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftSwing", 0.f, 0.f, 114.f, 70.f, 0.17f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftSwing", 0.f, 0.f, 46.f, 117.f, 0.65f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftSwing", 0.f, 0.f, 125.f, 80.f, 0.85f, 0.76f);

	GetSceneResource()->SetColorKey("PlayerLeftSwing", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Right/Player_SwingT1_Right_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerRightSwing",
		"PlayerRightSwing", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightSwing", 0.f, 0.f, 114.f, 70.f, 0.83f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightSwing", 0.f, 0.f, 46.f, 117.f, 0.35f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightSwing", 0.f, 0.f, 125.f, 80.f, 0.15f, 0.76f);

	GetSceneResource()->SetColorKey("PlayerRightSwing", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Left/Player_SwingT3_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerLeftSwingT3",
		"PlayerLeftSwingT3", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftSwingT3", 0.f, 0.f, 123.f, 68.f, 0.2f, 0.98f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftSwingT3", 0.f, 0.f, 123.f, 72.f, 0.28f, 0.83f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftSwingT3", 0.f, 0.f, 57.f, 116.f, 0.66f, 1.f);

	GetSceneResource()->SetColorKey("PlayerLeftSwingT3", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Right/Player_SwingT3_Right_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerRightSwingT3",
		"PlayerRightSwingT3", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightSwingT3", 0.f, 0.f, 123.f, 68.f, 0.8f, 0.98f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightSwingT3", 0.f, 0.f, 123.f, 72.f, 0.72f, 0.83f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightSwingT3", 0.f, 0.f, 57.f, 116.f, 0.34f, 1.f);

	GetSceneResource()->SetColorKey("PlayerRightSwingT3", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Left/Player_SwingTF_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerLeftSwingTF",
		"PlayerLeftSwingTF", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftSwingTF", 0.f, 0.f, 66.f, 122.f, 0.68f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftSwingTF", 0.f, 0.f, 46.f, 120.f, 0.45f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftSwingTF", 0.f, 0.f, 61.f, 118.f, 0.5f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftSwingTF", 0.f, 0.f, 121.f, 77.f, 0.84f, 0.78f);

	GetSceneResource()->SetColorKey("PlayerLeftSwingTF", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Right/Player_SwingTF_Right_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerRightSwingTF",
		"PlayerRightSwingTF", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightSwingTF", 0.f, 0.f, 66.f, 122.f, 0.32f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightSwingTF", 0.f, 0.f, 46.f, 120.f, 0.55f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightSwingTF", 0.f, 0.f, 61.f, 118.f, 0.5f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightSwingTF", 0.f, 0.f, 121.f, 77.f, 0.16f, 0.78f);

	GetSceneResource()->SetColorKey("PlayerRightSwingTF", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Left/Player_Walk_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerLeftWalk",
		"PlayerLeftWalk", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftWalk", 0.f, 0.f, 100.f, 69.f, 0.77f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftWalk", 0.f, 0.f, 102.f, 68.f, 0.75f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftWalk", 0.f, 0.f, 100.f, 69.f, 0.75f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftWalk", 0.f, 0.f, 96.f, 74.f, 0.72f, 0.89f);

	GetSceneResource()->SetColorKey("PlayerLeftWalk", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Right/Player_Walk_Right_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerRightWalk",
		"PlayerRightWalk", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightWalk", 0.f, 0.f, 100.f, 69.f, 0.23f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightWalk", 0.f, 0.f, 102.f, 68.f, 0.25f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightWalk", 0.f, 0.f, 100.f, 69.f, 0.25f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightWalk", 0.f, 0.f, 96.f, 74.f, 0.28f, 0.89f);

	GetSceneResource()->SetColorKey("PlayerRightWalk", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 1; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Left/Player_ProneStab_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerLeftProneStab",
		"PlayerLeftProneStab", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftProneStab", 0.f, 0.f, 127.f, 52.f, 0.85f, 0.77f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftProneStab", 0.f, 0.f, 142.f, 52.f, 0.87f, 0.77f);

	GetSceneResource()->SetColorKey("PlayerLeftProneStab", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 1; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Right/Player_ProneStab_Right_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerRightProneStab",
		"PlayerRightProneStab", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightProneStab", 0.f, 0.f, 127.f, 52.f, 0.15f, 0.77f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightProneStab", 0.f, 0.f, 142.f, 52.f, 0.13f, 0.77f);

	GetSceneResource()->SetColorKey("PlayerRightProneStab", 255, 0, 255);


	CResourceManager::GetInst()->CreateAnimationSequence("PlayerRope",
		"PlayerRope", TEXT("MapleStory/Player/Left/Player_Rope_0.bmp"), TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerRope", 0.f, 0.f, 72.f, 72.f, 0.5f, 1.f);

	GetSceneResource()->SetColorKey("PlayerRope", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 1; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Left/Player_Rope_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerRopeMove",
		"PlayerRopeMove", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerRopeMove", 0.f, 0.f, 72.f, 72.f, 0.5f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRopeMove", 0.f, 0.f, 72.f, 72.f, 0.5f, 1.f);

	GetSceneResource()->SetColorKey("PlayerRopeMove", 255, 0, 255);


	CResourceManager::GetInst()->CreateAnimationSequence("PlayerLeftAttacked",
		"PlayerLeftAttacked", TEXT("MapleStory/Player/Left/Player_Attacked_0.bmp"), TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftAttacked", 0.f, 0.f, 106.f, 66.f, 0.78f, 1.f);

	GetSceneResource()->SetColorKey("PlayerLeftAttacked", 255, 0, 255);


	CResourceManager::GetInst()->CreateAnimationSequence("PlayerRightAttacked",
		"PlayerRightAttacked", TEXT("MapleStory/Player/Right/Player_Attacked_0_Right.bmp"), TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightAttacked", 0.f, 0.f, 106.f, 66.f, 0.22f, 1.f);

	GetSceneResource()->SetColorKey("PlayerRightAttacked", 255, 0, 255);
}

void CTheSeed50F::PlayerEffectAnimationSequence()
{
	std::vector<std::wstring>	vecFileName;

	for (int i = 0; i <= 20; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/SkillEffect/LevelUp%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("LevelUp",
		"LevelUp", vecFileName, TEXTURE_PATH);

	for (int i = 0; i <= 20; ++i)
	{
		CResourceManager::GetInst()->AddAnimationFrame("LevelUp", 0.f, 0.f, 904.f, 904.f, 0.5f, 472 / 904.f);
	}

	CResourceManager::GetInst()->SetColorKey("LevelUp", 255, 0, 255);



	vecFileName.clear();

	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/SkillEffect/Left/SlashBlust_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("SlashBlustLeft",
		"SlashBlustLeft", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("SlashBlustLeft", 0.f, 0.f, 444.f, 224.f);
	CResourceManager::GetInst()->AddAnimationFrame("SlashBlustLeft", 0.f, 0.f, 392.f, 220.f);
	CResourceManager::GetInst()->AddAnimationFrame("SlashBlustLeft", 0.f, 0.f, 384.f, 216.f);
	CResourceManager::GetInst()->AddAnimationFrame("SlashBlustLeft", 0.f, 0.f, 388.f, 208.f);
	CResourceManager::GetInst()->AddAnimationFrame("SlashBlustLeft", 0.f, 0.f, 388.f, 208.f);
	CResourceManager::GetInst()->AddAnimationFrame("SlashBlustLeft", 0.f, 0.f, 380.f, 204.f);

	CResourceManager::GetInst()->SetColorKey("SlashBlustLeft", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/SkillEffect/Right/SlashBlust_Right_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("SlashBlustRight",
		"SlashBlustRight", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("SlashBlustRight", 0.f, 0.f, 444.f, 224.f);
	CResourceManager::GetInst()->AddAnimationFrame("SlashBlustRight", 0.f, 0.f, 392.f, 220.f);
	CResourceManager::GetInst()->AddAnimationFrame("SlashBlustRight", 0.f, 0.f, 384.f, 216.f);
	CResourceManager::GetInst()->AddAnimationFrame("SlashBlustRight", 0.f, 0.f, 388.f, 208.f);
	CResourceManager::GetInst()->AddAnimationFrame("SlashBlustRight", 0.f, 0.f, 388.f, 208.f);
	CResourceManager::GetInst()->AddAnimationFrame("SlashBlustRight", 0.f, 0.f, 380.f, 204.f);

	CResourceManager::GetInst()->SetColorKey("SlashBlustRight", 255, 0, 255);

	vecFileName.clear();

	for (int i = 1; i <= 14; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/SkillEffect/Left/RaisingBlow_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("RaisingBlowLeft",
		"RaisingBlowLeft", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowLeft", 0.f, 0.f, 344.f, 140.f, 0.f, 0.5f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowLeft", 0.f, 0.f, 376.f, 148.f, 0.f, 0.5f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowLeft", 0.f, 0.f, 400.f, 156.f, 0.f, 0.5f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowLeft", 0.f, 0.f, 740.f, 440.f, 0.4f, 0.5f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowLeft", 0.f, 0.f, 752.f, 428.f, 0.44f, 0.5f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowLeft", 0.f, 0.f, 760.f, 420.f, 0.44f, 0.5f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowLeft", 0.f, 0.f, 752.f, 380.f, 0.43f, 0.5f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowLeft", 0.f, 0.f, 760.f, 368.f, 0.68f, 0.63f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowLeft", 0.f, 0.f, 640.f, 380.f, 0.66f, 0.6f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowLeft", 0.f, 0.f, 628.f, 388.f, 0.62f, 0.6f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowLeft", 0.f, 0.f, 612.f, 384.f, 0.59f, 0.6f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowLeft", 0.f, 0.f, 612.f, 352.f, 0.55f, 0.6f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowLeft", 0.f, 0.f, 596.f, 340.f, 0.56f, 0.58f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowLeft", 0.f, 0.f, 380.f, 284.f, 0.87f, 0.62f);

	CResourceManager::GetInst()->SetColorKey("RaisingBlowLeft", 255, 0, 255);

	vecFileName.clear();

	for (int i = 1; i <= 14; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/SkillEffect/Right/RaisingBlow_Right_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("RaisingBlowRight",
		"RaisingBlowRight", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowRight", 0.f, 0.f, 344.f, 140.f, 1.f, 0.5f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowRight", 0.f, 0.f, 376.f, 148.f, 1.f, 0.5f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowRight", 0.f, 0.f, 400.f, 156.f, 1.f, 0.5f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowRight", 0.f, 0.f, 740.f, 440.f, 0.6f, 0.5f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowRight", 0.f, 0.f, 752.f, 428.f, 0.56f, 0.5f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowRight", 0.f, 0.f, 760.f, 420.f, 0.56f, 0.5f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowRight", 0.f, 0.f, 752.f, 380.f, 0.57f, 0.5f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowRight", 0.f, 0.f, 760.f, 368.f, 0.32f, 0.63f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowRight", 0.f, 0.f, 640.f, 380.f, 0.34f, 0.6f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowRight", 0.f, 0.f, 628.f, 388.f, 0.38f, 0.6f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowRight", 0.f, 0.f, 612.f, 384.f, 0.41f, 0.6f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowRight", 0.f, 0.f, 612.f, 352.f, 0.45f, 0.6f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowRight", 0.f, 0.f, 596.f, 340.f, 0.44f, 0.58f);
	CResourceManager::GetInst()->AddAnimationFrame("RaisingBlowRight", 0.f, 0.f, 380.f, 284.f, 0.13f, 0.62f);

	CResourceManager::GetInst()->SetColorKey("RaisingBlowRight", 255, 0, 255);
}

void CTheSeed50F::MonsterAnimationSequence()
{
	std::vector<std::wstring>	vecFileName;

	for (int i = 0; i <= 7; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_50F/Monster/Dorothy_Stand_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("DorothyStand",
		"DorothyStand", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("DorothyStand", 0.f, 0.f, 110.f, 119.f, 65 / 110.f, 143 / 119.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyStand", 0.f, 0.f, 111.f, 119.f, 65 / 111.f, 142 / 119.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyStand", 0.f, 0.f, 111.f, 119.f, 64 / 111.f, 141 / 119.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyStand", 0.f, 0.f, 109.f, 119.f, 63 / 109.f, 142 / 119.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyStand", 0.f, 0.f, 108.f, 119.f, 62 / 108.f, 143 / 119.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyStand", 0.f, 0.f, 108.f, 119.f, 63 / 108.f, 144 / 119.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyStand", 0.f, 0.f, 108.f, 119.f, 64 / 108.f, 145 / 119.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyStand", 0.f, 0.f, 110.f, 119.f, 65 / 110.f, 144 / 119.f);

	CResourceManager::GetInst()->SetColorKey("DorothyStand", 255, 0, 255);

	vecFileName.clear();


	for (int i = 0; i <= 16; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_50F/Monster/Dorothy_Attack_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("DorothyAttack",
		"DorothyAttack", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("DorothyAttack", 0.f, 0.f, 110.f, 119.f, 65 / 110.f, 143 / 119.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyAttack", 0.f, 0.f, 201.f, 134.f, 101 / 201.f, 142 / 134.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyAttack", 0.f, 0.f, 207.f, 136.f, 104 / 207.f, 141 / 136.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyAttack", 0.f, 0.f, 211.f, 139.f, 106 / 211.f, 142 / 139.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyAttack", 0.f, 0.f, 213.f, 142.f, 107 / 213.f, 144 / 142.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyAttack", 0.f, 0.f, 213.f, 143.f, 107 / 213.f, 145 / 143.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyAttack", 0.f, 0.f, 213.f, 144.f, 107 / 213.f, 146 / 144.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyAttack", 0.f, 0.f, 213.f, 144.f, 107 / 213.f, 146 / 144.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyAttack", 0.f, 0.f, 213.f, 144.f, 107 / 213.f, 146 / 144.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyAttack", 0.f, 0.f, 213.f, 144.f, 107 / 213.f, 146 / 144.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyAttack", 0.f, 0.f, 213.f, 259.f, 107 / 213.f, 261 / 259.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyAttack", 0.f, 0.f, 213.f, 260.f, 107 / 213.f, 262 / 260.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyAttack", 0.f, 0.f, 213.f, 260.f, 107 / 213.f, 262 / 260.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyAttack", 0.f, 0.f, 211.f, 233.f, 106 / 211.f, 236 / 233.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyAttack", 0.f, 0.f, 207.f, 232.f, 104 / 207.f, 237 / 232.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyAttack", 0.f, 0.f, 201.f, 230.f, 101 / 201.f, 238 / 230.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyAttack", 0.f, 0.f, 112.f, 205.f, 53 / 112.f, 233 / 205.f);

	CResourceManager::GetInst()->SetColorKey("DorothyAttack", 255, 0, 255);

	vecFileName.clear();


	for (int i = 0; i <= 15; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_50F/Monster/Dorothy_Skill1_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("DorothySkill1",
		"DorothySkill1", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill1", 0.f, 0.f, 108.f, 119.f, 65 / 108.f, 143 / 119.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill1", 0.f, 0.f, 290.f, 186.f, 230 / 290.f, 187 / 186.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill1", 0.f, 0.f, 291.f, 187.f, 229 / 291.f, 188 / 187.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill1", 0.f, 0.f, 291.f, 188.f, 229 / 291.f, 189 / 188.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill1", 0.f, 0.f, 291.f, 190.f, 229 / 291.f, 191 / 190.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill1", 0.f, 0.f, 291.f, 191.f, 229 / 291.f, 192 / 191.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill1", 0.f, 0.f, 288.f, 188.f, 226 / 288.f, 189 / 188.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill1", 0.f, 0.f, 236.f, 182.f, 192 / 236.f, 186 / 182.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill1", 0.f, 0.f, 218.f, 166.f, 175 / 218.f, 173 / 166.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill1", 0.f, 0.f, 256.f, 248.f, 214 / 256.f, 246 / 248.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill1", 0.f, 0.f, 267.f, 256.f, 223 / 267.f, 255 / 256.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill1", 0.f, 0.f, 272.f, 258.f, 228 / 272.f, 258 / 258.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill1", 0.f, 0.f, 275.f, 201.f, 229 / 275.f, 204 / 201.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill1", 0.f, 0.f, 272.f, 179.f, 228 / 272.f, 182 / 179.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill1", 0.f, 0.f, 269.f, 167.f, 225 / 269.f, 170 / 167.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill1", 0.f, 0.f, 271.f, 141.f, 226 / 271.f, 145 / 141.f);

	CResourceManager::GetInst()->SetColorKey("DorothySkill1", 255, 0, 255);

	vecFileName.clear();


	for (int i = 0; i <= 35; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_50F/Monster/Dorothy_Skill2_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("DorothySkill2",
		"DorothySkill2", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 110.f, 119.f, 65 / 110.f, 143 / 119.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 501.f, 191.f, 373 / 501.f, 211 / 191.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 483.f, 228.f, 352 / 483.f, 208 / 228.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 469.f, 225.f, 345 / 469.f, 205 / 225.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 460.f, 227.f, 336 / 460.f, 209 / 227.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 389.f, 221.f, 274 / 389.f, 209 / 221.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 354.f, 242.f, 241 / 354.f, 202 / 242.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 341.f, 229.f, 235 / 341.f, 196 / 229.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 352.f, 219.f, 256 / 352.f, 193 / 219.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 334.f, 212.f, 254 / 334.f, 185 / 212.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 319.f, 205.f, 247 / 319.f, 183 / 205.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 303.f, 196.f, 238 / 303.f, 181 / 196.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 469.f, 225.f, 345 / 469.f, 205 / 225.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 460.f, 227.f, 336 / 460.f, 209 / 227.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 389.f, 221.f, 274 / 389.f, 209 / 221.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 354.f, 242.f, 241 / 354.f, 202 / 242.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 341.f, 229.f, 235 / 341.f, 196 / 229.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 352.f, 219.f, 256 / 352.f, 193 / 219.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 334.f, 212.f, 254 / 334.f, 185 / 212.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 319.f, 205.f, 247 / 319.f, 183 / 205.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 303.f, 196.f, 238 / 303.f, 181 / 196.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 469.f, 225.f, 345 / 469.f, 205 / 225.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 460.f, 227.f, 336 / 460.f, 209 / 227.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 389.f, 221.f, 274 / 389.f, 209 / 221.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 1635.f, 305.f, 1538 / 1635.f, 252 / 305.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 1618.f, 308.f, 1546 / 1618.f, 255 / 308.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 1621.f, 308.f, 1546 / 1621.f, 255 / 308.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 1625.f, 307.f, 1542 / 1625.f, 255 / 307.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 1632.f, 305.f, 1549 / 1632.f, 254 / 305.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 1629.f, 297.f, 1541 / 1629.f, 251 / 297.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 1163.f, 219.f, 1072 / 1163.f, 206 / 219.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 966.f, 194.f, 871 / 966.f, 196 / 194.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 686.f, 140.f, 589 / 686.f, 142 / 140.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 661.f, 140.f, 590 / 661.f, 142 / 140.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 632.f, 140.f, 565 / 632.f, 142 / 140.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothySkill2", 0.f, 0.f, 599.f, 119.f, 559 / 599.f, 141 / 119.f);

	CResourceManager::GetInst()->SetColorKey("DorothySkill2", 255, 0, 255);


	vecFileName.clear();


	for (int i = 0; i <= 18; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_50F/Monster/Dorothy_Die_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("DorothyDie",
		"DorothyDie", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("DorothyDie", 0.f, 0.f, 110.f, 119.f, 65 / 110.f, 143 / 119.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyDie", 0.f, 0.f, 90.f, 135.f, 35 / 90.f, 162 / 135.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyDie", 0.f, 0.f, 116.f, 126.f, 51 / 116.f, 153 / 126.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyDie", 0.f, 0.f, 129.f, 119.f, 58 / 129.f, 146 / 119.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyDie", 0.f, 0.f, 150.f, 116.f, 75 / 150.f, 143 / 116.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyDie", 0.f, 0.f, 153.f, 116.f, 77 / 153.f, 143 / 116.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyDie", 0.f, 0.f, 287.f, 470.f, 54 / 287.f, 473 / 470.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyDie", 0.f, 0.f, 275.f, 469.f, 52 / 275.f, 472 / 469.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyDie", 0.f, 0.f, 305.f, 468.f, 62 / 305.f, 471 / 468.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyDie", 0.f, 0.f, 289.f, 463.f, 60 / 289.f, 466 / 463.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyDie", 0.f, 0.f, 321.f, 462.f, 79 / 321.f, 465 / 462.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyDie", 0.f, 0.f, 323.f, 472.f, 79 / 323.f, 475 / 472.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyDie", 0.f, 0.f, 313.f, 461.f, 73 / 313.f, 464 / 461.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyDie", 0.f, 0.f, 319.f, 460.f, 75 / 319.f, 463 / 460.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyDie", 0.f, 0.f, 284.f, 468.f, 77 / 284.f, 471 / 468.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyDie", 0.f, 0.f, 302.f, 464.f, 87 / 302.f, 467 / 464.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyDie", 0.f, 0.f, 316.f, 460.f, 77 / 316.f, 463 / 460.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyDie", 0.f, 0.f, 316.f, 467.f, 76 / 316.f, 470 / 467.f);
	CResourceManager::GetInst()->AddAnimationFrame("DorothyDie", 0.f, 0.f, 303.f, 450.f, 73 / 303.f, 454 / 450.f);

	CResourceManager::GetInst()->SetColorKey("DorothyDie", 255, 0, 255);


	vecFileName.clear();


	for (int i = 0; i <= 23; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_50F/Object/AreaWarning_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("AreaWarning",
		"AreaWarning", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 1.f, 1.f, 0 / 1.f, 0 / 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 199.f, 107.f, 99 / 199.f, 119 / 107.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 178.f, 107.f, 92 / 178.f, 109 / 107.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 177.f, 102.f, 88 / 177.f, 96 / 102.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 193.f, 103.f, 96 / 193.f, 92 / 103.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 195.f, 108.f, 97 / 195.f, 97 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 199.f, 112.f, 99 / 199.f, 100 / 112.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 199.f, 112.f, 99 / 199.f, 100 / 112.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 199.f, 112.f, 99 / 199.f, 100 / 112.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 199.f, 114.f, 99 / 199.f, 102 / 114.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 199.f, 113.f, 99 / 199.f, 101 / 113.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 199.f, 110.f, 99 / 199.f, 98 / 110.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 199.f, 106.f, 99 / 199.f, 94 / 106.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 199.f, 110.f, 99 / 199.f, 98 / 110.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 199.f, 112.f, 99 / 199.f, 100 / 112.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 199.f, 112.f, 99 / 199.f, 100 / 112.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 199.f, 112.f, 99 / 199.f, 100 / 112.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 199.f, 114.f, 99 / 199.f, 102 / 114.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 367.f, 213.f, 179 / 367.f, 216 / 213.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 345.f, 224.f, 170 / 345.f, 227 / 224.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 321.f, 235.f, 156 / 321.f, 238 / 235.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 317.f, 238.f, 158 / 317.f, 241 / 238.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 311.f, 238.f, 143 / 311.f, 242 / 238.f);
	CResourceManager::GetInst()->AddAnimationFrame("AreaWarning", 0.f, 0.f, 225.f, 239.f, 114 / 225.f, 244 / 239.f);

	CResourceManager::GetInst()->SetColorKey("AreaWarning", 255, 0, 255);


	vecFileName.clear();


	for (int i = 0; i <= 6; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_50F/Object/EnergyBall_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("EnergyBall",
		"EnergyBall", vecFileName, TEXTURE_PATH);

	for (int i = 0; i <= 6; ++i)
	{
		CResourceManager::GetInst()->AddAnimationFrame("EnergyBall", 0.f, 0.f, 134.f, 134.f, 0.5f, 1.f);
	}

	CResourceManager::GetInst()->SetColorKey("EnergyBall", 255, 0, 255);


	vecFileName.clear();


	for (int i = 0; i <= 6; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_50F/Object/Meteor1_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("MeteorRed",
		"MeteorRed", vecFileName, TEXTURE_PATH);

	for (int i = 0; i <= 6; ++i)
	{
		CResourceManager::GetInst()->AddAnimationFrame("MeteorRed", 0.f, 0.f, 81.f, 73.f, 11 / 81.f, 60 / 73.f);
	}

	CResourceManager::GetInst()->SetColorKey("MeteorRed", 255, 0, 255);


	vecFileName.clear();


	for (int i = 0; i <= 6; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_50F/Object/Meteor2_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("MeteorPurple",
		"MeteorPurple", vecFileName, TEXTURE_PATH);

	for (int i = 0; i <= 6; ++i)
	{
		CResourceManager::GetInst()->AddAnimationFrame("MeteorPurple", 0.f, 0.f, 102.f, 87.f, 12 / 102.f, 72 / 87.f);
	}

	CResourceManager::GetInst()->SetColorKey("MeteorPurple", 255, 0, 255);


	vecFileName.clear();


	for (int i = 0; i <= 6; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_50F/Object/Meteor3_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("MeteorPink",
		"MeteorPink", vecFileName, TEXTURE_PATH);

	for (int i = 0; i <= 6; ++i)
	{
		CResourceManager::GetInst()->AddAnimationFrame("MeteorPink", 0.f, 0.f, 115.f, 99.f, 14 / 115.f, 82 / 99.f);
	}

	CResourceManager::GetInst()->SetColorKey("MeteorPink", 255, 0, 255);
}
