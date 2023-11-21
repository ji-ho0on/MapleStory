#include "TheSeed7F.h"
#include "../GameObject/Player.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "../Widget/CharacterHUD.h"
#include "../GameObject/TileMap.h"
#include "../Resource/ResourceManager.h"
#include "../Collision/ColliderBox.h"
#include "../GameObject/GameObject.h"
#include "SceneManager.h"
#include "TheSeed50F.h"
#include "../GameObject/Lupin.h"
#include "../Widget/CharacterStatus.h"
#include "../GameObject/Effect.h"

CTheSeed7F::CTheSeed7F()
{
}

CTheSeed7F::~CTheSeed7F()
{
}

bool CTheSeed7F::Init()
{
	if (!CScene::Init())
		return false;

	CreateAnimationSequence();

	// 맵 Sound 로딩
	GetSceneResource()->LoadSound("BGM", "TheSeed7F_BGM", true, "MapleStory/MoonlightShadow.mp3");
	GetSceneResource()->LoadSound("Map", "Portal", false, "MapleStory/Portal.mp3");
	GetSceneResource()->SoundPlay("TheSeed7F_BGM");
	GetSceneResource()->SetVolume(20);


	// 캐릭터용 Sound 로딩
	GetSceneResource()->LoadSound("Character", "Jump", false, "MapleStory/Jump.mp3");
	GetSceneResource()->LoadSound("Character", "SlashBlust", false, "MapleStory/SlashBlust.mp3");
	GetSceneResource()->LoadSound("Character", "RaisingBlow", false, "MapleStory/RaisingBlow.mp3");

	// 몬스터용 Sound 로딩
	GetSceneResource()->LoadSound("Monster", "LupinAttack", false, "MapleStory/Lupin_Attack.mp3");
	GetSceneResource()->LoadSound("Monster", "LupinBananaDamage", false, "MapleStory/LupinBanana_Damage.mp3");
	GetSceneResource()->SetVolume("Monster", 30);


	// 카메라 설정
	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(1400.f, 2400.f);
	GetCamera()->SetTargetPivot(0.5f, 0.7f);

	// 플레이어 세팅
	CPlayer* Player = CreateObject<CPlayer>("Player");
	SetPlayer(Player);
	Player->SetPos(900.f, 2200.f);
	Player->SetFallStartY(2200.f);
	GetCamera()->SetTarget(Player);

	// 타일맵 세팅
	CTileMap* TheSeed7F = CreateObject<CTileMap>("TheSeed7F");
	TheSeed7F->LoadFileName("TheSeed7F.tmp", MAP_PATH);

	// 몬스터 세팅
	CLupin* Lupin0 = CreateObject<CLupin>("Lupin0");
	Lupin0->SetPos(117.f, 2170.f);
	Lupin0->SetDir(1.f, 0.f);

	CLupin* Lupin1 = CreateObject<CLupin>("Lupin1");
	Lupin1->SetPos(929.f, 1990.f);
	Lupin1->SetDir(-1.f, 0.f);

	CLupin* Lupin2 = CreateObject<CLupin>("Lupin2");
	Lupin2->SetPos(834.f, 1690.f);
	Lupin2->SetDir(1.f, 0.f);

	CLupin* Lupin3 = CreateObject<CLupin>("Lupin3");
	Lupin3->SetPos(750.f, 1510.f);
	Lupin3->SetDir(-1.f, 0.f);

	CLupin* Lupin4 = CreateObject<CLupin>("Lupin4");
	Lupin4->SetPos(1333.f, 1180.f);
	Lupin4->SetDir(-1.f, 0.f);

	CLupin* Lupin5 = CreateObject<CLupin>("Lupin5");
	Lupin5->SetPos(385.f, 1270.f);
	Lupin5->SetDir(1.f, 0.f);

	CLupin* Lupin6 = CreateObject<CLupin>("Lupin6");
	Lupin6->SetPos(389.f, 910.f);
	Lupin6->SetDir(-1.f, 0.f);

	CLupin* Lupin7 = CreateObject<CLupin>("Lupin7");
	Lupin7->SetPos(1244.f, 640.f);
	Lupin7->SetDir(-1.f, 0.f);

	CLupin* Lupin8 = CreateObject<CLupin>("Lupin8");
	Lupin8->SetPos(341.f, 400.f);
	Lupin8->SetDir(1.f, 0.f);

	// 밧줄 상호작용 충돌체 추가
	CColliderBox* Rope = TheSeed7F->AddCollider<CColliderBox>("Rope0");
	Rope->SetExtent(1.f, 150.f);
	Rope->SetOffset(792.f, 1870.f);
	Rope->AddOffset(0.f, 75.f);
	Rope->SetCollisionProfile("Rope");

	Rope = TheSeed7F->AddCollider<CColliderBox>("Rope1");
	Rope->SetExtent(1.f, 210.f);
	Rope->SetOffset(1195.f, 1060.f);
	Rope->AddOffset(0.f, 105.f);
	Rope->SetCollisionProfile("Rope");

	Rope = TheSeed7F->AddCollider<CColliderBox>("Rope2");
	Rope->SetExtent(1.f, 250.f);
	Rope->SetOffset(1063.f, 490.f);
	Rope->AddOffset(0.f, 125.f);
	Rope->SetCollisionProfile("Rope");

	Rope = TheSeed7F->AddCollider<CColliderBox>("Rope3");
	Rope->SetExtent(1.f, 184.f);
	Rope->SetOffset(477.f, 250.f);
	Rope->AddOffset(0.f, 92.f);
	Rope->SetCollisionProfile("Rope");

	// 포탈 상호작용 충돌체 설정
	CColliderBox* Potal = TheSeed7F->AddCollider<CColliderBox>("Potal0");
	Potal->SetExtent(30.f, 1.f);
	Potal->SetOffset(655.f, 250.f);
	Potal->SetCollisionProfile("Potal");
	Potal->SetCollisionBeginFunction<CTheSeed7F>(this, &CTheSeed7F::Clear);

	m_CharacterStatus = CreateWidgetWindow<CCharacterStatus>("CharacterStatus");

	return true;
}

