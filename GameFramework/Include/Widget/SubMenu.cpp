#include "SubMenu.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "ImageWidget.h"
#include "Button.h"

CSubMenu::CSubMenu()
{
}

CSubMenu::~CSubMenu()
{
}

bool CSubMenu::Init()
{
	if (!CWidgetWindow::Init())
		return false;


	SetSize(121.f, 151.f);
	SetPos(0.f, 0.f);

	m_SubMenuBackStart = CreateWidget<CImageWidget>("SubMenuBackStart");
	m_SubMenuBackStart->SetTexture("SubMenuBackStart", TEXT("MapleStory/UI/submenu_backgrnd_0.bmp"));
	m_SubMenuBackStart->SetColorKey(255, 0, 255);
	m_SubMenuBackStart->SetSize(121.f, 29.f);
	m_SubMenuBackStart->SetPos(0.f, 0.f);
	m_SubMenuBackStart->SetZOrder(0);


	m_SubMenuBackMiddle1 = CreateWidget<CImageWidget>("SubMenuBackMiddle1");
	m_SubMenuBackMiddle1->SetTexture("SubMenuBackMiddle1", TEXT("MapleStory/UI/submenu_backgrnd_3.bmp"));
	m_SubMenuBackMiddle1->SetColorKey(255, 0, 255);
	m_SubMenuBackMiddle1->SetSize(121.f, 26.f);
	m_SubMenuBackMiddle1->SetPos(0.f, 29.f);
	m_SubMenuBackMiddle1->SetZOrder(0);


	m_SubMenuBackMiddle2 = CreateWidget<CImageWidget>("SubMenuBackMiddle2");
	m_SubMenuBackMiddle2->SetTexture("SubMenuBackMiddle2", TEXT("MapleStory/UI/submenu_backgrnd_3.bmp"));
	m_SubMenuBackMiddle2->SetColorKey(255, 0, 255);
	m_SubMenuBackMiddle2->SetSize(121.f, 26.f);
	m_SubMenuBackMiddle2->SetPos(0.f, 55.f);
	m_SubMenuBackMiddle2->SetZOrder(0);


	m_SubMenuBackMiddle3 = CreateWidget<CImageWidget>("SubMenuBackMiddle3");
	m_SubMenuBackMiddle3->SetTexture("SubMenuBackMiddle3", TEXT("MapleStory/UI/submenu_backgrnd_3.bmp"));
	m_SubMenuBackMiddle3->SetColorKey(255, 0, 255);
	m_SubMenuBackMiddle3->SetSize(121.f, 26.f);
	m_SubMenuBackMiddle3->SetPos(0.f, 81.f);
	m_SubMenuBackMiddle3->SetZOrder(0);


	m_SubMenuBackEnd = CreateWidget<CImageWidget>("SubMenuBackEnd");
	m_SubMenuBackEnd->SetTexture("SubMenuBackEnd", TEXT("MapleStory/UI/submenu_backgrnd_2.bmp"));
	m_SubMenuBackEnd->SetColorKey(255, 0, 255);
	m_SubMenuBackEnd->SetSize(121.f, 44.f);
	m_SubMenuBackEnd->SetPos(0.f, 107.f);
	m_SubMenuBackEnd->SetZOrder(0);


	m_SubMenuTitle = CreateWidget<CImageWidget>("SubMenuTitle");
	m_SubMenuTitle->SetTexture("SubMenuTitle", TEXT("MapleStory/UI/submenu_title_menu.bmp"));
	m_SubMenuTitle->SetColorKey(255, 0, 255);
	m_SubMenuTitle->SetSize(87.f, 16.f);
	m_SubMenuTitle->SetPos(17.f, 6.f);
	m_SubMenuTitle->SetZOrder(1);


	m_AuctionButton = CreateWidget<CButton>("AuctionButton");
	m_AuctionButton->SetTexture("AuctionButton", TEXT("MapleStory/UI/submenu_menu_button_auction.bmp"));
	m_AuctionButton->SetColorKey(255, 0, 255);
	m_AuctionButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(109.f, 26.f));
	m_AuctionButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(109.f, 0.f), Vector2(218.f, 26.f));
	m_AuctionButton->SetButtonStateData(EButton_State::Click, Vector2(218.f, 0.f), Vector2(327.f, 26.f));
	m_AuctionButton->SetButtonStateData(EButton_State::Disable, Vector2(327.f, 0.f), Vector2(436.f, 26.f));
	m_AuctionButton->SetPos(6.f, 29.f);
	m_AuctionButton->SetZOrder(2);


	m_MonsterCollectionButton = CreateWidget<CButton>("MonsterCollectionButton");
	m_MonsterCollectionButton->SetTexture("MonsterCollectionButton", TEXT("MapleStory/UI/submenu_menu_button_monsterCollection.bmp"));
	m_MonsterCollectionButton->SetColorKey(255, 0, 255);
	m_MonsterCollectionButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(109.f, 26.f));
	m_MonsterCollectionButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(109.f, 0.f), Vector2(218.f, 26.f));
	m_MonsterCollectionButton->SetButtonStateData(EButton_State::Click, Vector2(218.f, 0.f), Vector2(327.f, 26.f));
	m_MonsterCollectionButton->SetButtonStateData(EButton_State::Disable, Vector2(327.f, 0.f), Vector2(436.f, 26.f));
	m_MonsterCollectionButton->SetPos(6.f, 55.f);
	m_MonsterCollectionButton->SetZOrder(2);


	m_QuestButton = CreateWidget<CButton>("QuestButton");
	m_QuestButton->SetTexture("QuestButton", TEXT("MapleStory/UI/submenu_menu_button_quest.bmp"));
	m_QuestButton->SetColorKey(255, 0, 255);
	m_QuestButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(109.f, 26.f));
	m_QuestButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(109.f, 0.f), Vector2(218.f, 26.f));
	m_QuestButton->SetButtonStateData(EButton_State::Click, Vector2(218.f, 0.f), Vector2(327.f, 26.f));
	m_QuestButton->SetButtonStateData(EButton_State::Disable, Vector2(327.f, 0.f), Vector2(436.f, 26.f));
	m_QuestButton->SetPos(6.f, 81.f);
	m_QuestButton->SetZOrder(2);


	m_UnionButton = CreateWidget<CButton>("UnionButton");
	m_UnionButton->SetTexture("UnionButton", TEXT("MapleStory/UI/submenu_menu_button_union.bmp"));
	m_UnionButton->SetColorKey(255, 0, 255);
	m_UnionButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(109.f, 26.f));
	m_UnionButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(109.f, 0.f), Vector2(218.f, 26.f));
	m_UnionButton->SetButtonStateData(EButton_State::Click, Vector2(218.f, 0.f), Vector2(327.f, 26.f));
	m_UnionButton->SetButtonStateData(EButton_State::Disable, Vector2(327.f, 0.f), Vector2(436.f, 26.f));
	m_UnionButton->SetPos(6.f, 107.f);
	m_UnionButton->SetZOrder(2);


	return true;
}

void CSubMenu::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}
