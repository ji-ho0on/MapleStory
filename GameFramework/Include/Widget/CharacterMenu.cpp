#include "CharacterMenu.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "ImageWidget.h"
#include "Button.h"

CCharacterMenu::CCharacterMenu()
{
}

CCharacterMenu::~CCharacterMenu()
{
}

bool CCharacterMenu::Init()
{
	if (!CWidgetWindow::Init())
		return false;


	SetSize(121.f, 177.f);
	SetPos(0.f, 0.f);

	m_CharacterMenuBackStart = CreateWidget<CImageWidget>("CharacterMenuBackStart");
	m_CharacterMenuBackStart->SetTexture("CharacterMenuBackStart", TEXT("MapleStory/UI/submenu_backgrnd_0.bmp"));
	m_CharacterMenuBackStart->SetColorKey(255, 0, 255);
	m_CharacterMenuBackStart->SetSize(121.f, 29.f);
	m_CharacterMenuBackStart->SetPos(0.f, 0.f);
	m_CharacterMenuBackStart->SetZOrder(0);


	m_CharacterMenuBackMiddle1 = CreateWidget<CImageWidget>("CharacterMenuBackMiddle1");
	m_CharacterMenuBackMiddle1->SetTexture("CharacterMenuBackMiddle1", TEXT("MapleStory/UI/submenu_backgrnd_3.bmp"));
	m_CharacterMenuBackMiddle1->SetColorKey(255, 0, 255);
	m_CharacterMenuBackMiddle1->SetSize(121.f, 26.f);
	m_CharacterMenuBackMiddle1->SetPos(0.f, 29.f);
	m_CharacterMenuBackMiddle1->SetZOrder(0);


	m_CharacterMenuBackMiddle2 = CreateWidget<CImageWidget>("CharacterMenuBackMiddle2");
	m_CharacterMenuBackMiddle2->SetTexture("CharacterMenuBackMiddle2", TEXT("MapleStory/UI/submenu_backgrnd_3.bmp"));
	m_CharacterMenuBackMiddle2->SetColorKey(255, 0, 255);
	m_CharacterMenuBackMiddle2->SetSize(121.f, 26.f);
	m_CharacterMenuBackMiddle2->SetPos(0.f, 55.f);
	m_CharacterMenuBackMiddle2->SetZOrder(0);


	m_CharacterMenuBackMiddle3 = CreateWidget<CImageWidget>("CharacterMenuBackMiddle3");
	m_CharacterMenuBackMiddle3->SetTexture("CharacterMenuBackMiddle3", TEXT("MapleStory/UI/submenu_backgrnd_3.bmp"));
	m_CharacterMenuBackMiddle3->SetColorKey(255, 0, 255);
	m_CharacterMenuBackMiddle3->SetSize(121.f, 26.f);
	m_CharacterMenuBackMiddle3->SetPos(0.f, 81.f);
	m_CharacterMenuBackMiddle3->SetZOrder(0);


	m_CharacterMenuBackMiddle4 = CreateWidget<CImageWidget>("CharacterMenuBackMiddle4");
	m_CharacterMenuBackMiddle4->SetTexture("CharacterMenuBackMiddle4", TEXT("MapleStory/UI/submenu_backgrnd_3.bmp"));
	m_CharacterMenuBackMiddle4->SetColorKey(255, 0, 255);
	m_CharacterMenuBackMiddle4->SetSize(121.f, 26.f);
	m_CharacterMenuBackMiddle4->SetPos(0.f, 107.f);
	m_CharacterMenuBackMiddle4->SetZOrder(0);


	m_CharacterMenuBackEnd = CreateWidget<CImageWidget>("CharacterMenuBackEnd");
	m_CharacterMenuBackEnd->SetTexture("CharacterMenuBackEnd", TEXT("MapleStory/UI/submenu_backgrnd_2.bmp"));
	m_CharacterMenuBackEnd->SetColorKey(255, 0, 255);
	m_CharacterMenuBackEnd->SetSize(121.f, 44.f);
	m_CharacterMenuBackEnd->SetPos(0.f, 133.f);
	m_CharacterMenuBackEnd->SetZOrder(0);


	m_CharacterMenuTitle = CreateWidget<CImageWidget>("CharacterMenuTitle");
	m_CharacterMenuTitle->SetTexture("CharacterMenuTitle", TEXT("MapleStory/UI/submenu_title_character.bmp"));
	m_CharacterMenuTitle->SetColorKey(255, 0, 255);
	m_CharacterMenuTitle->SetSize(87.f, 16.f);
	m_CharacterMenuTitle->SetPos(17.f, 6.f);
	m_CharacterMenuTitle->SetZOrder(1);


	m_InfoButton = CreateWidget<CButton>("InfoButton");
	m_InfoButton->SetTexture("InfoButton", TEXT("MapleStory/UI/submenu_character_button_character.bmp"));
	m_InfoButton->SetColorKey(255, 0, 255);
	m_InfoButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(109.f, 26.f));
	m_InfoButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(109.f, 0.f), Vector2(218.f, 26.f));
	m_InfoButton->SetButtonStateData(EButton_State::Click, Vector2(218.f, 0.f), Vector2(327.f, 26.f));
	m_InfoButton->SetButtonStateData(EButton_State::Disable, Vector2(327.f, 0.f), Vector2(436.f, 26.f));
	m_InfoButton->SetPos(6.f, 29.f);
	m_InfoButton->SetZOrder(2);


	m_StatButton = CreateWidget<CButton>("StatButton");
	m_StatButton->SetTexture("StatButton", TEXT("MapleStory/UI/submenu_character_button_Stat.bmp"));
	m_StatButton->SetColorKey(255, 0, 255);
	m_StatButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(109.f, 26.f));
	m_StatButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(109.f, 0.f), Vector2(218.f, 26.f));
	m_StatButton->SetButtonStateData(EButton_State::Click, Vector2(218.f, 0.f), Vector2(327.f, 26.f));
	m_StatButton->SetButtonStateData(EButton_State::Disable, Vector2(327.f, 0.f), Vector2(436.f, 26.f));
	m_StatButton->SetPos(6.f, 55.f);
	m_StatButton->SetZOrder(2);


	m_EquipButton = CreateWidget<CButton>("EquipButton");
	m_EquipButton->SetTexture("EquipButton", TEXT("MapleStory/UI/submenu_character_button_Equip.bmp"));
	m_EquipButton->SetColorKey(255, 0, 255);
	m_EquipButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(109.f, 26.f));
	m_EquipButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(109.f, 0.f), Vector2(218.f, 26.f));
	m_EquipButton->SetButtonStateData(EButton_State::Click, Vector2(218.f, 0.f), Vector2(327.f, 26.f));
	m_EquipButton->SetButtonStateData(EButton_State::Disable, Vector2(327.f, 0.f), Vector2(436.f, 26.f));
	m_EquipButton->SetPos(6.f, 81.f);
	m_EquipButton->SetZOrder(2);


	m_InventoryButton = CreateWidget<CButton>("InventoryButton");
	m_InventoryButton->SetTexture("InventoryButton", TEXT("MapleStory/UI/submenu_character_button_Item.bmp"));
	m_InventoryButton->SetColorKey(255, 0, 255);
	m_InventoryButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(109.f, 26.f));
	m_InventoryButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(109.f, 0.f), Vector2(218.f, 26.f));
	m_InventoryButton->SetButtonStateData(EButton_State::Click, Vector2(218.f, 0.f), Vector2(327.f, 26.f));
	m_InventoryButton->SetButtonStateData(EButton_State::Disable, Vector2(327.f, 0.f), Vector2(436.f, 26.f));
	m_InventoryButton->SetPos(6.f, 107.f);
	m_InventoryButton->SetZOrder(2);


	m_SkillButton = CreateWidget<CButton>("SkillButton");
	m_SkillButton->SetTexture("SkillButton", TEXT("MapleStory/UI/submenu_character_button_Skill.bmp"));
	m_SkillButton->SetColorKey(255, 0, 255);
	m_SkillButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(109.f, 26.f));
	m_SkillButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(109.f, 0.f), Vector2(218.f, 26.f));
	m_SkillButton->SetButtonStateData(EButton_State::Click, Vector2(218.f, 0.f), Vector2(327.f, 26.f));
	m_SkillButton->SetButtonStateData(EButton_State::Disable, Vector2(327.f, 0.f), Vector2(436.f, 26.f));
	m_SkillButton->SetPos(6.f, 133.f);
	m_SkillButton->SetZOrder(2);


	return true;
}

void CCharacterMenu::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}
