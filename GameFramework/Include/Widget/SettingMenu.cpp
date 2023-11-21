#include "SettingMenu.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "ImageWidget.h"
#include "Button.h"
#include "../GameManager.h"

CSettingMenu::CSettingMenu()
{
}

CSettingMenu::~CSettingMenu()
{
}

bool CSettingMenu::Init()
{
	if (!CWidgetWindow::Init())
		return false;


	SetSize(121.f, 125.f);
	SetPos(0.f, 0.f);

	m_SettingMenuBackStart = CreateWidget<CImageWidget>("SettingMenuBackStart");
	m_SettingMenuBackStart->SetTexture("SettingMenuBackStart", TEXT("MapleStory/UI/submenu_backgrnd_0.bmp"));
	m_SettingMenuBackStart->SetColorKey(255, 0, 255);
	m_SettingMenuBackStart->SetSize(121.f, 29.f);
	m_SettingMenuBackStart->SetPos(0.f, 0.f);
	m_SettingMenuBackStart->SetZOrder(0);


	m_SettingMenuBackMiddle1 = CreateWidget<CImageWidget>("SettingMenuBackMiddle1");
	m_SettingMenuBackMiddle1->SetTexture("SettingMenuBackMiddle1", TEXT("MapleStory/UI/submenu_backgrnd_3.bmp"));
	m_SettingMenuBackMiddle1->SetColorKey(255, 0, 255);
	m_SettingMenuBackMiddle1->SetSize(121.f, 26.f);
	m_SettingMenuBackMiddle1->SetPos(0.f, 29.f);
	m_SettingMenuBackMiddle1->SetZOrder(0);


	m_SettingMenuBackMiddle2 = CreateWidget<CImageWidget>("SettingMenuBackMiddle2");
	m_SettingMenuBackMiddle2->SetTexture("SettingMenuBackMiddle2", TEXT("MapleStory/UI/submenu_backgrnd_3.bmp"));
	m_SettingMenuBackMiddle2->SetColorKey(255, 0, 255);
	m_SettingMenuBackMiddle2->SetSize(121.f, 26.f);
	m_SettingMenuBackMiddle2->SetPos(0.f, 55.f);
	m_SettingMenuBackMiddle2->SetZOrder(0);


	m_SettingMenuBackEnd = CreateWidget<CImageWidget>("SettingMenuBackEnd");
	m_SettingMenuBackEnd->SetTexture("SettingMenuBackEnd", TEXT("MapleStory/UI/submenu_backgrnd_2.bmp"));
	m_SettingMenuBackEnd->SetColorKey(255, 0, 255);
	m_SettingMenuBackEnd->SetSize(121.f, 44.f);
	m_SettingMenuBackEnd->SetPos(0.f, 81.f);
	m_SettingMenuBackEnd->SetZOrder(0);


	m_SettingMenuTitle = CreateWidget<CImageWidget>("SettingMenuTitle");
	m_SettingMenuTitle->SetTexture("SettingMenuTitle", TEXT("MapleStory/UI/submenu_title_setting.bmp"));
	m_SettingMenuTitle->SetColorKey(255, 0, 255);
	m_SettingMenuTitle->SetSize(87.f, 16.f);
	m_SettingMenuTitle->SetPos(17.f, 6.f);
	m_SettingMenuTitle->SetZOrder(1);


	m_ChannelButton = CreateWidget<CButton>("ChannelButton");
	m_ChannelButton->SetTexture("ChannelButton", TEXT("MapleStory/UI/submenu_setting_button_channel.bmp"));
	m_ChannelButton->SetColorKey(255, 0, 255);
	m_ChannelButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(109.f, 26.f));
	m_ChannelButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(109.f, 0.f), Vector2(218.f, 26.f));
	m_ChannelButton->SetButtonStateData(EButton_State::Click, Vector2(218.f, 0.f), Vector2(327.f, 26.f));
	m_ChannelButton->SetButtonStateData(EButton_State::Disable, Vector2(327.f, 0.f), Vector2(436.f, 26.f));
	m_ChannelButton->SetPos(6.f, 29.f);
	m_ChannelButton->SetZOrder(2);


	m_OptionButton = CreateWidget<CButton>("OptionButton");
	m_OptionButton->SetTexture("OptionButton", TEXT("MapleStory/UI/submenu_setting_button_option.bmp"));
	m_OptionButton->SetColorKey(255, 0, 255);
	m_OptionButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(109.f, 26.f));
	m_OptionButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(109.f, 0.f), Vector2(218.f, 26.f));
	m_OptionButton->SetButtonStateData(EButton_State::Click, Vector2(218.f, 0.f), Vector2(327.f, 26.f));
	m_OptionButton->SetButtonStateData(EButton_State::Disable, Vector2(327.f, 0.f), Vector2(436.f, 26.f));
	m_OptionButton->SetPos(6.f, 55.f);
	m_OptionButton->SetZOrder(2);


	m_GameQuitButton = CreateWidget<CButton>("GameQuitButton");
	m_GameQuitButton->SetTexture("GameQuitButton", TEXT("MapleStory/UI/submenu_setting_button_GameQuit.bmp"));
	m_GameQuitButton->SetColorKey(255, 0, 255);
	m_GameQuitButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(109.f, 26.f));
	m_GameQuitButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(109.f, 0.f), Vector2(218.f, 26.f));
	m_GameQuitButton->SetButtonStateData(EButton_State::Click, Vector2(218.f, 0.f), Vector2(327.f, 26.f));
	m_GameQuitButton->SetButtonStateData(EButton_State::Disable, Vector2(327.f, 0.f), Vector2(436.f, 26.f));
	m_GameQuitButton->SetPos(6.f, 81.f);
	m_GameQuitButton->SetCallback<CSettingMenu>(EButton_Sound_State::Click, this, &CSettingMenu::GameQuitButtonCallBack);
	m_GameQuitButton->SetZOrder(2);

	return true;
}

void CSettingMenu::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CSettingMenu::GameQuitButtonCallBack()
{
	CGameManager::GetInst()->Exit();
}
