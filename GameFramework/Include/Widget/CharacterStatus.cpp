#include "CharacterStatus.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "ProgressBar.h"
#include "ImageWidget.h"
#include "Number.h"
#include "Text.h"
#include "Button.h"
#include "../GameObject/Player.h"
#include "CharacterMenu.h"
#include "EventMenu.h"
#include "CommunityMenu.h"
#include "SettingMenu.h"
#include "SubMenu.h"

CCharacterStatus::CCharacterStatus()
{
}

CCharacterStatus::~CCharacterStatus()
{
}

bool CCharacterStatus::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	SetSize(1280.f, 83.f);
	SetPos(0.f, 637.f);

	m_HP = 100;
	m_HPMax = 100;

	m_MP = 100;
	m_MPMax = 100;

	m_Level = 1;
	m_EXP = 0;

	// 경험치
	m_EXPBarBack = CreateWidget<CImageWidget>("EXPBarBack");
	m_EXPBarBack->SetTexture("EXPBarBack", TEXT("MapleStory/UI/EXPBar_1280_layer_back.bmp"));
	m_EXPBarBack->SetColorKey(255, 0, 255);
	m_EXPBarBack->SetSize(1280.f, 10.f);
	m_EXPBarBack->SetPos(0.f, 74.f);
	m_EXPBarBack->SetZOrder(0);

	m_EXPBar = CreateWidget<CProgressBar>("EXPBar");
	m_EXPBar->SetTexture(EProgressBar_Texture_Type::Bar, "EXPBar", TEXT("MapleStory/UI/EXPBar_1280_layer_gauge.bmp"));
	m_EXPBar->SetSize(1264.f, 7.f);
	m_EXPBar->SetPos(15.f, 76.f);
	m_EXPBar->SetBarDir(EProgressBar_Dir::LeftToRight);
	m_EXPBar->SetZOrder(1);
	m_EXPBar->SetValue(0.f);

	m_EXPBarFrame = CreateWidget<CImageWidget>("EXPBarFrame");
	m_EXPBarFrame->SetTexture("EXPBarFrame", TEXT("MapleStory/UI/EXPBar_1280_layer_cover.bmp"));
	m_EXPBarFrame->SetColorKey(255, 0, 255);
	m_EXPBarFrame->SetSize(1010.f, 7.f);
	m_EXPBarFrame->SetPos(140.f, 76.f);
	m_EXPBarFrame->SetZOrder(2);

	std::vector<std::wstring>	vecFileName;

	for (int i = 0; i <= 9; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/UI/EXPBar_number_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	m_EXPNumber = CreateWidget<CNumber>("EXPNumber");
	m_EXPNumber->SetTexture("EXPNumber", vecFileName);
	m_EXPNumber->SetColorKey(255, 0, 255);
	m_EXPNumber->SetSize(7.f, 9.f);
	m_EXPNumber->SetPos(620.f, 75.f);
	m_EXPNumber->SetNumber(0);
	m_EXPNumber->SetZOrder(3);

	m_EXPBracketLeft = CreateWidget<CImageWidget>("EXPBracketLeft");
	m_EXPBracketLeft->SetTexture("EXPBracketLeft", TEXT("MapleStory/UI/EXPBar_number_[.bmp"));
	m_EXPBracketLeft->SetColorKey(255, 0, 255);
	m_EXPBracketLeft->SetSize(7.f, 9.f);
	m_EXPBracketLeft->SetPos(642.f, 75.f);
	m_EXPBracketLeft->SetZOrder(3);

	m_EXPLeft = CreateWidget<CNumber>("EXPLeft");
	m_EXPLeft->SetTexture("EXPLeft", vecFileName);
	m_EXPLeft->SetColorKey(255, 0, 255);
	m_EXPLeft->SetSize(7.f, 9.f);
	m_EXPLeft->SetPos(650.f, 75.f);
	m_EXPLeft->SetNumber(0);
	m_EXPLeft->SetZOrder(3);

	m_EXPDot = CreateWidget<CImageWidget>("EXPDot");
	m_EXPDot->SetTexture("EXPDot", TEXT("MapleStory/UI/EXPBar_number_dot.bmp"));
	m_EXPDot->SetColorKey(255, 0, 255);
	m_EXPDot->SetSize(3.f, 3.f);
	m_EXPDot->SetPos(664.f, 80.f);
	m_EXPDot->SetZOrder(3);

	m_EXPRight = CreateWidget<CNumber>("EXPRight");
	m_EXPRight->SetTexture("EXPRight", vecFileName);
	m_EXPRight->SetColorKey(255, 0, 255);
	m_EXPRight->SetSize(7.f, 9.f);
	m_EXPRight->SetPos(668.f, 75.f);
	m_EXPRight->SetNumber(0);
	m_EXPRight->SetZOrder(3);

	m_EXPPercent = CreateWidget<CImageWidget>("EXPPercent");
	m_EXPPercent->SetTexture("EXPPercent", TEXT("MapleStory/UI/EXPBar_number_%.bmp"));
	m_EXPPercent->SetColorKey(255, 0, 255);
	m_EXPPercent->SetSize(9.f, 9.f);
	m_EXPPercent->SetPos(683.f, 75.f);
	m_EXPPercent->SetZOrder(3);

	m_EXPBracketRight = CreateWidget<CImageWidget>("EXPBracketRight");
	m_EXPBracketRight->SetTexture("EXPBracketRight", TEXT("MapleStory/UI/EXPBar_number_].bmp"));
	m_EXPBracketRight->SetColorKey(255, 0, 255);
	m_EXPBracketRight->SetSize(4.f, 9.f);
	m_EXPBracketRight->SetPos(694.f, 75.f);
	m_EXPBracketRight->SetZOrder(3);



	// HP, MP
	m_StatusBarBack = CreateWidget<CImageWidget>("StatusBarBack");
	m_StatusBarBack->SetTexture("StatusBarBack", TEXT("MapleStory/UI/status_backgrnd.bmp"));
	m_StatusBarBack->SetColorKey(255, 0, 255);
	m_StatusBarBack->SetSize(198.f, 37.f);
	m_StatusBarBack->SetPos(518.f, 31.f);
	m_StatusBarBack->SetZOrder(0);

	m_HPBar = CreateWidget<CProgressBar>("HPBar");
	m_HPBar->SetTexture(EProgressBar_Texture_Type::Bar, "HPBar", TEXT("MapleStory/UI/status_gauge_hp_layer_0.bmp"));
	m_HPBar->SetSize(171.f, 13.f);
	m_HPBar->SetPos(539.f, 38.f);
	m_HPBar->SetBarDir(EProgressBar_Dir::LeftToRight);
	m_HPBar->SetZOrder(1);

	m_MPBar = CreateWidget<CProgressBar>("MPBar");
	m_MPBar->SetTexture(EProgressBar_Texture_Type::Bar, "MPBar", TEXT("MapleStory/UI/status_gauge_mp_layer_0.bmp"));
	m_MPBar->SetSize(171.f, 13.f);
	m_MPBar->SetPos(539.f, 51.f);
	m_MPBar->SetBarDir(EProgressBar_Dir::LeftToRight);
	m_MPBar->SetZOrder(1);

	vecFileName.clear();

	for (int i = 0; i <= 9; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/UI/status_gauge_number_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	m_HPNumber = CreateWidget<CNumber>("HPNumber");
	m_HPNumber->SetTexture("HPNumber", vecFileName);
	m_HPNumber->SetColorKey(255, 0, 255);
	m_HPNumber->SetSize(7.f, 9.f);
	m_HPNumber->SetPos(587.f, 39.f);
	m_HPNumber->SetNumber(1000);
	m_HPNumber->SetZOrder(2);

	m_HPSlash = CreateWidget<CImageWidget>("HPSlash");
	m_HPSlash->SetTexture("HPSlash", TEXT("MapleStory/UI/status_gauge_number_slash.bmp"));
	m_HPSlash->SetColorKey(255, 0, 255);
	m_HPSlash->SetSize(6.f, 10.f);
	m_HPSlash->SetPos(624.f, 39.f);
	m_HPSlash->SetZOrder(2);

	m_HPMaxNumber = CreateWidget<CNumber>("HPMaxNumber");
	m_HPMaxNumber->SetTexture("HPMaxNumber", vecFileName);
	m_HPMaxNumber->SetColorKey(255, 0, 255);
	m_HPMaxNumber->SetSize(7.f, 9.f);
	m_HPMaxNumber->SetPos(637.f, 39.f);
	m_HPMaxNumber->SetNumber(1000);
	m_HPMaxNumber->SetZOrder(2);


	m_MPNumber = CreateWidget<CNumber>("MPNumber");
	m_MPNumber->SetTexture("MPNumber", vecFileName);
	m_MPNumber->SetColorKey(255, 0, 255);
	m_MPNumber->SetSize(7.f, 9.f);
	m_MPNumber->SetPos(587.f, 55.f);
	m_MPNumber->SetNumber(1000);
	m_MPNumber->SetZOrder(2);

	m_MPSlash = CreateWidget<CImageWidget>("MPSlash");
	m_MPSlash->SetTexture("MPSlash", TEXT("MapleStory/UI/status_gauge_number_slash.bmp"));
	m_MPSlash->SetColorKey(255, 0, 255);
	m_MPSlash->SetSize(6.f, 10.f);
	m_MPSlash->SetPos(624.f, 55.f);
	m_MPSlash->SetZOrder(2);

	m_MPMaxNumber = CreateWidget<CNumber>("MPMaxNumber");
	m_MPMaxNumber->SetTexture("MPMaxNumber", vecFileName);
	m_MPMaxNumber->SetColorKey(255, 0, 255);
	m_MPMaxNumber->SetSize(7.f, 9.f);
	m_MPMaxNumber->SetPos(637.f, 55.f);
	m_MPMaxNumber->SetNumber(1000);
	m_MPMaxNumber->SetZOrder(2);


	m_StatusBarFrame = CreateWidget<CImageWidget>("StatusBarFrame");
	m_StatusBarFrame->SetTexture("StatusBarFrame", TEXT("MapleStory/UI/status_layer_cover.bmp"));
	m_StatusBarFrame->SetColorKey(255, 0, 255);
	m_StatusBarFrame->SetSize(204.f, 70.f);
	m_StatusBarFrame->SetPos(515.f, 9.f);
	m_StatusBarFrame->SetZOrder(2);

	// 레벨
	m_LvImage = CreateWidget<CImageWidget>("LvImage");
	m_LvImage->SetTexture("LvImage", TEXT("MapleStory/UI/status_layer_Lv.bmp"));
	m_LvImage->SetColorKey(255, 0, 255);
	m_LvImage->SetSize(15.f, 10.f);
	m_LvImage->SetPos(537.f, 17.f);
	m_LvImage->SetZOrder(3);

	vecFileName.clear();

	for (int i = 0; i <= 9; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		wsprintf(FileName, TEXT("MapleStory/UI/status_lvNumber_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	m_LvNumber = CreateWidget<CNumber>("LvNumber");
	m_LvNumber->SetTexture("LvNumber", vecFileName);
	m_LvNumber->SetColorKey(255, 0, 255);
	m_LvNumber->SetSize(7.f, 10.f);
	m_LvNumber->SetPos(552.f, 17.f);
	m_LvNumber->SetNumber(200);
	m_LvNumber->SetZOrder(3);

	m_CharacterName = CreateWidget<CText>("CharacterName");
	m_CharacterName->SetText(TEXT("최지훈"));
	m_CharacterName->SetPos(595.f, 10.f);
	m_CharacterName->SetTextColor(255, 255, 255);
	m_CharacterName->SetZOrder(3);





	m_QuickSlotBack = CreateWidget<CImageWidget>("QuickSlotBack");
	m_QuickSlotBack->SetTexture("QuickSlotBack", TEXT("MapleStory/UI/quickSlot_backgrnd2.bmp"));
	m_QuickSlotBack->SetColorKey(255, 0, 255);
	m_QuickSlotBack->SetSize(347.f, 67.f);
	m_QuickSlotBack->SetPos(931.f, 7.f);
	m_QuickSlotBack->SetZOrder(0);

	// 스킬 아이콘
	m_SlashBlustIcon = CreateWidget<CProgressBar>("SlashBlustIcon");
	m_SlashBlustIcon->SetTexture(EProgressBar_Texture_Type::Back, "SlashBlustIconDisable", TEXT("MapleStory/UI/SlashBlust_icon_Disabled.bmp"));
	m_SlashBlustIcon->SetTexture(EProgressBar_Texture_Type::Bar, "SlashBlustIconEnable", TEXT("MapleStory/UI/SlashBlust_icon.bmp"));
	m_SlashBlustIcon->SetColorKey(EProgressBar_Texture_Type::Back, 255, 0, 255);
	m_SlashBlustIcon->SetColorKey(EProgressBar_Texture_Type::Bar, 255, 0, 255);
	m_SlashBlustIcon->SetSize(32.f, 32.f);
	m_SlashBlustIcon->SetPos(930.f, 41.f);
	m_SlashBlustIcon->SetBarDir(EProgressBar_Dir::BottomToTop);
	m_SlashBlustIcon->SetZOrder(1);

	m_RaisingBlowIcon = CreateWidget<CProgressBar>("RaisingBlowIcon");
	m_RaisingBlowIcon->SetTexture(EProgressBar_Texture_Type::Back, "RaisingBlowIconDisable", TEXT("MapleStory/UI/RaisingBlow_icon_Disabled.bmp"));
	m_RaisingBlowIcon->SetTexture(EProgressBar_Texture_Type::Bar, "RaisingBlowIconEnable", TEXT("MapleStory/UI/RaisingBlow_icon.bmp"));
	m_RaisingBlowIcon->SetColorKey(EProgressBar_Texture_Type::Back, 255, 0, 255);
	m_RaisingBlowIcon->SetColorKey(EProgressBar_Texture_Type::Bar, 255, 0, 255);
	m_RaisingBlowIcon->SetSize(32.f, 32.f);
	m_RaisingBlowIcon->SetPos(930.f, 6.f);
	m_RaisingBlowIcon->SetBarDir(EProgressBar_Dir::BottomToTop);
	m_RaisingBlowIcon->SetZOrder(1);


	m_QuickSlotFrame = CreateWidget<CImageWidget>("QuickSlotFrame");
	m_QuickSlotFrame->SetTexture("QuickSlotFrame", TEXT("MapleStory/UI/quickSlot_layer_cover2.bmp"));
	m_QuickSlotFrame->SetColorKey(255, 0, 255);
	m_QuickSlotFrame->SetSize(352.f, 73.f);
	m_QuickSlotFrame->SetPos(928.f, 3.f);
	m_QuickSlotFrame->SetZOrder(2);



	// 메뉴 버튼

	m_CashShopButton = CreateWidget<CButton>("CashShopButton");
	m_CashShopButton->SetTexture("CashShopButton", TEXT("MapleStory/UI/menu_button_CashShop.bmp"));
	m_CashShopButton->SetColorKey(255, 0, 255);
	m_CashShopButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(34.f, 37.f));
	m_CashShopButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(34.f, 0.f), Vector2(68.f, 37.f));
	m_CashShopButton->SetButtonStateData(EButton_State::Click, Vector2(68.f, 0.f), Vector2(102.f, 37.f));
	m_CashShopButton->SetButtonStateData(EButton_State::Disable, Vector2(102.f, 0.f), Vector2(136.f, 37.f));
	m_CashShopButton->SetPos(719.f, 40.f);
	m_CashShopButton->SetZOrder(4);

	m_CashShopButton->SetCallback<CCharacterStatus>(EButton_Sound_State::Click, this, &CCharacterStatus::CashShopButtonCallback);


	m_EventButton = CreateWidget<CButton>("EventButton");
	m_EventButton->SetTexture("EventButton", TEXT("MapleStory/UI/menu_button_Event.bmp"));
	m_EventButton->SetColorKey(255, 0, 255);
	m_EventButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(34.f, 37.f));
	m_EventButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(34.f, 0.f), Vector2(68.f, 37.f));
	m_EventButton->SetButtonStateData(EButton_State::Click, Vector2(68.f, 0.f), Vector2(102.f, 37.f));
	m_EventButton->SetButtonStateData(EButton_State::Disable, Vector2(102.f, 0.f), Vector2(136.f, 37.f));
	m_EventButton->SetPos(754.f, 40.f);
	m_EventButton->SetZOrder(4);

	m_EventButton->SetCallback<CCharacterStatus>(EButton_Sound_State::Click, this, &CCharacterStatus::EventButtonCallback);


	m_CharacterButton = CreateWidget<CButton>("CharacterButton");
	m_CharacterButton->SetTexture("CharacterButton", TEXT("MapleStory/UI/menu_button_Character.bmp"));
	m_CharacterButton->SetColorKey(255, 0, 255);
	m_CharacterButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(34.f, 37.f));
	m_CharacterButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(34.f, 0.f), Vector2(68.f, 37.f));
	m_CharacterButton->SetButtonStateData(EButton_State::Click, Vector2(68.f, 0.f), Vector2(102.f, 37.f));
	m_CharacterButton->SetButtonStateData(EButton_State::Disable, Vector2(102.f, 0.f), Vector2(136.f, 37.f));
	m_CharacterButton->SetPos(789.f, 40.f);
	m_CharacterButton->SetZOrder(4);

	m_CharacterButton->SetCallback<CCharacterStatus>(EButton_Sound_State::Click, this, &CCharacterStatus::CharacterButtonCallback);


	m_CommunityButton = CreateWidget<CButton>("CommunityButton");
	m_CommunityButton->SetTexture("CommunityButton", TEXT("MapleStory/UI/menu_button_Community.bmp"));
	m_CommunityButton->SetColorKey(255, 0, 255);
	m_CommunityButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(34.f, 37.f));
	m_CommunityButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(34.f, 0.f), Vector2(68.f, 37.f));
	m_CommunityButton->SetButtonStateData(EButton_State::Click, Vector2(68.f, 0.f), Vector2(102.f, 37.f));
	m_CommunityButton->SetButtonStateData(EButton_State::Disable, Vector2(102.f, 0.f), Vector2(136.f, 37.f));
	m_CommunityButton->SetPos(824.f, 40.f);
	m_CommunityButton->SetZOrder(4);

	m_CommunityButton->SetCallback<CCharacterStatus>(EButton_Sound_State::Click, this, &CCharacterStatus::CommunityButtonCallback);


	m_SettingButton = CreateWidget<CButton>("SettingButton");
	m_SettingButton->SetTexture("SettingButton", TEXT("MapleStory/UI/menu_button_Setting.bmp"));
	m_SettingButton->SetColorKey(255, 0, 255);
	m_SettingButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(34.f, 37.f));
	m_SettingButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(34.f, 0.f), Vector2(68.f, 37.f));
	m_SettingButton->SetButtonStateData(EButton_State::Click, Vector2(68.f, 0.f), Vector2(102.f, 37.f));
	m_SettingButton->SetButtonStateData(EButton_State::Disable, Vector2(102.f, 0.f), Vector2(136.f, 37.f));
	m_SettingButton->SetPos(859.f, 40.f);
	m_SettingButton->SetZOrder(4);

	m_SettingButton->SetCallback<CCharacterStatus>(EButton_Sound_State::Click, this, &CCharacterStatus::SettingButtonCallback);



	m_MenuButton = CreateWidget<CButton>("MenuButton");
	m_MenuButton->SetTexture("MenuButton", TEXT("MapleStory/UI/menu_button_Menu.bmp"));
	m_MenuButton->SetColorKey(255, 0, 255);
	m_MenuButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(34.f, 37.f));
	m_MenuButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(34.f, 0.f), Vector2(68.f, 37.f));
	m_MenuButton->SetButtonStateData(EButton_State::Click, Vector2(68.f, 0.f), Vector2(102.f, 37.f));
	m_MenuButton->SetButtonStateData(EButton_State::Disable, Vector2(102.f, 0.f), Vector2(136.f, 37.f));
	m_MenuButton->SetPos(894.f, 40.f);
	m_MenuButton->SetZOrder(4);

	m_MenuButton->SetCallback<CCharacterStatus>(EButton_Sound_State::Click, this, &CCharacterStatus::MenuButtonCallback);



	return true;
}

