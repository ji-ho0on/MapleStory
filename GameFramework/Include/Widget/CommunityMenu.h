#pragma once
#include "WidgetWindow.h"
class CCommunityMenu :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CCommunityMenu();
    virtual ~CCommunityMenu();

private:
    CSharedPtr<class CImageWidget>  m_CommunityMenuBackStart;
    CSharedPtr<class CImageWidget>  m_CommunityMenuBackMiddle1;
    CSharedPtr<class CImageWidget>  m_CommunityMenuBackMiddle2;
    CSharedPtr<class CImageWidget>  m_CommunityMenuBackMiddle3;
    CSharedPtr<class CImageWidget>  m_CommunityMenuBackEnd;

    CSharedPtr<class CImageWidget>  m_CommunityMenuTitle;


    CSharedPtr<class CButton>       m_BossButton;
    CSharedPtr<class CButton>       m_PartyButton;
    CSharedPtr<class CButton>       m_FriendButton;
    CSharedPtr<class CButton>       m_GuildButton;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

