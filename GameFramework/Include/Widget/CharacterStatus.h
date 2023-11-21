#pragma once

#include "WidgetWindow.h"

class CCharacterStatus :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CCharacterStatus();
    virtual ~CCharacterStatus();

protected:

    int		m_HP;
    int		m_HPMax;

    int		m_MP;
    int		m_MPMax;

    int		m_Level;
    int		m_EXP;

    // 경험치
    CSharedPtr<class CImageWidget>  m_EXPBarBack;
    CSharedPtr<class CProgressBar>  m_EXPBar;
    CSharedPtr<class CImageWidget>  m_EXPBarFrame;
    CSharedPtr<class CNumber>       m_EXPNumber;
    CSharedPtr<class CImageWidget>  m_EXPBracketLeft;
    CSharedPtr<class CNumber>       m_EXPLeft;
    CSharedPtr<class CImageWidget>  m_EXPDot;
    CSharedPtr<class CNumber>       m_EXPRight;
    CSharedPtr<class CImageWidget>  m_EXPPercent;
    CSharedPtr<class CImageWidget>  m_EXPBracketRight;

    // HP, MP
    CSharedPtr<class CImageWidget>  m_StatusBarBack;
    CSharedPtr<class CProgressBar>  m_HPBar;
    CSharedPtr<class CProgressBar>  m_MPBar;
    CSharedPtr<class CNumber>       m_HPNumber;
    CSharedPtr<class CImageWidget>  m_HPSlash;
    CSharedPtr<class CNumber>       m_HPMaxNumber;
    CSharedPtr<class CNumber>       m_MPNumber;
    CSharedPtr<class CImageWidget>  m_MPSlash;
    CSharedPtr<class CNumber>       m_MPMaxNumber;

    CSharedPtr<class CImageWidget>  m_StatusBarFrame;

    // 레벨
    CSharedPtr<class CImageWidget>  m_LvImage;
    CSharedPtr<class CNumber>       m_LvNumber;

    // 이름
    CSharedPtr<class CText>         m_CharacterName;

    // 퀵슬롯 이미지
    CSharedPtr<class CImageWidget>  m_QuickSlotBack;
    CSharedPtr<class CImageWidget>  m_QuickSlotFrame;


    // 스킬 아이콘
    CSharedPtr<class CProgressBar>  m_SlashBlustIcon;
    CSharedPtr<class CProgressBar>  m_RaisingBlowIcon;


    // 메뉴버튼
    CSharedPtr<class CButton>       m_CashShopButton;

    CSharedPtr<class CButton>       m_EventButton;

    CSharedPtr<class CButton>       m_CharacterButton;

    CSharedPtr<class CButton>       m_CommunityButton;

    CSharedPtr<class CButton>       m_SettingButton;

    CSharedPtr<class CButton>       m_MenuButton;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    int GetHP()	const
    {
        return m_HP;
    }

    int GetHPMax()	const
    {
        return m_HPMax;
    }

    int GetMP()	const
    {
        return m_MP;
    }

    int GetMPMax()	const
    {
        return m_MPMax;
    }

    int GetEXP()	const
    {
        return m_EXP;
    }

    int GetLevel()	const
    {
        return m_Level;
    }

public:
    void SetHP(int HP)
    {
        m_HP = HP;
    }

    void SetHPMax(int HPMax)
    {
        m_HPMax = HPMax;
    }

    void SetMP(int MP)
    {
        m_MP = MP;
    }

    void SetMPMax(int MPMax)
    {
        m_MPMax = MPMax;
    }

    void SetLevel(int Level)
    {
        m_Level = Level;
    }

    void SetEXP(int EXP)
    {
        m_EXP = EXP;
    }

private:
    void CashShopButtonCallback();
    void EventButtonCallback();
    void CharacterButtonCallback();
    void CommunityButtonCallback();
    void SettingButtonCallback();
    void MenuButtonCallback();
};

