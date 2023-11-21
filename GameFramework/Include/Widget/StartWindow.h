#pragma once

#include "WidgetWindow.h"

class CStartWindow :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CStartWindow();
    virtual ~CStartWindow();

private:
    CSharedPtr<class CImageWidget>  m_LoginBack;
    CSharedPtr<class CImageWidget>  m_LoginImage;
    CSharedPtr<class CButton>       m_LoginButton;
    CSharedPtr<class CButton>       m_ExitButton;


    CSharedPtr<class CButton>       m_EditButton;


    CSharedPtr<class CText>         m_LoginIDText;
    TCHAR                           m_LoginIDAddText[32];

    float       m_IDTextTime;
    int         m_IDAddCount;

    CSharedPtr<class CText>         m_LoginPWText;
    TCHAR                           m_LoginPWAddText[32];

    float       m_PWTextTime;
    int         m_PWAddCount;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    void StartButtonCallback();
    void EditButtonCallback();
    void EndButtonCallback();
};

