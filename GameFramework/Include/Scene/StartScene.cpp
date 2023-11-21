
#include "StartScene.h"
#include "../GameObject/Player.h"
#include "../GameObject/Monster.h"
#include "../GameObject/BackObj.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "../Widget/StartWindow.h"

CStartScene::CStartScene()
{
}

CStartScene::~CStartScene()
{
}

bool CStartScene::Init()
{
	if (!CScene::Init())
		return false;

	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(1280.f, 720.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	m_StartWindow = CreateWidgetWindow<CStartWindow>("StartWindow");
	m_StartWindow->SetPos(0.f, 0.f);

	// 사운드 설정
	GetSceneResource()->LoadSound("BGM", "MainTitle", true, "MainTitle.mp3");
	GetSceneResource()->SetVolume(20);
	GetSceneResource()->SoundPlay("MainTitle");

	return true;
}