void CTheSeed7F::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);
}

void CTheSeed7F::PostUpdate(float DeltaTime)
{
	CScene::PostUpdate(DeltaTime);

	CPlayer* Player = (CPlayer*)m_Player.Get();

	if (Player->GetPotal())
	{
		GetSceneResource()->SoundPlay("Portal");
		CInput::GetInst()->ClearCallback();
		CSceneManager::GetInst()->CreateScene<CTheSeed50F>();
		return;
	}

	// 플레이어가 로프에 매달릴때 플레이어의 x 값을 로프의 x값으로 맞춰준다.
	if (Player->GetRope())
	{
		for (int i = 0; i <= 3; ++i)
		{
			TCHAR	RopeNumber[128] = {};
			wsprintf(RopeNumber, TEXT("Rope%d"), i);

			int Len = (int)wcslen((wchar_t*)RopeNumber);
			Len = 2 * Len + 1;
			char* cRopeNumber = new char[Len];

			wcstombs_s(nullptr, cRopeNumber, (size_t)(Len), RopeNumber, (size_t)(Len - 1));

			std::string RopeName = cRopeNumber;

			SAFE_DELETE_ARRAY(cRopeNumber);

			CCollider* Rope = m_TileMap->FindCollider(RopeName);

			if (Player->FindCollider("Player")->CheckCollisionList(Rope))
			{
				Player->SetPosX(Rope->GetOffset().x);
				break;
			}
		}
	}
}

void CTheSeed7F::CreateAnimationSequence()
{
	//PlayerAnimationSequence();
	//
	//PlayerEffectAnimationSequence();

	MonsterAnimationSequence();
}

