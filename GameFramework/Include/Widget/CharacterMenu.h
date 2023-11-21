#pragma once

#include "WidgetWindow.h"

class CCharacterMenu :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CCharacterMenu();
    virtual ~CCharacterMenu();

private:
    CSharedPtr<class CImageWidget>  m_CharacterMenuBackStart;
    CSharedPtr<class CImageWidget>  m_CharacterMenuBackMiddle1;
    CSharedPtr<class CImageWidget>  m_CharacterMenuBackMiddle2;
    CSharedPtr<class CImageWidget>  m_CharacterMenuBackMiddle3;
    CSharedPtr<class CImageWidget>  m_CharacterMenuBackMiddle4;
    CSharedPtr<class CImageWidget>  m_CharacterMenuBackEnd;

    CSharedPtr<class CImageWidget>  m_CharacterMenuTitle;


    CSharedPtr<class CButton>       m_InfoButton;
    CSharedPtr<class CButton>       m_StatButton;
    CSharedPtr<class CButton>       m_EquipButton;
    CSharedPtr<class CButton>       m_InventoryButton;
    CSharedPtr<class CButton>       m_SkillButton;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

