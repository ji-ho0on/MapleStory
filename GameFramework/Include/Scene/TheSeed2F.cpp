#include "TheSeed2F.h"
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
#include "TheSeed7F.h"
#include "TheSeed50F.h"
#include "../GameObject/Effect.h"
#include "../GameObject/Hector.h"
#include "../GameObject/WhiteFang.h"
#include "../GameObject/RedCard.h"
#include "../GameObject/BlueCard.h"
#include "../GameObject/GreenCard.h"
#include "../GameObject/YellowCard.h"
#include "../GameObject/VioletCard.h"
#include "../GameObject/SealBreakCard.h"
#include "../Widget/CharacterStatus.h"
#include "../Widget/CharacterMenu.h"

CTheSeed2F::CTheSeed2F()
{
}

CTheSeed2F::~CTheSeed2F()
{
}

bool CTheSeed2F::Init()
{
	if (!CScene::Init())
		return false;

	CreateAnimationSequence();

	// 맵 Sound 로딩
	GetSceneResource()->LoadSound("BGM", "TheSeed2F_BGM", true, "MapleStory/WarmRegard.mp3");
	GetSceneResource()->LoadSound("Map", "Portal", false, "MapleStory/Portal.mp3");
	GetSceneResource()->SoundPlay("TheSeed2F_BGM");
	GetSceneResource()->SetVolume(20);

	// 캐릭터용 Sound 로딩
	GetSceneResource()->LoadSound("Character", "Jump", false, "MapleStory/Jump.mp3");
	GetSceneResource()->LoadSound("Character", "SlashBlust", false, "MapleStory/SlashBlust.mp3");
	GetSceneResource()->LoadSound("Character", "RaisingBlow", false, "MapleStory/RaisingBlow.mp3");
	GetSceneResource()->LoadSound("Character", "RaisingBlow", false, "MapleStory/RaisingBlow.mp3");
	GetSceneResource()->LoadSound("Character", "LevelUp", false, "MapleStory/LevelUp.mp3");

	// 몬스터용 Sound 로딩
	GetSceneResource()->LoadSound("Monster", "HectorAttack", false, "MapleStory/Hector_Attack.mp3");
	GetSceneResource()->LoadSound("Monster", "HectorDamage", false, "MapleStory/Hector_Damage.mp3");
	GetSceneResource()->LoadSound("Monster", "HectorDie", false, "MapleStory/Hector_Die.mp3");
	GetSceneResource()->SetVolume("Monster", 30);


	// 카메라 설정
	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(3120.f, 1700.f);
	GetCamera()->SetTargetPivot(0.5f, 0.7f);

	// 타일맵 세팅
	CTileMap* TheSeed2F = CreateObject<CTileMap>("TheSeed2F");
	TheSeed2F->LoadFileName("TheSeed2F.tmp", MAP_PATH);
	SetTileMap(TheSeed2F);

	// 플레이어 세팅
	CPlayer* Player = CreateObject<CPlayer>("Player");
	SetPlayer(Player);
	Player->SetPos(1740.f, 1200.f);
	Player->SetFallStartY(1200.f);
	GetCamera()->SetTarget(Player);


	srand((unsigned int)time(0));

	int Random = rand();

	int RedCardNumber = rand() % (int)ECard_Number::Max;
	int BlueCardNumber = rand() % (int)ECard_Number::Max;
	int GreenCardNumber = rand() % (int)ECard_Number::Max;
	int YellowCardNumber = rand() % (int)ECard_Number::Max;

	// 카드 상호작용 세팅
	m_RedCard = CreateObject<CRedCard>("RedCard");
	m_RedCard->SetPos(1260.f, 960.f);
	m_RedCard->SetCardNumber((ECard_Number)RedCardNumber);


	m_BlueCard = CreateObject<CBlueCard>("BlueCard");
	m_BlueCard->SetPos(2960.f, 1510.f);
	m_BlueCard->SetCardNumber((ECard_Number)BlueCardNumber);


	m_GreenCard = CreateObject<CGreenCard>("GreenCard");
	m_GreenCard->SetPos(90.f, 1630.f);
	m_GreenCard->SetCardNumber((ECard_Number)GreenCardNumber);


	m_YellowCard = CreateObject<CYellowCard>("YellowCard");
	m_YellowCard->SetPos(2880.f, 960.f);
	m_YellowCard->SetCardNumber((ECard_Number)YellowCardNumber);

	// 밧줄 상호작용 충돌체 추가
	CColliderBox* Rope = TheSeed2F->AddCollider<CColliderBox>("Rope0");
	Rope->SetExtent(1.f, 115.f);
	Rope->SetOffset(299.5f, 1497.5f);
	Rope->SetCollisionProfile("Rope");

	Rope = TheSeed2F->AddCollider<CColliderBox>("Rope1");
	Rope->SetExtent(1.f, 110.f);
	Rope->SetOffset(976.f, 1495.f);
	Rope->SetCollisionProfile("Rope");

	Rope = TheSeed2F->AddCollider<CColliderBox>("Rope2");
	Rope->SetExtent(1.f, 260.f);
	Rope->SetOffset(542.f, 1140.f);
	Rope->AddOffset(2.5f, 130.f);
	Rope->SetCollisionProfile("Rope");

	Rope = TheSeed2F->AddCollider<CColliderBox>("Rope3");
	Rope->SetExtent(1.f, 120.f);
	Rope->SetOffset(935.f, 960.f);
	Rope->AddOffset(2.5f, 60.f);
	Rope->SetCollisionProfile("Rope");

	Rope = TheSeed2F->AddCollider<CColliderBox>("Rope4");
	Rope->SetExtent(1.f, 220.f);
	Rope->SetOffset(1496.f, 960.f);
	Rope->AddOffset(2.5f, 110.f);
	Rope->SetCollisionProfile("Rope");

	Rope = TheSeed2F->AddCollider<CColliderBox>("Rope5");
	Rope->SetExtent(1.f, 120.f);
	Rope->SetOffset(1542.f, 1070.f);
	Rope->AddOffset(2.5f, 60.f);
	Rope->SetCollisionProfile("Rope");

	Rope = TheSeed2F->AddCollider<CColliderBox>("Rope6");
	Rope->SetExtent(1.f, 160.f);
	Rope->SetOffset(1976.f, 1260.f);
	Rope->AddOffset(2.5f, 80.f);
	Rope->SetCollisionProfile("Rope");

	Rope = TheSeed2F->AddCollider<CColliderBox>("Rope7");
	Rope->SetExtent(1.f, 230.f);
	Rope->SetOffset(2645.f, 960.f);
	Rope->AddOffset(2.5f, 115.f);
	Rope->SetCollisionProfile("Rope");

	Rope = TheSeed2F->AddCollider<CColliderBox>("Rope8");
	Rope->SetExtent(1.f, 320.f);
	Rope->SetOffset(2783.f, 960.f);
	Rope->AddOffset(2.5f, 160.f);
	Rope->SetCollisionProfile("Rope");

	Rope = TheSeed2F->AddCollider<CColliderBox>("Rope9");
	Rope->SetExtent(1.f, 170.f);
	Rope->SetOffset(2678.f, 1080.f);
	Rope->AddOffset(2.5f, 85.f);
	Rope->SetCollisionProfile("Rope");

	Rope = TheSeed2F->AddCollider<CColliderBox>("Rope10");
	Rope->SetExtent(1.f, 170.f);
	Rope->SetOffset(2722.f, 1150.f);
	Rope->AddOffset(2.5f, 85.f);
	Rope->SetCollisionProfile("Rope");

	Rope = TheSeed2F->AddCollider<CColliderBox>("Rope11");
	Rope->SetExtent(1.f, 220.f);
	Rope->SetOffset(2756.f, 1200.f);
	Rope->AddOffset(2.5f, 110.f);
	Rope->SetCollisionProfile("Rope");


	// 포탈 상호작용 충돌체 설정
	CColliderBox* Potal = TheSeed2F->AddCollider<CColliderBox>("Potal");
	Potal->SetExtent(30.f, 1.f);
	Potal->SetOffset(1750.f, 1450.f);
	Potal->SetCollisionProfile("Potal");
	Potal->SetEnable(false); // 모든 카드의 hit가 true로 바뀐다면 포탈이 생성됨

	m_vecSequenceKey[(int)ECard_Color::Red].push_back("RedCard1");
	m_vecSequenceKey[(int)ECard_Color::Red].push_back("RedCard2");
	m_vecSequenceKey[(int)ECard_Color::Red].push_back("RedCard3");
	m_vecSequenceKey[(int)ECard_Color::Red].push_back("RedCard4");
	m_vecSequenceKey[(int)ECard_Color::Red].push_back("RedCard5");
	m_vecSequenceKey[(int)ECard_Color::Red].push_back("RedCard6");
	m_vecSequenceKey[(int)ECard_Color::Red].push_back("RedCard7");

	m_vecSequenceKey[(int)ECard_Color::Blue].push_back("BlueCard1");
	m_vecSequenceKey[(int)ECard_Color::Blue].push_back("BlueCard2");
	m_vecSequenceKey[(int)ECard_Color::Blue].push_back("BlueCard3");
	m_vecSequenceKey[(int)ECard_Color::Blue].push_back("BlueCard4");
	m_vecSequenceKey[(int)ECard_Color::Blue].push_back("BlueCard5");
	m_vecSequenceKey[(int)ECard_Color::Blue].push_back("BlueCard6");
	m_vecSequenceKey[(int)ECard_Color::Blue].push_back("BlueCard7");

	m_vecSequenceKey[(int)ECard_Color::Green].push_back("GreenCard1");
	m_vecSequenceKey[(int)ECard_Color::Green].push_back("GreenCard2");
	m_vecSequenceKey[(int)ECard_Color::Green].push_back("GreenCard3");
	m_vecSequenceKey[(int)ECard_Color::Green].push_back("GreenCard4");
	m_vecSequenceKey[(int)ECard_Color::Green].push_back("GreenCard5");
	m_vecSequenceKey[(int)ECard_Color::Green].push_back("GreenCard6");
	m_vecSequenceKey[(int)ECard_Color::Green].push_back("GreenCard7");

	m_vecSequenceKey[(int)ECard_Color::Yellow].push_back("YellowCard1");
	m_vecSequenceKey[(int)ECard_Color::Yellow].push_back("YellowCard2");
	m_vecSequenceKey[(int)ECard_Color::Yellow].push_back("YellowCard3");
	m_vecSequenceKey[(int)ECard_Color::Yellow].push_back("YellowCard4");
	m_vecSequenceKey[(int)ECard_Color::Yellow].push_back("YellowCard5");
	m_vecSequenceKey[(int)ECard_Color::Yellow].push_back("YellowCard6");
	m_vecSequenceKey[(int)ECard_Color::Yellow].push_back("YellowCard7");

	m_vecSequenceKey[(int)ECard_Color::Violet].push_back("VioletCard");
	m_vecSequenceKey[(int)ECard_Color::Violet].push_back("VioletCard");
	m_vecSequenceKey[(int)ECard_Color::Violet].push_back("VioletCard");
	m_vecSequenceKey[(int)ECard_Color::Violet].push_back("VioletCard");
	m_vecSequenceKey[(int)ECard_Color::Violet].push_back("VioletCard");
	m_vecSequenceKey[(int)ECard_Color::Violet].push_back("VioletCard");
	m_vecSequenceKey[(int)ECard_Color::Violet].push_back("VioletCard");

	for (int i = 0; i < 21; ++i)
	{
		m_SpawnInfo[i].Spawn = false;
		m_SpawnInfo[i].SpawnNumber = i;
	}

	for (int i = 0; i < 11; ++i)
	{
		m_SpawnInfo[i].Type = EMonster_Type::WhiteFang;
	}

	for (int i = 11; i < 21; ++i)
	{
		m_SpawnInfo[i].Type = EMonster_Type::Hector;
	}

	m_SpawnInfo[0].Pos = Vector2(250.f, 1630.f);
	m_SpawnInfo[1].Pos = Vector2(460.f, 1630.f);
	m_SpawnInfo[2].Pos = Vector2(700.f, 1570.f);
	m_SpawnInfo[3].Pos = Vector2(900.f, 1570.f);
	m_SpawnInfo[4].Pos = Vector2(1200.f, 1510.f);
	m_SpawnInfo[5].Pos = Vector2(1470.f, 1510.f);
	m_SpawnInfo[6].Pos = Vector2(1680.f, 1450.f);
	m_SpawnInfo[7].Pos = Vector2(1980.f, 1450.f);
	m_SpawnInfo[8].Pos = Vector2(2190.f, 1510.f);
	m_SpawnInfo[9].Pos = Vector2(2440.f, 1510.f);
	m_SpawnInfo[10].Pos = Vector2(2700.f, 1510.f);

	m_SpawnInfo[11].Pos = Vector2(410.f, 1440.f);
	m_SpawnInfo[12].Pos = Vector2(610.f, 1440.f);
	m_SpawnInfo[13].Pos = Vector2(780.f, 1440.f);
	m_SpawnInfo[14].Pos = Vector2(600.f, 1140.f);
	m_SpawnInfo[15].Pos = Vector2(810.f, 1140.f);
	m_SpawnInfo[16].Pos = Vector2(1030.f, 1140.f);
	m_SpawnInfo[17].Pos = Vector2(1460.f, 1260.f);
	m_SpawnInfo[18].Pos = Vector2(1700.f, 1260.f);
	m_SpawnInfo[19].Pos = Vector2(1900.f, 1260.f);
	m_SpawnInfo[20].Pos = Vector2(2900.f, 1510.f);

	// 몬스터 세팅
	for (int i = 0; i < 21; ++i)
	{
		if (m_SpawnInfo[i].Type == EMonster_Type::Hector)
		{
			CHector* Hector = CreateObject<CHector>("Hector");
			Hector->SetPos(m_SpawnInfo[i].Pos);
			Hector->SetFallStartY(m_SpawnInfo[i].Pos.y);
			Hector->SetSpawnNumber(i);

			m_SpawnInfo[i].Spawn = true;
		}

		else if (m_SpawnInfo[i].Type == EMonster_Type::WhiteFang)
		{
			CWhiteFang* WhiteFang = CreateObject<CWhiteFang>("WhiteFang");
			WhiteFang->SetPos(m_SpawnInfo[i].Pos);
			WhiteFang->SetFallStartY(m_SpawnInfo[i].Pos.y);
			WhiteFang->SetSpawnNumber(i);

			m_SpawnInfo[i].Spawn = true;
		}
	}


	m_RedCardOn = false;
	m_BlueCardOn = false;
	m_GreenCardOn = false;
	m_YellowCardOn = false;

	m_SpawnTime = 0.f;

	m_CharacterStatus = CreateWidgetWindow<CCharacterStatus>("CharacterStatus");

	//m_CharacterMenu = CreateWidgetWindow<CCharacterMenu>("CharacterMenu");
	//m_CharacterMenu->SetPos(745.f, 500.f);
	//m_CharacterMenu->SetEnable(false);
	

	return true;
}

