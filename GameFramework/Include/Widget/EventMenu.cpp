#include "EventMenu.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "ImageWidget.h"
#include "Button.h"

CEventMenu::CEventMenu()
{
}

CEventMenu::~CEventMenu()
{
}

bool CEventMenu::Init()
{
	if (!CWidgetWindow::Init())
		return false;


	SetSize(121.f, 99.f);
	SetPos(0.f, 0.f);

	m_EventMenuBackStart = CreateWidget<CImageWidget>("EventMenuBackStart");
	m_EventMenuBackStart->SetTexture("EventMenuBackStart", TEXT("MapleStory/UI/submenu_backgrnd_0.bmp"));
	m_EventMenuBackStart->SetColorKey(255, 0, 255);
	m_EventMenuBackStart->SetSize(121.f, 29.f);
	m_EventMenuBackStart->SetPos(0.f, 0.f);
	m_EventMenuBackStart->SetZOrder(0);


	m_EventMenuBackMiddle = CreateWidget<CImageWidget>("EventMenuBackMiddle");
	m_EventMenuBackMiddle->SetTexture("EventMenuBackMiddle", TEXT("MapleStory/UI/submenu_backgrnd_3.bmp"));
	m_EventMenuBackMiddle->SetColorKey(255, 0, 255);
	m_EventMenuBackMiddle->SetSize(121.f, 26.f);
	m_EventMenuBackMiddle->SetPos(0.f, 29.f);
	m_EventMenuBackMiddle->SetZOrder(0);


	m_EventMenuBackEnd = CreateWidget<CImageWidget>("EventMenuBackEnd");
	m_EventMenuBackEnd->SetTexture("EventMenuBackEnd", TEXT("MapleStory/UI/submenu_backgrnd_2.bmp"));
	m_EventMenuBackEnd->SetColorKey(255, 0, 255);
	m_EventMenuBackEnd->SetSize(121.f, 44.f);
	m_EventMenuBackEnd->SetPos(0.f, 55.f);
	m_EventMenuBackEnd->SetZOrder(0);


	m_EventMenuTitle = CreateWidget<CImageWidget>("EventMenuTitle");
	m_EventMenuTitle->SetTexture("EventMenuTitle", TEXT("MapleStory/UI/submenu_title_event.bmp"));
	m_EventMenuTitle->SetColorKey(255, 0, 255);
	m_EventMenuTitle->SetSize(87.f, 16.f);
	m_EventMenuTitle->SetPos(17.f, 6.f);
	m_EventMenuTitle->SetZOrder(1);


	m_EventListButton = CreateWidget<CButton>("EventListButton");
	m_EventListButton->SetTexture("EventListButton", TEXT("MapleStory/UI/submenu_event_button_schedule.bmp"));
	m_EventListButton->SetColorKey(255, 0, 255);
	m_EventListButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(109.f, 26.f));
	m_EventListButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(109.f, 0.f), Vector2(218.f, 26.f));
	m_EventListButton->SetButtonStateData(EButton_State::Click, Vector2(218.f, 0.f), Vector2(327.f, 26.f));
	m_EventListButton->SetButtonStateData(EButton_State::Disable, Vector2(327.f, 0.f), Vector2(436.f, 26.f));
	m_EventListButton->SetPos(6.f, 29.f);
	m_EventListButton->SetZOrder(2);

	m_DailyGiftButton = CreateWidget<CButton>("DailyGiftButton");
	m_DailyGiftButton->SetTexture("DailyGiftButton", TEXT("MapleStory/UI/submenu_event_button_dailyGift.bmp"));
	m_DailyGiftButton->SetColorKey(255, 0, 255);
	m_DailyGiftButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(109.f, 26.f));
	m_DailyGiftButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(109.f, 0.f), Vector2(218.f, 26.f));
	m_DailyGiftButton->SetButtonStateData(EButton_State::Click, Vector2(218.f, 0.f), Vector2(327.f, 26.f));
	m_DailyGiftButton->SetButtonStateData(EButton_State::Disable, Vector2(327.f, 0.f), Vector2(436.f, 26.f));
	m_DailyGiftButton->SetPos(6.f, 55.f);
	m_DailyGiftButton->SetZOrder(2);


	return true;
}

void CEventMenu::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}
