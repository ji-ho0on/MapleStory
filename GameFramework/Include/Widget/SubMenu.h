#pragma once

#include "WidgetWindow.h"

class CSubMenu :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CSubMenu();
    virtual ~CSubMenu();

private:
    CSharedPtr<class CImageWidget>  m_SubMenuBackStart;
    CSharedPtr<class CImageWidget>  m_SubMenuBackMiddle1;
    CSharedPtr<class CImageWidget>  m_SubMenuBackMiddle2;
    CSharedPtr<class CImageWidget>  m_SubMenuBackMiddle3;
    CSharedPtr<class CImageWidget>  m_SubMenuBackEnd;

    CSharedPtr<class CImageWidget>  m_SubMenuTitle;


    CSharedPtr<class CButton>       m_AuctionButton;
    CSharedPtr<class CButton>       m_MonsterCollectionButton;
    CSharedPtr<class CButton>       m_QuestButton;
    CSharedPtr<class CButton>       m_UnionButton;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