void CCharacterStatus::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	CPlayer* Player = (CPlayer*)m_Scene->GetPlayer();

	m_HP = Player->GetHP();
	m_HPMax = Player->GetHPMax();

	m_HPMaxNumber->SetNumber(m_HPMax);
	m_HPNumber->SetNumber(m_HP);
	m_HPBar->SetValue(m_HP / (float)m_HPMax);


	m_MP = Player->GetMP();
	m_MPMax = Player->GetMPMax();

	m_MPMaxNumber->SetNumber(m_MPMax);
	m_MPNumber->SetNumber(m_MP);
	m_MPBar->SetValue(m_MP / (float)m_MPMax);


	m_Level = Player->GetLevel();
	m_LvNumber->SetNumber(m_Level);


	m_EXP = Player->GetEXP();
	int PlayerEXPMax = Player->GetEXPMax();

	float PlayerEXPPercent = 100 * m_EXP / (float)PlayerEXPMax;

	int PlayerEXPLeft = (int)PlayerEXPPercent;
	int PlayerEXPRight = (int)((PlayerEXPPercent - PlayerEXPLeft) * 100);

	m_EXPNumber->SetNumber(m_EXP);

	m_EXPLeft->SetNumber(PlayerEXPLeft);
	m_EXPRight->SetNumber(PlayerEXPRight);

	m_EXPBar->SetValue(m_EXP / (float)PlayerEXPMax);
}