void CTheSeed7F::PlayerAnimationSequence()
{
	std::vector<std::wstring>	vecFileName1;

	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Left/Player_Alert_%d.bmp"), i);
		vecFileName1.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerLeftAlert",
		"PlayerLeftAlert", vecFileName1, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftAlert", 0.f, 0.f, 106.f, 66.f, 0.78f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftAlert", 0.f, 0.f, 106.f, 67.f, 0.78f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftAlert", 0.f, 0.f, 106.f, 68.f, 0.78f, 1.f);

	CResourceManager::GetInst()->SetColorKey("PlayerLeftAlert", 255, 0, 255);

	std::vector<std::wstring>	vecFileName2;

	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Right/Player_Alert_Right_%d.bmp"), i);
		vecFileName2.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerRightAlert",
		"PlayerRightAlert", vecFileName2, TEXTURE_PATH);

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

	std::vector<std::wstring>	vecFileName3;

	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Left/Player_Stand_%d.bmp"), i);
		vecFileName3.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerLeftStand",
		"PlayerLeftStand", vecFileName3, TEXTURE_PATH);

	for (int i = 0; i <= 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerLeftStand", 0.f, 0.f, 72.f, 81.f, 0.54f, 0.83f);
	}

	GetSceneResource()->SetColorKey("PlayerLeftStand", 255, 0, 255);

	std::vector<std::wstring>	vecFileName4;

	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Right/Player_Stand_Right_%d.bmp"), i);
		vecFileName4.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerRightStand",
		"PlayerRightStand", vecFileName4, TEXTURE_PATH);

	for (int i = 0; i <= 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerRightStand", 0.f, 0.f, 72.f, 81.f, 0.46f, 0.83f);
	}

	GetSceneResource()->SetColorKey("PlayerRightStand", 255, 0, 255);

	std::vector<std::wstring>	vecFileName5;

	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Left/Player_SwingT1_%d.bmp"), i);
		vecFileName5.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerLeftSwing",
		"PlayerLeftSwing", vecFileName5, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftSwing", 0.f, 0.f, 114.f, 70.f, 0.17f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftSwing", 0.f, 0.f, 46.f, 117.f, 0.65f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftSwing", 0.f, 0.f, 125.f, 80.f, 0.85f, 0.76f);

	GetSceneResource()->SetColorKey("PlayerLeftSwing", 255, 0, 255);

	std::vector<std::wstring>	vecFileName6;

	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Right/Player_SwingT1_Right_%d.bmp"), i);
		vecFileName6.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerRightSwing",
		"PlayerRightSwing", vecFileName6, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightSwing", 0.f, 0.f, 114.f, 70.f, 0.83f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightSwing", 0.f, 0.f, 46.f, 117.f, 0.35f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightSwing", 0.f, 0.f, 125.f, 80.f, 0.15f, 0.76f);

	GetSceneResource()->SetColorKey("PlayerRightSwing", 255, 0, 255);

	std::vector<std::wstring>	vecFileName7;

	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Left/Player_SwingT3_%d.bmp"), i);
		vecFileName7.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerLeftSwingT3",
		"PlayerLeftSwingT3", vecFileName7, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftSwingT3", 0.f, 0.f, 123.f, 68.f, 0.2f, 0.98f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftSwingT3", 0.f, 0.f, 123.f, 72.f, 0.28f, 0.83f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftSwingT3", 0.f, 0.f, 57.f, 116.f, 0.66f, 1.f);

	GetSceneResource()->SetColorKey("PlayerLeftSwingT3", 255, 0, 255);

	std::vector<std::wstring>	vecFileName8;

	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Right/Player_SwingT3_Right_%d.bmp"), i);
		vecFileName8.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerRightSwingT3",
		"PlayerRightSwingT3", vecFileName8, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightSwingT3", 0.f, 0.f, 123.f, 68.f, 0.8f, 0.98f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightSwingT3", 0.f, 0.f, 123.f, 72.f, 0.72f, 0.83f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightSwingT3", 0.f, 0.f, 57.f, 116.f, 0.34f, 1.f);

	GetSceneResource()->SetColorKey("PlayerRightSwingT3", 255, 0, 255);

	std::vector<std::wstring>	vecFileName9;

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Left/Player_SwingTF_%d.bmp"), i);
		vecFileName9.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerLeftSwingTF",
		"PlayerLeftSwingTF", vecFileName9, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftSwingTF", 0.f, 0.f, 66.f, 122.f, 0.68f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftSwingTF", 0.f, 0.f, 46.f, 120.f, 0.45f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftSwingTF", 0.f, 0.f, 61.f, 118.f, 0.5f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftSwingTF", 0.f, 0.f, 121.f, 77.f, 0.84f, 0.78f);

	GetSceneResource()->SetColorKey("PlayerLeftSwingTF", 255, 0, 255);

	std::vector<std::wstring>	vecFileName10;

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Right/Player_SwingTF_Right_%d.bmp"), i);
		vecFileName10.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerRightSwingTF",
		"PlayerRightSwingTF", vecFileName10, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightSwingTF", 0.f, 0.f, 66.f, 122.f, 0.32f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightSwingTF", 0.f, 0.f, 46.f, 120.f, 0.55f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightSwingTF", 0.f, 0.f, 61.f, 118.f, 0.5f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightSwingTF", 0.f, 0.f, 121.f, 77.f, 0.16f, 0.78f);

	GetSceneResource()->SetColorKey("PlayerRightSwingTF", 255, 0, 255);

	std::vector<std::wstring>	vecFileName11;

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Left/Player_Walk_%d.bmp"), i);
		vecFileName11.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerLeftWalk",
		"PlayerLeftWalk", vecFileName11, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftWalk", 0.f, 0.f, 100.f, 69.f, 0.77f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftWalk", 0.f, 0.f, 102.f, 68.f, 0.75f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftWalk", 0.f, 0.f, 100.f, 69.f, 0.75f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftWalk", 0.f, 0.f, 96.f, 74.f, 0.72f, 0.89f);

	GetSceneResource()->SetColorKey("PlayerLeftWalk", 255, 0, 255);

	std::vector<std::wstring>	vecFileName12;

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Right/Player_Walk_Right_%d.bmp"), i);
		vecFileName12.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerRightWalk",
		"PlayerRightWalk", vecFileName12, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightWalk", 0.f, 0.f, 100.f, 69.f, 0.23f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightWalk", 0.f, 0.f, 102.f, 68.f, 0.25f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightWalk", 0.f, 0.f, 100.f, 69.f, 0.25f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightWalk", 0.f, 0.f, 96.f, 74.f, 0.28f, 0.89f);

	GetSceneResource()->SetColorKey("PlayerRightWalk", 255, 0, 255);

	std::vector<std::wstring>	vecFileName13;

	for (int i = 0; i <= 1; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Left/Player_ProneStab_%d.bmp"), i);
		vecFileName13.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerLeftProneStab",
		"PlayerLeftProneStab", vecFileName13, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftProneStab", 0.f, 0.f, 127.f, 52.f, 0.85f, 0.77f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftProneStab", 0.f, 0.f, 142.f, 52.f, 0.87f, 0.77f);

	GetSceneResource()->SetColorKey("PlayerLeftProneStab", 255, 0, 255);

	std::vector<std::wstring>	vecFileName14;

	for (int i = 0; i <= 1; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Right/Player_ProneStab_Right_%d.bmp"), i);
		vecFileName14.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerRightProneStab",
		"PlayerRightProneStab", vecFileName14, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightProneStab", 0.f, 0.f, 127.f, 52.f, 0.15f, 0.77f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRightProneStab", 0.f, 0.f, 142.f, 52.f, 0.13f, 0.77f);

	GetSceneResource()->SetColorKey("PlayerRightProneStab", 255, 0, 255);


	CResourceManager::GetInst()->CreateAnimationSequence("PlayerRope",
		"PlayerRope", TEXT("MapleStory/Player/Left/Player_Rope_0.bmp"), TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerRope", 0.f, 0.f, 72.f, 72.f, 0.5f, 1.f);

	GetSceneResource()->SetColorKey("PlayerRope", 255, 0, 255);

	std::vector<std::wstring>	vecFileName15;

	for (int i = 0; i <= 1; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/Player/Left/Player_Rope_%d.bmp"), i);
		vecFileName15.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("PlayerRopeMove",
		"PlayerRopeMove", vecFileName15, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("PlayerRopeMove", 0.f, 0.f, 72.f, 72.f, 0.5f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("PlayerRopeMove", 0.f, 0.f, 72.f, 72.f, 0.5f, 1.f);

	GetSceneResource()->SetColorKey("PlayerRopeMove", 255, 0, 255);


	CResourceManager::GetInst()->CreateAnimationSequence("PlayerLeftAttacked",
		"PlayerLeftAttacked", TEXT("MapleStory/Player/Left/Player_Attacked_0.bmp"), TEXTURE_PATH);

	for (int i = 0; i < 6; ++i)
	{
		CResourceManager::GetInst()->AddAnimationFrame("PlayerLeftAttacked", i * 106.f, 0.f, 106.f, 68.f, 0.78f, 1.f);
	}

	GetSceneResource()->SetColorKey("PlayerLeftAttacked", 255, 0, 255);


	CResourceManager::GetInst()->CreateAnimationSequence("PlayerRightAttacked",
		"PlayerRightAttacked", TEXT("MapleStory/Player/Right/Player_Attacked_0_Right.bmp"), TEXTURE_PATH);

	for (int i = 0; i < 6; ++i)
	{
		CResourceManager::GetInst()->AddAnimationFrame("PlayerRightAttacked", i * 106.f, 0.f, 106.f, 68.f, 0.22f, 1.f);
	}

	GetSceneResource()->SetColorKey("PlayerRightAttacked", 255, 0, 255);
}

void CTheSeed7F::PlayerEffectAnimationSequence()
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

void CTheSeed7F::MonsterAnimationSequence()
{
	std::vector<std::wstring>	vecMonsterFileName1;

	for (int i = 0; i <= 10; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_7F/Monster/Left/Lupin_Attack_%d.bmp"), i);
		vecMonsterFileName1.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("LupinLeftAttack",
		"LupinLeftAttack", vecMonsterFileName1, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("LupinLeftAttack", 0.f, 0.f, 50.f, 55.f, 0.44f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinLeftAttack", 0.f, 0.f, 50.f, 57.f, 0.44f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinLeftAttack", 0.f, 0.f, 49.f, 54.f, 0.43f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinLeftAttack", 0.f, 0.f, 56.f, 54.f, 0.375f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinLeftAttack", 0.f, 0.f, 54.f, 54.f, 0.389f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinLeftAttack", 0.f, 0.f, 49.f, 54.f, 0.43f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinLeftAttack", 0.f, 0.f, 49.f, 54.f, 0.43f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinLeftAttack", 0.f, 0.f, 49.f, 54.f, 0.43f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinLeftAttack", 0.f, 0.f, 49.f, 54.f, 0.43f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinLeftAttack", 0.f, 0.f, 49.f, 54.f, 0.43f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinLeftAttack", 0.f, 0.f, 49.f, 54.f, 0.43f, 1.f);

	CResourceManager::GetInst()->SetColorKey("LupinLeftAttack", 255, 0, 255);

	std::vector<std::wstring>	vecMonsterFileName2;

	for (int i = 0; i <= 10; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_7F/Monster/Right/Lupin_Attack_%d_Right.bmp"), i);
		vecMonsterFileName2.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("LupinRightAttack",
		"LupinRightAttack", vecMonsterFileName2, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("LupinRightAttack", 0.f, 0.f, 50.f, 55.f, 0.56f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinRightAttack", 0.f, 0.f, 50.f, 57.f, 0.56f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinRightAttack", 0.f, 0.f, 49.f, 54.f, 0.57f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinRightAttack", 0.f, 0.f, 56.f, 54.f, 0.625f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinRightAttack", 0.f, 0.f, 54.f, 54.f, 0.611f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinRightAttack", 0.f, 0.f, 49.f, 54.f, 0.57f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinRightAttack", 0.f, 0.f, 49.f, 54.f, 0.57f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinRightAttack", 0.f, 0.f, 49.f, 54.f, 0.57f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinRightAttack", 0.f, 0.f, 49.f, 54.f, 0.57f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinRightAttack", 0.f, 0.f, 49.f, 54.f, 0.57f, 1.f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinRightAttack", 0.f, 0.f, 49.f, 54.f, 0.57f, 1.f);

	CResourceManager::GetInst()->SetColorKey("LupinRightAttack", 255, 0, 255);


	CResourceManager::GetInst()->CreateAnimationSequence("LupinLeftStand",
		"LupinLeftStand", TEXT("MapleStory/TheSeed_7F/Monster/Left/Lupin_Stand_0.bmp"), TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("LupinLeftStand", 0.f, 0.f, 49.f, 54.f, 0.43f, 1.f);

	CResourceManager::GetInst()->SetColorKey("LupinLeftStand", 255, 0, 255);


	CResourceManager::GetInst()->CreateAnimationSequence("LupinRightStand",
		"LupinRightStand", TEXT("MapleStory/TheSeed_7F/Monster/Right/Lupin_Stand_0_Right.bmp"), TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("LupinRightStand", 0.f, 0.f, 49.f, 54.f, 0.57f, 1.f);

	CResourceManager::GetInst()->SetColorKey("LupinRightStand", 255, 0, 255);


	std::vector<std::wstring>	vecMonsterFileName3;

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_7F/Object/Left/Lupin_Banana_%d.bmp"), i);
		vecMonsterFileName3.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("LupinLeftBanana",
		"LupinLeftBanana", vecMonsterFileName3, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("LupinLeftBanana", 0.f, 0.f, 21.f, 24.f, 0.5f, 0.5f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinLeftBanana", 0.f, 0.f, 30.f, 28.f, 0.5f, 0.5f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinLeftBanana", 0.f, 0.f, 34.f, 33.f, 0.5f, 0.5f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinLeftBanana", 0.f, 0.f, 29.f, 35.f, 0.5f, 0.5f);

	CResourceManager::GetInst()->SetColorKey("LupinLeftBanana", 255, 0, 255);

	std::vector<std::wstring>	vecMonsterFileName4;

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_7F/Object/Right/Lupin_Banana_%d_Right.bmp"), i);
		vecMonsterFileName4.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("LupinRightBanana",
		"LupinRightBanana", vecMonsterFileName4, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("LupinRightBanana", 0.f, 0.f, 21.f, 24.f, 0.5f, 0.5f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinRightBanana", 0.f, 0.f, 30.f, 28.f, 0.5f, 0.5f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinRightBanana", 0.f, 0.f, 34.f, 33.f, 0.5f, 0.5f);
	CResourceManager::GetInst()->AddAnimationFrame("LupinRightBanana", 0.f, 0.f, 29.f, 35.f, 0.5f, 0.5f);

	CResourceManager::GetInst()->SetColorKey("LupinRightBanana", 255, 0, 255);
}

void CTheSeed7F::Clear(CCollider* Src, CCollider* Dest)
{
	if (Dest->GetOwner()->GetName() == "Player")
	{
		CEffect* ClearEffect = CreateObject<CEffect>("7FClearEffect");
		ClearEffect->AddAnimation("Clear", false, 1.5f);
		ClearEffect->SetPos(GetCamera()->GetPos() + Vector2(640.f, 200.f));
	}
}
