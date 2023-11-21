#include "DorothyHP.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "ProgressBar.h"
#include "ImageWidget.h"
#include "../GameObject/Dorothy.h"
#include "../Scene/TheSeed50F.h"

CDorothyHP::CDorothyHP()
{
}

CDorothyHP::~CDorothyHP()
{
}

bool CDorothyHP::Init()
{
	if (!CWidgetWindow::Init())
		return false;


	SetSize(800.f, 37.f);
	SetPos(240.f, 0.f);


	m_DorothyHPBack = CreateWidget<CImageWidget>("HPBack");
	m_DorothyHPBack->SetTexture("HPBack", TEXT("MapleStory/UI/boss_hp_backgrnd.bmp"));
	m_DorothyHPBack->SetColorKey(255, 0, 255);
	m_DorothyHPBack->SetSize(800.f, 37.f);
	m_DorothyHPBack->SetPos(0.f, 0.f);
	m_DorothyHPBack->SetZOrder(0);


	m_DorothyHPIcon = CreateWidget<CImageWidget>("HPIcon");
	m_DorothyHPIcon->SetTexture("HPIcon", TEXT("MapleStory/UI/boss_hp_icon.bmp"));
	m_DorothyHPIcon->SetColorKey(255, 0, 255);
	m_DorothyHPIcon->SetSize(33.f, 33.f);
	m_DorothyHPIcon->SetPos(2.f, 2.f);
	m_DorothyHPIcon->SetZOrder(1);


	m_DorothyHPBar = CreateWidget<CProgressBar>("DorothyHPBar");
	m_DorothyHPBar->SetTexture(EProgressBar_Texture_Type::Bar, "DorothyHPBar", TEXT("MapleStory/UI/boss_hp_gauge.bmp"));
	m_DorothyHPBar->SetSize(758.f, 10.f);
	m_DorothyHPBar->SetPos(39.f, 6.f);
	m_DorothyHPBar->SetBarDir(EProgressBar_Dir::LeftToRight);
	m_DorothyHPBar->SetZOrder(1);

	return true;
}

void CDorothyHP::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	CTheSeed50F* Scene = (CTheSeed50F*)m_Scene;

	if (Scene)
	{
		CDorothy* Dorothy = Scene->GetDorothy();

		if (Dorothy)
		{
			int DorothyHP = Dorothy->GetHP();
			int DorothyHPMax = Dorothy->GetMaxHP();

			m_DorothyHPBar->SetValue(DorothyHP / (float)DorothyHPMax);
		}
	}
}
