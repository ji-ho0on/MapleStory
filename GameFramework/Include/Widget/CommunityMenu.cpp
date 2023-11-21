#include "CommunityMenu.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "ImageWidget.h"
#include "Button.h"

CCommunityMenu::CCommunityMenu()
{
}

CCommunityMenu::~CCommunityMenu()
{
}

bool CCommunityMenu::Init()
{
	if (!CWidgetWindow::Init())
		return false;


	SetSize(121.f, 151.f);
	SetPos(0.f, 0.f);

	m_CommunityMenuBackStart = CreateWidget<CImageWidget>("CommunityMenuBackStart");
	m_CommunityMenuBackStart->SetTexture("CommunityMenuBackStart", TEXT("MapleStory/UI/submenu_backgrnd_0.bmp"));
	m_CommunityMenuBackStart->SetColorKey(255, 0, 255);
	m_CommunityMenuBackStart->SetSize(121.f, 29.f);
	m_CommunityMenuBackStart->SetPos(0.f, 0.f);
	m_CommunityMenuBackStart->SetZOrder(0);


	m_CommunityMenuBackMiddle1 = CreateWidget<CImageWidget>("CommunityMenuBackMiddle1");
	m_CommunityMenuBackMiddle1->SetTexture("CommunityMenuBackMiddle1", TEXT("MapleStory/UI/submenu_backgrnd_3.bmp"));
	m_CommunityMenuBackMiddle1->SetColorKey(255, 0, 255);
	m_CommunityMenuBackMiddle1->SetSize(121.f, 26.f);
	m_CommunityMenuBackMiddle1->SetPos(0.f, 29.f);
	m_CommunityMenuBackMiddle1->SetZOrder(0);


	m_CommunityMenuBackMiddle2 = CreateWidget<CImageWidget>("CommunityMenuBackMiddle2");
	m_CommunityMenuBackMiddle2->SetTexture("CommunityMenuBackMiddle2", TEXT("MapleStory/UI/submenu_backgrnd_3.bmp"));
	m_CommunityMenuBackMiddle2->SetColorKey(255, 0, 255);
	m_CommunityMenuBackMiddle2->SetSize(121.f, 26.f);
	m_CommunityMenuBackMiddle2->SetPos(0.f, 55.f);
	m_CommunityMenuBackMiddle2->SetZOrder(0);


	m_CommunityMenuBackMiddle3 = CreateWidget<CImageWidget>("CommunityMenuBackMiddle3");
	m_CommunityMenuBackMiddle3->SetTexture("CommunityMenuBackMiddle3", TEXT("MapleStory/UI/submenu_backgrnd_3.bmp"));
	m_CommunityMenuBackMiddle3->SetColorKey(255, 0, 255);
	m_CommunityMenuBackMiddle3->SetSize(121.f, 26.f);
	m_CommunityMenuBackMiddle3->SetPos(0.f, 81.f);
	m_CommunityMenuBackMiddle3->SetZOrder(0);


	m_CommunityMenuBackEnd = CreateWidget<CImageWidget>("CommunityMenuBackEnd");
	m_CommunityMenuBackEnd->SetTexture("CommunityMenuBackEnd", TEXT("MapleStory/UI/submenu_backgrnd_2.bmp"));
	m_CommunityMenuBackEnd->SetColorKey(255, 0, 255);
	m_CommunityMenuBackEnd->SetSize(121.f, 44.f);
	m_CommunityMenuBackEnd->SetPos(0.f, 107.f);
	m_CommunityMenuBackEnd->SetZOrder(0);


	m_CommunityMenuTitle = CreateWidget<CImageWidget>("CommunityMenuTitle");
	m_CommunityMenuTitle->SetTexture("CommunityMenuTitle", TEXT("MapleStory/UI/submenu_title_community.bmp"));
	m_CommunityMenuTitle->SetColorKey(255, 0, 255);
	m_CommunityMenuTitle->SetSize(87.f, 16.f);
	m_CommunityMenuTitle->SetPos(17.f, 6.f);
	m_CommunityMenuTitle->SetZOrder(1);


	m_BossButton = CreateWidget<CButton>("BossButton");
	m_BossButton->SetTexture("BossButton", TEXT("MapleStory/UI/submenu_community_button_boss.bmp"));
	m_BossButton->SetColorKey(255, 0, 255);
	m_BossButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(109.f, 26.f));
	m_BossButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(109.f, 0.f), Vector2(218.f, 26.f));
	m_BossButton->SetButtonStateData(EButton_State::Click, Vector2(218.f, 0.f), Vector2(327.f, 26.f));
	m_BossButton->SetButtonStateData(EButton_State::Disable, Vector2(327.f, 0.f), Vector2(436.f, 26.f));
	m_BossButton->SetPos(6.f, 29.f);
	m_BossButton->SetZOrder(2);


	m_PartyButton = CreateWidget<CButton>("PartyButton");
	m_PartyButton->SetTexture("PartyButton", TEXT("MapleStory/UI/submenu_community_button_bossParty.bmp"));
	m_PartyButton->SetColorKey(255, 0, 255);
	m_PartyButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(109.f, 26.f));
	m_PartyButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(109.f, 0.f), Vector2(218.f, 26.f));
	m_PartyButton->SetButtonStateData(EButton_State::Click, Vector2(218.f, 0.f), Vector2(327.f, 26.f));
	m_PartyButton->SetButtonStateData(EButton_State::Disable, Vector2(327.f, 0.f), Vector2(436.f, 26.f));
	m_PartyButton->SetPos(6.f, 55.f);
	m_PartyButton->SetZOrder(2);


	m_FriendButton = CreateWidget<CButton>("FriendButton");
	m_FriendButton->SetTexture("FriendButton", TEXT("MapleStory/UI/submenu_community_button_friends.bmp"));
	m_FriendButton->SetColorKey(255, 0, 255);
	m_FriendButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(109.f, 26.f));
	m_FriendButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(109.f, 0.f), Vector2(218.f, 26.f));
	m_FriendButton->SetButtonStateData(EButton_State::Click, Vector2(218.f, 0.f), Vector2(327.f, 26.f));
	m_FriendButton->SetButtonStateData(EButton_State::Disable, Vector2(327.f, 0.f), Vector2(436.f, 26.f));
	m_FriendButton->SetPos(6.f, 81.f);
	m_FriendButton->SetZOrder(2);


	m_GuildButton = CreateWidget<CButton>("GuildButton");
	m_GuildButton->SetTexture("GuildButton", TEXT("MapleStory/UI/submenu_community_button_guild.bmp"));
	m_GuildButton->SetColorKey(255, 0, 255);
	m_GuildButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(109.f, 26.f));
	m_GuildButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(109.f, 0.f), Vector2(218.f, 26.f));
	m_GuildButton->SetButtonStateData(EButton_State::Click, Vector2(218.f, 0.f), Vector2(327.f, 26.f));
	m_GuildButton->SetButtonStateData(EButton_State::Disable, Vector2(327.f, 0.f), Vector2(436.f, 26.f));
	m_GuildButton->SetPos(6.f, 107.f);
	m_GuildButton->SetZOrder(2);


	return true;
}

void CCommunityMenu::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}