void CCharacterStatus::CashShopButtonCallback()
{
}

void CCharacterStatus::EventButtonCallback()
{
	CEventMenu* Menu = m_Scene->FindWidgetWindow<CEventMenu>("EventMenu");

	if (Menu)
	{
		if (!Menu->GetEnable())
			Menu->SetEnable(true);

		else
			Menu->SetEnable(false);
	}
}

void CCharacterStatus::CharacterButtonCallback()
{
	CCharacterMenu* Menu = m_Scene->FindWidgetWindow<CCharacterMenu>("CharacterMenu");

	if (Menu)
	{
		if (!Menu->GetEnable())
			Menu->SetEnable(true);

		else
			Menu->SetEnable(false);
	}
}

void CCharacterStatus::CommunityButtonCallback()
{
	CCommunityMenu* Menu = m_Scene->FindWidgetWindow<CCommunityMenu>("CommunityMenu");

	if (Menu)
	{
		if (!Menu->GetEnable())
			Menu->SetEnable(true);

		else
			Menu->SetEnable(false);
	}
}

void CCharacterStatus::SettingButtonCallback()
{
	CSettingMenu* Menu = m_Scene->FindWidgetWindow<CSettingMenu>("SettingMenu");

	if (Menu)
	{
		if (!Menu->GetEnable())
			Menu->SetEnable(true);

		else
			Menu->SetEnable(false);
	}
}

void CCharacterStatus::MenuButtonCallback()
{
	CSubMenu* Menu = m_Scene->FindWidgetWindow<CSubMenu>("SubMenu");

	if (Menu)
	{
		if (!Menu->GetEnable())
			Menu->SetEnable(true);

		else
			Menu->SetEnable(false);
	}
}
