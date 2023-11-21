

#include "StartWindow.h"
#include "Button.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../GameManager.h"
#include "../Scene/TheSeed2F.h"
//#include "../Scene/TheSeed7F.h"
//#include "../Scene/TheSeed50F.h"
#include "../Scene/EditScene.h"
#include "../Scene/SceneManager.h"
#include "../Input.h"
#include "ImageWidget.h"
#include "Text.h"
#include "Number.h"
#include "../GameManager.h"

CStartWindow::CStartWindow()
{
}

CStartWindow::~CStartWindow()
{
}

bool CStartWindow::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	m_Scene->GetSceneResource()->LoadSound("UI", "ButtonHovered", false, "1Up.wav");
	m_Scene->GetSceneResource()->LoadSound("UI", "ButtonClick", false, "Stun.wav");

	SetSize(1280.f, 768.f);

	m_LoginBack = CreateWidget<CImageWidget>("Background");
	m_LoginBack->SetTexture("Background", TEXT("MapleStory/UI/Login/Background.bmp"));
	m_LoginBack->SetColorKey(255, 0, 255);
	m_LoginBack->SetSize(1280.f, 768.f);
	m_LoginBack->SetPos(0.f, 0.f);
	m_LoginBack->SetZOrder(0);

	m_LoginImage = CreateWidget<CImageWidget>("LoginImage");
	m_LoginImage->SetTexture("LoginImage", TEXT("MapleStory/UI/Login/LoginImage.bmp"));
	m_LoginImage->SetSize(1024.f, 768.f);
	m_LoginImage->SetPos(128.f, 0.f);
	m_LoginImage->SetZOrder(1);

	m_LoginButton = CreateWidget<CButton>("LoginButton");
	m_LoginButton->SetTexture("LoginButton", TEXT("MapleStory/UI/Login/Title_new_BtLogin.bmp"));
	m_LoginButton->SetColorKey(255, 0, 255);
	m_LoginButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(278.f, 53.f));
	m_LoginButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(278.f, 0.f), Vector2(556.f, 53.f));
	m_LoginButton->SetButtonStateData(EButton_State::Click, Vector2(556.f, 0.f), Vector2(834.f, 53.f));
	m_LoginButton->SetButtonStateData(EButton_State::Disable, Vector2(834.f, 0.f), Vector2(1112.f, 53.f));
	m_LoginButton->SetPos(501.f, 414.f);
	m_LoginButton->SetZOrder(2);

	m_LoginButton->SetCallback<CStartWindow>(EButton_Sound_State::Click, this, &CStartWindow::StartButtonCallback);


	m_ExitButton = CreateWidget<CButton>("ExitButton");
	m_ExitButton->SetTexture("ExitButton", TEXT("MapleStory/UI/Login/ExitButton_1.bmp"));
	m_ExitButton->SetColorKey(255, 0, 255);
	m_ExitButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(44.f, 21.f));
	m_ExitButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(44.f, 21.f));
	m_ExitButton->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(44.f, 21.f));
	m_ExitButton->SetButtonStateData(EButton_State::Disable, Vector2(0.f, 0.f), Vector2(44.f, 21.f));
	m_ExitButton->SetPos(740.f, 474.f);
	m_ExitButton->SetZOrder(2);

	m_ExitButton->SetCallback<CStartWindow>(EButton_Sound_State::Click, this, &CStartWindow::EndButtonCallback);



	//m_EditButton = CreateWidget<CButton>("EditButton");

	//m_EditButton->SetTexture("EditButton", TEXT("EditButton.bmp"));
	//m_EditButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(200.f, 100.f));
	//m_EditButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(200.f, 0.f), Vector2(400.f, 100.f));
	//m_EditButton->SetButtonStateData(EButton_State::Click, Vector2(400.f, 0.f), Vector2(600.f, 100.f));
	//m_EditButton->SetButtonStateData(EButton_State::Disable, Vector2(600.f, 0.f), Vector2(800.f, 100.f));

	//m_EditButton->SetSound(EButton_Sound_State::MouseHovered, "ButtonHovered");
	//m_EditButton->SetSound(EButton_Sound_State::Click, "ButtonClick");

	//m_EditButton->SetPos(900.f, 620.f);
	//m_EditButton->SetZOrder(2);

	//m_EditButton->SetCallback<CStartWindow>(EButton_Sound_State::Click,	this, &CStartWindow::EditButtonCallback);

	m_LoginIDText = CreateWidget<CText>("LoginIDText");

	m_LoginIDText->SetText(TEXT(""));
	m_LoginIDText->SetPos(508.f, 325.f);
	m_LoginIDText->SetTextColor(0, 0, 0);

	m_LoginIDText->EnableShadow(true);
	m_LoginIDText->SetShadowOffset(1.f, 1.f);
	m_LoginIDText->SetZOrder(3);

	m_IDTextTime = 0.f;

	memset(m_LoginIDAddText, 0, sizeof(TCHAR) * 32);
	lstrcpy(m_LoginIDAddText, TEXT("√÷¡ˆ»∆"));
	m_IDAddCount = 0;

	m_LoginPWText = CreateWidget<CText>("LoginPWText");

	m_LoginPWText->SetText(TEXT(""));
	m_LoginPWText->SetPos(508.f, 370.f);
	m_LoginPWText->SetTextColor(0, 0, 0);

	m_LoginPWText->EnableShadow(true);
	m_LoginPWText->SetShadowOffset(1.f, 1.f);
	m_LoginPWText->SetZOrder(3);

	m_PWTextTime = 0.f;

	memset(m_LoginPWAddText, 0, sizeof(TCHAR) * 32);
	lstrcpy(m_LoginPWAddText, TEXT("PASSWORD"));
	m_PWAddCount = 0;

	return true;
}

void CStartWindow::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	if (m_IDAddCount < lstrlen(m_LoginIDAddText))
	{
		m_IDTextTime += DeltaTime;

		if (m_IDTextTime >= 0.5f)
		{
			m_IDTextTime -= 0.5f;

			m_LoginIDText->AddText(m_LoginIDAddText[m_IDAddCount]);

			++m_IDAddCount;
		}
	}


	if (m_PWAddCount < lstrlen(m_LoginPWAddText))
	{
		m_PWTextTime += DeltaTime;

		if (m_PWTextTime >= 0.2f)
		{
			m_PWTextTime -= 0.2f;

			m_LoginPWText->AddText(m_LoginPWAddText[m_PWAddCount]);

			++m_PWAddCount;
		}
	}
}

void CStartWindow::StartButtonCallback()
{
	CInput::GetInst()->ClearCallback();
	CSceneManager::GetInst()->CreateScene<CTheSeed2F>();
}

void CStartWindow::EditButtonCallback()
{
	CInput::GetInst()->ClearCallback();
	CSceneManager::GetInst()->CreateScene<CEditScene>();
}

void CStartWindow::EndButtonCallback()
{
	CGameManager::GetInst()->Exit();
}