void CTheSeed2F::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);

	CPlayer* Player = (CPlayer*)m_Player.Get();

	if (m_SelectedCard)
	{
		m_SelectedCard->SetPos(Player->GetPos());
	}


	if (m_RedCardOn && m_BlueCardOn && m_GreenCardOn && m_YellowCardOn)
	{
		CCollider* Potal = GetTileMap()->FindCollider("Potal");

		if (!Potal->GetEnable())
		{
			Potal->SetEnable(true);

			CEffect* ClearEffect = CreateObject<CEffect>("2FClearEffect");
			ClearEffect->AddAnimation("Clear", false, 1.5f);
			ClearEffect->SetPos(GetCamera()->GetPos() + Vector2(640.f, 200.f));
		}
	}


	// 몬스터 소환
	m_SpawnTime += DeltaTime;


	if (m_SpawnTime >= 8.f)
	{
		m_SpawnTime -= 8.f;

		for (int i = 0; i < 21; ++i)
		{
			if (!m_SpawnInfo[i].Spawn)
			{
				if (m_SpawnInfo[i].Type == EMonster_Type::Hector)
				{
					CHector* Hector = CreateObject<CHector>("Hector");
					Hector->SetPos(m_SpawnInfo[i].Pos);
					Hector->SetFallStartY(m_SpawnInfo[i].Pos.y);
					Hector->SetSpawnNumber(i);

					m_SpawnInfo[i].Spawn = true;
				}

				else if (m_SpawnInfo[i].Type == EMonster_Type::WhiteFang)
				{
					CWhiteFang* WhiteFang = CreateObject<CWhiteFang>("WhiteFang");
					WhiteFang->SetPos(m_SpawnInfo[i].Pos);
					WhiteFang->SetFallStartY(m_SpawnInfo[i].Pos.y);
					WhiteFang->SetSpawnNumber(i);

					m_SpawnInfo[i].Spawn = true;
				}
			}
		}
	}
}

