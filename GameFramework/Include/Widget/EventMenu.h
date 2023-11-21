#pragma once

#include "WidgetWindow.h"

class CEventMenu :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CEventMenu();
    virtual ~CEventMenu();

private:
    CSharedPtr<class CImageWidget>  m_EventMenuBackStart;
    CSharedPtr<class CImageWidget>  m_EventMenuBackMiddle;
    CSharedPtr<class CImageWidget>  m_EventMenuBackEnd;

    CSharedPtr<class CImageWidget>  m_EventMenuTitle;


    CSharedPtr<class CButton>       m_EventListButton;
    CSharedPtr<class CButton>       m_DailyGiftButton;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

