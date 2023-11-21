#pragma once

#include "WidgetWindow.h"

class CSettingMenu :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CSettingMenu();
    virtual ~CSettingMenu();

private:
    CSharedPtr<class CImageWidget>  m_SettingMenuBackStart;
    CSharedPtr<class CImageWidget>  m_SettingMenuBackMiddle1;
    CSharedPtr<class CImageWidget>  m_SettingMenuBackMiddle2;
    CSharedPtr<class CImageWidget>  m_SettingMenuBackEnd;

    CSharedPtr<class CImageWidget>  m_SettingMenuTitle;


    CSharedPtr<class CButton>       m_ChannelButton;
    CSharedPtr<class CButton>       m_OptionButton;
    CSharedPtr<class CButton>       m_GameQuitButton;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    void GameQuitButtonCallBack();
};