void CTheSeed2F::PostUpdate(float DeltaTime)
{
	CScene::PostUpdate(DeltaTime);

	CPlayer* Player = (CPlayer*)m_Player.Get();

	if (Player->GetPotal())
	{
		GetSceneResource()->SoundPlay("Portal");
		CInput::GetInst()->ClearCallback();
		CSceneManager::GetInst()->CreateScene<CTheSeed7F>();
		return;
	}

	// 플레이어가 로프에 매달릴때 플레이어의 x 값을 로프의 x값으로 맞춰준다.
	if (Player->GetRope())
	{
		for (int i = 0; i <= 11; ++i)
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

void CTheSeed2F::SelectCard()
{
	CPlayer* Player = (CPlayer*)m_Player.Get();

	int CardColor = rand() % (int)ECard_Color::Max;

	int CardNumber = rand() % (int)ECard_Number::Max;

	if (m_SelectedCard)
	{
		m_SelectedCard->SetActive(false);
		m_SelectedCard = nullptr;
	}

	CCard* SelectedCard = nullptr;

	switch ((ECard_Color)CardColor)
	{
	case ECard_Color::Red:
		SelectedCard = (CCard*)CreateObject<CRedCard>("SelectedCard");
		break;
	case ECard_Color::Blue:
		SelectedCard = (CCard*)CreateObject<CBlueCard>("SelectedCard");
		break;
	case ECard_Color::Green:
		SelectedCard = (CCard*)CreateObject<CGreenCard>("SelectedCard");
		break;
	case ECard_Color::Yellow:
		SelectedCard = (CCard*)CreateObject<CYellowCard>("SelectedCard");
		break;
	case ECard_Color::Violet:
		SelectedCard = (CCard*)CreateObject<CVioletCard>("SelectedCard");
		break;
	}

	SelectedCard->SetCardColor((ECard_Color)CardColor);
	SelectedCard->SetCardNumber((ECard_Number)CardNumber);
	SelectedCard->SetPos(Player->GetPos());

	m_SelectedCard = SelectedCard;

	m_SelectedCard->SetOwner(Player);
}

void CTheSeed2F::ChangeCard(CCard* ChangeCard)
{
	if (!m_SelectedCard)
	{
		return;
	}

	if (m_SelectedCard->GetCardColor() == ECard_Color::Violet)
	{
		if (ChangeCard->GetCardColor() == ECard_Color::Red)
		{
			CRedCard* RedCard = (CRedCard*)ChangeCard;
			RedCard->SetHitNumber(ECard_Number::Max);
			m_RedCardOn = true;
		}

		else if (ChangeCard->GetCardColor() == ECard_Color::Blue)
		{
			CBlueCard* BlueCard = (CBlueCard*)ChangeCard;
			BlueCard->SetHitNumber(ECard_Number::Max);
			m_BlueCardOn = true;
		}

		else if (ChangeCard->GetCardColor() == ECard_Color::Green)
		{
			CGreenCard* GreenCard = (CGreenCard*)ChangeCard;
			GreenCard->SetHitNumber(ECard_Number::Max);
			m_GreenCardOn = true;
		}

		else if (ChangeCard->GetCardColor() == ECard_Color::Yellow)
		{
			CYellowCard* YellowCard = (CYellowCard*)ChangeCard;
			YellowCard->SetHitNumber(ECard_Number::Max);
			m_YellowCardOn = true;
		}
	
		else
		{
			CVioletCard* VioletCard = (CVioletCard*)ChangeCard;
			VioletCard->SetHitColor(ECard_Color::Violet);
		}

		ChangeCard->SetCardColor(ECard_Color::Violet);
		

		m_SelectedCard->SetActive(false);
		m_SelectedCard = nullptr;

		return;
	}


	if (m_SelectedCard->GetCardColor() == ChangeCard->GetCardColor())
	{
		if (m_SelectedCard->GetCardNumber() > ChangeCard->GetCardNumber())
		{
			if (ChangeCard->GetCardColor() == ECard_Color::Red)
			{
				CRedCard* RedCard = (CRedCard*)ChangeCard;
				RedCard->SetHitNumber(m_SelectedCard->GetCardNumber());
				m_RedCardOn = true;
			}

			else if (ChangeCard->GetCardColor() == ECard_Color::Blue)
			{
				CBlueCard* BlueCard = (CBlueCard*)ChangeCard;
				BlueCard->SetHitNumber(m_SelectedCard->GetCardNumber());
				m_BlueCardOn = true;
			}

			else if (ChangeCard->GetCardColor() == ECard_Color::Green)
			{
				CGreenCard* GreenCard = (CGreenCard*)ChangeCard;
				GreenCard->SetHitNumber(m_SelectedCard->GetCardNumber());
				m_GreenCardOn = true;
			}

			else if (ChangeCard->GetCardColor() == ECard_Color::Yellow)
			{
				CYellowCard* YellowCard = (CYellowCard*)ChangeCard;
				YellowCard->SetHitNumber(m_SelectedCard->GetCardNumber());
				m_YellowCardOn = true;
			}

			else
			{
				return;
			}

			m_SelectedCard->SetActive(false);
			m_SelectedCard = nullptr;

			return;
		}
	}
}

void CTheSeed2F::ResetSpawn(int SpawnNumber)
{
	m_SpawnInfo[SpawnNumber].Spawn = false;
}

void CTheSeed2F::CreateAnimationSequence()
{
	PlayerAnimationSequence();
	
	PlayerEffectAnimationSequence();

	MonsterAnimationSequence();

	ObjectAnimationSequence1();

	ObjectAnimationSequence2();

	std::vector<std::wstring>	vecFileName;

	for (int i = 0; i <= 11; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/UI/clear_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("Clear",
		"Clear", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 127.f, 149.f, 193 / 127.f, 122 / 149.f);
	CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 200.f, 113.f, 163 / 200.f, 100 / 113.f);
	CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 262.f, 112.f, 165 / 262.f, 99 / 112.f);
	CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 331.f, 110.f, 164 / 331.f, 98 / 110.f);
	CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 341.f, 138.f, 161 / 341.f, 113 / 138.f);
	CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 349.f, 158.f, 161 / 349.f, 123 / 158.f);
	CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 345.f, 151.f, 161 / 345.f, 119 / 151.f);
	CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 323.f, 100.f, 161 / 323.f, 93 / 100.f);
	CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 398.f, 119.f, 197 / 398.f, 108 / 119.f);
	CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 418.f, 125.f, 207 / 418.f, 110 / 125.f);
	CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 357.f, 102.f, 178 / 357.f, 94 / 102.f);
	CResourceManager::GetInst()->AddAnimationFrame("Clear", 0.f, 0.f, 347.f, 92.f, 173 / 347.f, 89 / 92.f);

	CResourceManager::GetInst()->SetColorKey("Clear", 255, 0, 255);
}

