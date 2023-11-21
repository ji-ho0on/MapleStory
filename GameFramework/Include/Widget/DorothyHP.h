#pragma once

#include "WidgetWindow.h"

class CDorothyHP :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CDorothyHP();
    virtual ~CDorothyHP();

private:
    CSharedPtr<class CImageWidget>  m_DorothyHPBack;
    CSharedPtr<class CImageWidget>  m_DorothyHPIcon;
    CSharedPtr<class CProgressBar>  m_DorothyHPBar;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

