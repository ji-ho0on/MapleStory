
#include "Widget.h"
#include "WidgetWindow.h"
#include "../Input.h"
#include "../GameObject/GameObject.h"

CWidget::CWidget()	:
	m_Scene(nullptr),
	m_Owner(nullptr),
	m_ZOrder(0),
	m_MouseHovered(false)
{
}

CWidget::CWidget(const CWidget& widget)	:
	CRef(widget)
{
	m_ZOrder = widget.m_ZOrder;
	m_MouseHovered = widget.m_MouseHovered;
}

CWidget::~CWidget()
{
}

CWidgetWindow* CWidget::GetOwner()
{
	return m_Owner;
}

bool CWidget::Init()
{
	return true;
}

void CWidget::Update(float DeltaTime)
{
}

void CWidget::PostUpdate(float DeltaTime)
{
}

void CWidget::Render(HDC hDC, float DeltaTime)
{
}

void CWidget::Render(HDC hDC, const Vector2& Pos, float DeltaTime)
{
}

bool CWidget::CollisionMouse(const Vector2& Pos)
{
	Vector2 CollisionPos = m_Pos;

	if (m_Owner)
	{
		CollisionPos = m_Pos + m_Owner->GetPos();
	}

	if (Pos.x < CollisionPos.x)
		return false;

	else if (Pos.x > CollisionPos.x + m_Size.x)
		return false;

	else if (Pos.y < CollisionPos.y)
		return false;

	else if (Pos.y > CollisionPos.y + m_Size.y)
		return false;

	if (!m_MouseHovered)
		CollisionMouseHoveredCallback(Pos);

	return true;
}

void CWidget::CollisionMouseHoveredCallback(const Vector2& Pos)
{
	m_MouseHovered = true;

	CInput::GetInst()->GetMouseObj()->ChangeAnimation("MouseOvered");
}

void CWidget::CollisionMouseReleaseCallback()
{
	m_MouseHovered = false;

	CInput::GetInst()->GetMouseObj()->ChangeAnimation("MouseNormal");
}