void CTheSeed2F::PlayerAnimationSequence()
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

void CTheSeed2F::PlayerEffectAnimationSequence()
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

void CTheSeed2F::MonsterAnimationSequence()
{
	// 헥터
	std::vector<std::wstring>	vecFileName;

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Monster/Left/Hector_Stand_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("HectorLeftStand",
		"HectorLeftStand", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftStand", 0.f, 0.f, 102.f, 56.f, 50 / 102.f, 56 / 56.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftStand", 0.f, 0.f, 127.f, 54.f, 75 / 127.f, 54 / 54.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftStand", 0.f, 0.f, 133.f, 56.f, 81 / 133.f, 56 / 56.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftStand", 0.f, 0.f, 136.f, 54.f, 87 / 136.f, 54 / 54.f);

	CResourceManager::GetInst()->SetColorKey("HectorLeftStand", 255, 0, 255);


	vecFileName.clear();


	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Monster/Right/Hector_Stand_Right_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("HectorRightStand",
		"HectorRightStand", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("HectorRightStand", 0.f, 0.f, 102.f, 56.f, 52 / 102.f, 56 / 56.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorRightStand", 0.f, 0.f, 127.f, 54.f, 52 / 127.f, 54 / 54.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorRightStand", 0.f, 0.f, 133.f, 56.f, 52 / 133.f, 56 / 56.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorRightStand", 0.f, 0.f, 136.f, 54.f, 49 / 136.f, 54 / 54.f);

	CResourceManager::GetInst()->SetColorKey("HectorRightStand", 255, 0, 255);


	vecFileName.clear();


	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Monster/Left/Hector_Move_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("HectorLeftMove",
		"HectorLeftMove", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftMove", 0.f, 0.f, 109.f, 57.f, 54 / 109.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftMove", 0.f, 0.f, 109.f, 55.f, 54 / 109.f, 55 / 55.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftMove", 0.f, 0.f, 106.f, 56.f, 53 / 106.f, 57 / 56.f);

	CResourceManager::GetInst()->SetColorKey("HectorLeftMove", 255, 0, 255);


	vecFileName.clear();


	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Monster/Right/Hector_Move_Right_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("HectorRightMove",
		"HectorRightMove", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("HectorRightMove", 0.f, 0.f, 109.f, 57.f, 55 / 109.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorRightMove", 0.f, 0.f, 109.f, 55.f, 55 / 109.f, 55 / 55.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorRightMove", 0.f, 0.f, 106.f, 56.f, 53 / 106.f, 57 / 56.f);

	CResourceManager::GetInst()->SetColorKey("HectorRightMove", 255, 0, 255);


	vecFileName.clear();


	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Monster/Left/Hector_Attack_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("HectorLeftAttack",
		"HectorLeftAttack", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftAttack", 0.f, 0.f, 102.f, 57.f, 49 / 102.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftAttack", 0.f, 0.f, 102.f, 57.f, 49 / 102.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftAttack", 0.f, 0.f, 102.f, 57.f, 45 / 102.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftAttack", 0.f, 0.f, 103.f, 57.f, 52 / 103.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftAttack", 0.f, 0.f, 107.f, 57.f, 52 / 107.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftAttack", 0.f, 0.f, 111.f, 57.f, 52 / 111.f, 57 / 57.f);

	CResourceManager::GetInst()->SetColorKey("HectorLeftAttack", 255, 0, 255);


	vecFileName.clear();


	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Monster/Right/Hector_Attack_Right_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("HectorRightAttack",
		"HectorRightAttack", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("HectorRightAttack", 0.f, 0.f, 102.f, 57.f, 53 / 102.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorRightAttack", 0.f, 0.f, 102.f, 57.f, 53 / 102.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorRightAttack", 0.f, 0.f, 102.f, 57.f, 57 / 102.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorRightAttack", 0.f, 0.f, 103.f, 57.f, 51 / 103.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorRightAttack", 0.f, 0.f, 107.f, 57.f, 55 / 107.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorRightAttack", 0.f, 0.f, 111.f, 57.f, 59 / 111.f, 57 / 57.f);

	CResourceManager::GetInst()->SetColorKey("HectorRightAttack", 255, 0, 255);


	vecFileName.clear();


	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Monster/Left/Hector_Die_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("HectorLeftDie",
		"HectorLeftDie", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftDie", 0.f, 0.f, 106.f, 44.f, 47 / 106.f, 44 / 44.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftDie", 0.f, 0.f, 109.f, 39.f, 50 / 109.f, 39 / 39.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftDie", 0.f, 0.f, 109.f, 34.f, 52 / 109.f, 34 / 34.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftDie", 0.f, 0.f, 100.f, 32.f, 52 / 100.f, 32 / 32.f);

	CResourceManager::GetInst()->SetColorKey("HectorLeftDie", 255, 0, 255);


	vecFileName.clear();


	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Monster/Right/Hector_Die_Right_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("HectorRightDie",
		"HectorRightDie", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("HectorRightDie", 0.f, 0.f, 106.f, 44.f, 59 / 106.f, 44 / 44.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorRightDie", 0.f, 0.f, 109.f, 39.f, 59 / 109.f, 39 / 39.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorRightDie", 0.f, 0.f, 109.f, 34.f, 57 / 109.f, 34 / 34.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorRightDie", 0.f, 0.f, 100.f, 32.f, 48 / 100.f, 32 / 32.f);

	CResourceManager::GetInst()->SetColorKey("HectorRightDie", 255, 0, 255);


	CResourceManager::GetInst()->CreateAnimationSequence("HectorLeftHit",
		"HectorLeftHit", TEXT("MapleStory/TheSeed_2F/Monster/Left/Hector_Hit_0.bmp"), TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftHit", 0.f, 0.f, 98.f, 46.f, 48 / 98.f, 46 / 46.f);

	CResourceManager::GetInst()->SetColorKey("HectorLeftHit", 255, 0, 255);


	CResourceManager::GetInst()->CreateAnimationSequence("HectorRightHit",
		"HectorRightHit", TEXT("MapleStory/TheSeed_2F/Monster/Right/Hector_Hit_Right_0.bmp"), TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("HectorRightHit", 0.f, 0.f, 98.f, 46.f, 50 / 98.f, 46 / 46.f);

	CResourceManager::GetInst()->SetColorKey("HectorRightHit", 255, 0, 255);


	CResourceManager::GetInst()->CreateAnimationSequence("HectorLeftJump",
		"HectorLeftJump", TEXT("MapleStory/TheSeed_2F/Monster/Left/Hector_Jump_0.bmp"), TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftJump", 0.f, 0.f, 109.f, 55.f, 54 / 109.f, 55 / 55.f);

	CResourceManager::GetInst()->SetColorKey("HectorLeftJump", 255, 0, 255);


	CResourceManager::GetInst()->CreateAnimationSequence("HectorRightJump",
		"HectorRightJump", TEXT("MapleStory/TheSeed_2F/Monster/Right/Hector_Jump_Right_0.bmp"), TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("HectorRightJump", 0.f, 0.f, 109.f, 55.f, 55 / 109.f, 55 / 55.f);

	CResourceManager::GetInst()->SetColorKey("HectorRightJump", 255, 0, 255);


	// 화이트팽
	vecFileName.clear();


	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Monster/Left/WhiteFang_Stand_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("WhiteFangLeftStand",
		"WhiteFangLeftStand", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangLeftStand", 0.f, 0.f, 102.f, 56.f, 50 / 102.f, 56 / 56.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangLeftStand", 0.f, 0.f, 127.f, 54.f, 75 / 127.f, 54 / 54.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangLeftStand", 0.f, 0.f, 133.f, 56.f, 81 / 133.f, 56 / 56.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangLeftStand", 0.f, 0.f, 136.f, 54.f, 87 / 136.f, 54 / 54.f);

	CResourceManager::GetInst()->SetColorKey("WhiteFangLeftStand", 255, 0, 255);


	vecFileName.clear();


	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Monster/Right/WhiteFang_Stand_Right_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("WhiteFangRightStand",
		"WhiteFangRightStand", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangRightStand", 0.f, 0.f, 102.f, 56.f, 52 / 102.f, 56 / 56.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangRightStand", 0.f, 0.f, 127.f, 54.f, 52 / 127.f, 54 / 54.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangRightStand", 0.f, 0.f, 133.f, 56.f, 52 / 133.f, 56 / 56.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangRightStand", 0.f, 0.f, 136.f, 54.f, 49 / 136.f, 54 / 54.f);

	CResourceManager::GetInst()->SetColorKey("WhiteFangRightStand", 255, 0, 255);


	vecFileName.clear();


	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Monster/Left/WhiteFang_Move_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("WhiteFangLeftMove",
		"WhiteFangLeftMove", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangLeftMove", 0.f, 0.f, 109.f, 57.f, 54 / 109.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangLeftMove", 0.f, 0.f, 109.f, 55.f, 54 / 109.f, 55 / 55.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangLeftMove", 0.f, 0.f, 106.f, 56.f, 53 / 106.f, 57 / 56.f);

	CResourceManager::GetInst()->SetColorKey("WhiteFangLeftMove", 255, 0, 255);


	vecFileName.clear();


	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Monster/Right/WhiteFang_Move_Right_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("WhiteFangRightMove",
		"WhiteFangRightMove", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangRightMove", 0.f, 0.f, 109.f, 57.f, 55 / 109.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangRightMove", 0.f, 0.f, 109.f, 55.f, 55 / 109.f, 55 / 55.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangRightMove", 0.f, 0.f, 106.f, 56.f, 53 / 106.f, 57 / 56.f);

	CResourceManager::GetInst()->SetColorKey("WhiteFangRightMove", 255, 0, 255);


	vecFileName.clear();


	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Monster/Left/WhiteFang_Attack_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("WhiteFangLeftAttack",
		"WhiteFangLeftAttack", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangLeftAttack", 0.f, 0.f, 102.f, 57.f, 49 / 102.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangLeftAttack", 0.f, 0.f, 102.f, 57.f, 49 / 102.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangLeftAttack", 0.f, 0.f, 102.f, 57.f, 45 / 102.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangLeftAttack", 0.f, 0.f, 103.f, 57.f, 52 / 103.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangLeftAttack", 0.f, 0.f, 107.f, 57.f, 52 / 107.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangLeftAttack", 0.f, 0.f, 111.f, 57.f, 52 / 111.f, 57 / 57.f);

	CResourceManager::GetInst()->SetColorKey("WhiteFangLeftAttack", 255, 0, 255);


	vecFileName.clear();


	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Monster/Right/WhiteFang_Attack_Right_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("WhiteFangRightAttack",
		"WhiteFangRightAttack", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangRightAttack", 0.f, 0.f, 102.f, 57.f, 53 / 102.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangRightAttack", 0.f, 0.f, 102.f, 57.f, 53 / 102.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangRightAttack", 0.f, 0.f, 102.f, 57.f, 57 / 102.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangRightAttack", 0.f, 0.f, 103.f, 57.f, 51 / 103.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangRightAttack", 0.f, 0.f, 107.f, 57.f, 55 / 107.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangRightAttack", 0.f, 0.f, 111.f, 57.f, 59 / 111.f, 57 / 57.f);

	CResourceManager::GetInst()->SetColorKey("WhiteFangRightAttack", 255, 0, 255);


	vecFileName.clear();


	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Monster/Left/WhiteFang_Die_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("WhiteFangLeftDie",
		"WhiteFangLeftDie", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangLeftDie", 0.f, 0.f, 106.f, 44.f, 47 / 106.f, 44 / 44.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangLeftDie", 0.f, 0.f, 109.f, 39.f, 50 / 109.f, 39 / 39.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangLeftDie", 0.f, 0.f, 109.f, 34.f, 52 / 109.f, 34 / 34.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangLeftDie", 0.f, 0.f, 100.f, 32.f, 52 / 100.f, 32 / 32.f);

	CResourceManager::GetInst()->SetColorKey("WhiteFangLeftDie", 255, 0, 255);


	vecFileName.clear();


	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Monster/Right/WhiteFang_Die_Right_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("WhiteFangRightDie",
		"WhiteFangRightDie", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangRightDie", 0.f, 0.f, 106.f, 44.f, 59 / 106.f, 44 / 44.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangRightDie", 0.f, 0.f, 109.f, 39.f, 59 / 109.f, 39 / 39.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangRightDie", 0.f, 0.f, 109.f, 34.f, 57 / 109.f, 34 / 34.f);
	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangRightDie", 0.f, 0.f, 100.f, 32.f, 48 / 100.f, 32 / 32.f);

	CResourceManager::GetInst()->SetColorKey("WhiteFangRightDie", 255, 0, 255);


	CResourceManager::GetInst()->CreateAnimationSequence("WhiteFangLeftHit",
		"WhiteFangLeftHit", TEXT("MapleStory/TheSeed_2F/Monster/Left/WhiteFang_Hit_0.bmp"), TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangLeftHit", 0.f, 0.f, 98.f, 46.f, 48 / 98.f, 46 / 46.f);

	CResourceManager::GetInst()->SetColorKey("WhiteFangLeftHit", 255, 0, 255);


	CResourceManager::GetInst()->CreateAnimationSequence("WhiteFangRightHit",
		"WhiteFangRightHit", TEXT("MapleStory/TheSeed_2F/Monster/Right/WhiteFang_Hit_Right_0.bmp"), TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangRightHit", 0.f, 0.f, 98.f, 46.f, 50 / 98.f, 46 / 46.f);

	CResourceManager::GetInst()->SetColorKey("WhiteFangRightHit", 255, 0, 255);


	CResourceManager::GetInst()->CreateAnimationSequence("WhiteFangLeftJump",
		"WhiteFangLeftJump", TEXT("MapleStory/TheSeed_2F/Monster/Left/WhiteFang_Jump_0.bmp"), TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangLeftJump", 0.f, 0.f, 109.f, 55.f, 54 / 109.f, 55 / 55.f);

	CResourceManager::GetInst()->SetColorKey("WhiteFangLeftJump", 255, 0, 255);


	CResourceManager::GetInst()->CreateAnimationSequence("WhiteFangRightJump",
		"WhiteFangRightJump", TEXT("MapleStory/TheSeed_2F/Monster/Right/WhiteFang_Jump_Right_0.bmp"), TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("WhiteFangRightJump", 0.f, 0.f, 109.f, 55.f, 55 / 109.f, 55 / 55.f);

	CResourceManager::GetInst()->SetColorKey("WhiteFangRightJump", 255, 0, 255);



	vecFileName.clear();


	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Monster/Left/WhiteFang_Attack_Effect_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("HectorLeftAttackEffect",
		"HectorLeftAttackEffect", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftAttackEffect", 0.f, 0.f, 109.f, 57.f, 79 / 109.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftAttackEffect", 0.f, 0.f, 102.f, 58.f, 107 / 102.f, 58 / 58.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorLeftAttackEffect", 0.f, 0.f, 107.f, 56.f, 161 / 133.f, 56 / 56.f);

	CResourceManager::GetInst()->SetColorKey("HectorLeftAttackEffect", 255, 0, 255);

	vecFileName.clear();


	for (int i = 0; i <= 2; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Monster/Right/WhiteFang_Attack_Effect_%d_Right.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("HectorRightAttackEffect",
		"HectorRightAttackEffect", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("HectorRightAttackEffect", 0.f, 0.f, 109.f, 57.f, 30 / 109.f, 57 / 57.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorRightAttackEffect", 0.f, 0.f, 102.f, 58.f, -5 / 102.f, 58 / 58.f);
	CResourceManager::GetInst()->AddAnimationFrame("HectorRightAttackEffect", 0.f, 0.f, 107.f, 56.f, -28 / 133.f, 56 / 56.f);

	CResourceManager::GetInst()->SetColorKey("HectorRightAttackEffect", 255, 0, 255);
}

void CTheSeed2F::ObjectAnimationSequence1()
{
	// BlueCard
	std::vector<std::wstring>	vecFileName;

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/BlueCard1_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("BlueCard1",
		"BlueCard1", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("BlueCard1", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard1", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard1", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard1", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("BlueCard1", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/BlueCard2_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("BlueCard2",
		"BlueCard2", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("BlueCard2", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard2", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard2", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard2", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("BlueCard2", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/BlueCard3_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("BlueCard3",
		"BlueCard3", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("BlueCard3", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard3", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard3", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard3", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("BlueCard3", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/BlueCard4_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("BlueCard4",
		"BlueCard4", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("BlueCard4", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard4", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard4", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard4", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("BlueCard4", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/BlueCard5_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("BlueCard5",
		"BlueCard5", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("BlueCard5", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard5", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard5", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard5", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("BlueCard5", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/BlueCard6_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("BlueCard6",
		"BlueCard6", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("BlueCard6", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard6", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard6", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard6", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("BlueCard6", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/BlueCard7_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("BlueCard7",
		"BlueCard7", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("BlueCard7", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard7", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard7", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCard7", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("BlueCard7", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/BlueCard_Hit_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("BlueCardHit",
		"BlueCardHit", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("BlueCardHit", 0.f, 0.f, 100.f, 108.f, 46 / 100.f, 165 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCardHit", 0.f, 0.f, 100.f, 152.f, 46 / 100.f, 222 / 152.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCardHit", 0.f, 0.f, 101.f, 157.f, 46 / 101.f, 237 / 157.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCardHit", 0.f, 0.f, 101.f, 162.f, 46 / 101.f, 251 / 162.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCardHit", 0.f, 0.f, 100.f, 186.f, 46 / 100.f, 264 / 186.f);
	CResourceManager::GetInst()->AddAnimationFrame("BlueCardHit", 0.f, 0.f, 100.f, 118.f, 46 / 100.f, 247 / 118.f);

	CResourceManager::GetInst()->SetColorKey("BlueCardHit", 255, 0, 255);


	// GreenCard
	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/GreenCard1_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("GreenCard1",
		"GreenCard1", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("GreenCard1", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard1", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard1", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard1", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("GreenCard1", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/GreenCard2_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("GreenCard2",
		"GreenCard2", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("GreenCard2", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard2", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard2", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard2", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("GreenCard2", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/GreenCard3_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("GreenCard3",
		"GreenCard3", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("GreenCard3", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard3", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard3", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard3", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("GreenCard3", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/GreenCard4_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("GreenCard4",
		"GreenCard4", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("GreenCard4", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard4", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard4", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard4", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("GreenCard4", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/GreenCard5_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("GreenCard5",
		"GreenCard5", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("GreenCard5", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard5", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard5", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard5", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("GreenCard5", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/GreenCard6_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("GreenCard6",
		"GreenCard6", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("GreenCard6", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard6", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard6", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard6", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("GreenCard6", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/GreenCard7_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("GreenCard7",
		"GreenCard7", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("GreenCard7", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard7", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard7", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCard7", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("GreenCard7", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/GreenCard_Hit_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("GreenCardHit",
		"GreenCardHit", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("GreenCardHit", 0.f, 0.f, 100.f, 108.f, 46 / 100.f, 165 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCardHit", 0.f, 0.f, 100.f, 152.f, 46 / 100.f, 222 / 152.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCardHit", 0.f, 0.f, 101.f, 157.f, 46 / 101.f, 237 / 157.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCardHit", 0.f, 0.f, 101.f, 162.f, 46 / 101.f, 251 / 162.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCardHit", 0.f, 0.f, 100.f, 186.f, 46 / 100.f, 264 / 186.f);
	CResourceManager::GetInst()->AddAnimationFrame("GreenCardHit", 0.f, 0.f, 100.f, 118.f, 46 / 100.f, 247 / 118.f);

	CResourceManager::GetInst()->SetColorKey("GreenCardHit", 255, 0, 255);


	// RedCard
	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/RedCard1_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("RedCard1",
		"RedCard1", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("RedCard1", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard1", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard1", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard1", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("RedCard1", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/RedCard2_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("RedCard2",
		"RedCard2", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("RedCard2", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard2", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard2", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard2", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("RedCard2", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/RedCard3_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("RedCard3",
		"RedCard3", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("RedCard3", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard3", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard3", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard3", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("RedCard3", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/RedCard4_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("RedCard4",
		"RedCard4", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("RedCard4", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard4", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard4", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard4", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("RedCard4", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/RedCard5_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("RedCard5",
		"RedCard5", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("RedCard5", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard5", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard5", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard5", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("RedCard5", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/RedCard6_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("RedCard6",
		"RedCard6", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("RedCard6", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard6", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard6", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard6", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("RedCard6", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/RedCard7_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("RedCard7",
		"RedCard7", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("RedCard7", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard7", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard7", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCard7", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("RedCard7", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/RedCard_Hit_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("RedCardHit",
		"RedCardHit", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("RedCardHit", 0.f, 0.f, 100.f, 108.f, 46 / 100.f, 165 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCardHit", 0.f, 0.f, 100.f, 152.f, 46 / 100.f, 222 / 152.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCardHit", 0.f, 0.f, 101.f, 157.f, 46 / 101.f, 237 / 157.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCardHit", 0.f, 0.f, 101.f, 162.f, 46 / 101.f, 251 / 162.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCardHit", 0.f, 0.f, 100.f, 186.f, 46 / 100.f, 264 / 186.f);
	CResourceManager::GetInst()->AddAnimationFrame("RedCardHit", 0.f, 0.f, 100.f, 118.f, 46 / 100.f, 247 / 118.f);

	CResourceManager::GetInst()->SetColorKey("RedCardHit", 255, 0, 255);
}

void CTheSeed2F::ObjectAnimationSequence2()
{
	// VioletCard
	std::vector<std::wstring>	vecFileName;

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/VioletCard_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("VioletCard",
		"VioletCard", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("VioletCard", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("VioletCard", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("VioletCard", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("VioletCard", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("VioletCard", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/VioletCard_Hit_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("VioletCardHit",
		"VioletCardHit", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("VioletCardHit", 0.f, 0.f, 100.f, 108.f, 46 / 100.f, 165 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("VioletCardHit", 0.f, 0.f, 100.f, 152.f, 46 / 100.f, 222 / 152.f);
	CResourceManager::GetInst()->AddAnimationFrame("VioletCardHit", 0.f, 0.f, 101.f, 157.f, 46 / 101.f, 237 / 157.f);
	CResourceManager::GetInst()->AddAnimationFrame("VioletCardHit", 0.f, 0.f, 101.f, 162.f, 46 / 101.f, 251 / 162.f);
	CResourceManager::GetInst()->AddAnimationFrame("VioletCardHit", 0.f, 0.f, 100.f, 186.f, 46 / 100.f, 264 / 186.f);
	CResourceManager::GetInst()->AddAnimationFrame("VioletCardHit", 0.f, 0.f, 100.f, 118.f, 46 / 100.f, 247 / 118.f);

	CResourceManager::GetInst()->SetColorKey("VioletCardHit", 255, 0, 255);


	// YellowCard
	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/YellowCard1_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("YellowCard1",
		"YellowCard1", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("YellowCard1", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard1", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard1", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard1", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("YellowCard1", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/YellowCard2_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("YellowCard2",
		"YellowCard2", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("YellowCard2", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard2", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard2", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard2", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("YellowCard2", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/YellowCard3_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("YellowCard3",
		"YellowCard3", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("YellowCard3", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard3", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard3", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard3", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("YellowCard3", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/YellowCard4_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("YellowCard4",
		"YellowCard4", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("YellowCard4", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard4", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard4", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard4", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("YellowCard4", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/YellowCard5_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("YellowCard5",
		"YellowCard5", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("YellowCard5", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard5", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard5", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard5", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("YellowCard5", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/YellowCard6_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("YellowCard6",
		"YellowCard6", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("YellowCard6", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard6", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard6", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard6", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("YellowCard6", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 3; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/YellowCard7_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("YellowCard7",
		"YellowCard7", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("YellowCard7", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 247 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard7", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 248 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard7", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 249 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCard7", 0.f, 0.f, 82.f, 108.f, 41 / 82.f, 250 / 108.f);

	CResourceManager::GetInst()->SetColorKey("YellowCard7", 255, 0, 255);

	vecFileName.clear();

	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/YellowCard_Hit_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("YellowCardHit",
		"YellowCardHit", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("YellowCardHit", 0.f, 0.f, 100.f, 108.f, 46 / 100.f, 165 / 108.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCardHit", 0.f, 0.f, 100.f, 152.f, 46 / 100.f, 222 / 152.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCardHit", 0.f, 0.f, 101.f, 157.f, 46 / 101.f, 237 / 157.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCardHit", 0.f, 0.f, 101.f, 162.f, 46 / 101.f, 251 / 162.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCardHit", 0.f, 0.f, 100.f, 186.f, 46 / 100.f, 264 / 186.f);
	CResourceManager::GetInst()->AddAnimationFrame("YellowCardHit", 0.f, 0.f, 100.f, 118.f, 46 / 100.f, 247 / 118.f);

	CResourceManager::GetInst()->SetColorKey("YellowCardHit", 255, 0, 255);



	// SealBreakCard
	CResourceManager::GetInst()->CreateAnimationSequence("SealBreakCard",
		"SealBreakCard", TEXT("MapleStory/TheSeed_2F/Object/SealBreakCard.bmp"), TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("SealBreakCard", 0.f, 0.f, 36.f, 36.f, 18 / 36.f, 36 / 36.f);

	CResourceManager::GetInst()->SetColorKey("SealBreakCard", 255, 0, 255);


	vecFileName.clear();

	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/TheSeed_2F/Object/SealBreakCard.bmp"));
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("SealBreakCardGround",
		"SealBreakCardGround", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("SealBreakCardGround", 0.f, 0.f, 36.f, 36.f, 18 / 36.f, 36 / 36.f);
	CResourceManager::GetInst()->AddAnimationFrame("SealBreakCardGround", 0.f, 0.f, 36.f, 36.f, 18 / 36.f, 37 / 36.f);
	CResourceManager::GetInst()->AddAnimationFrame("SealBreakCardGround", 0.f, 0.f, 36.f, 36.f, 18 / 36.f, 38 / 36.f);
	CResourceManager::GetInst()->AddAnimationFrame("SealBreakCardGround", 0.f, 0.f, 36.f, 36.f, 18 / 36.f, 39 / 36.f);
	CResourceManager::GetInst()->AddAnimationFrame("SealBreakCardGround", 0.f, 0.f, 36.f, 36.f, 18 / 36.f, 38 / 36.f);
	CResourceManager::GetInst()->AddAnimationFrame("SealBreakCardGround", 0.f, 0.f, 36.f, 36.f, 18 / 36.f, 37 / 36.f);

	CResourceManager::GetInst()->SetColorKey("SealBreakCardGround", 255, 0, 255);
}