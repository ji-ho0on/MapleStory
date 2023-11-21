#pragma once

#include "Scene.h"

class CStartScene :
    public CScene
{
	friend class CSceneManager;

protected:
	CStartScene();
	virtual ~CStartScene();

private:
	CSharedPtr<class CWidgetWindow>	m_StartWindow;

public:
	bool Init();
};

