
#include "Camera.h"
#include "../Input.h"

CCamera::CCamera() :
	m_FollowTime(0.3f),
	m_ProportionalConst(0.f),
	m_FollowAccTime(0.3f),
	m_PrevLookPos(Vector2(-1.f, -1.f))
{
}

CCamera::~CCamera()
{
}

void CCamera::CalculateDiff(float DeltaTime)
{
	if (m_PrevLookPos == Vector2(-1.f, -1.f))
	{
		m_PrevLookPos = m_LookPos;
	}

	if (m_FollowAccTime >= m_FollowTime)
	{
		m_Pos = m_LookPos;
	}

	else
	{
		m_FollowAccTime += DeltaTime;

		float DeltaSpeed = m_ProportionalConst * (m_FollowAccTime - m_FollowTime);
		Vector2	LookDirNorm = (m_LookPos - m_PrevLookPos) / m_LookPos.Distance(m_PrevLookPos);
		m_Pos = m_PrevLookPos + LookDirNorm * DeltaSpeed * DeltaTime;
	}

	m_PrevLookPos = m_Pos;
}

void CCamera::Update(float DeltaTime)
{
	//if (m_Target)
	//{
	//	if (!m_Target->GetActive())
	//		m_Target = nullptr;

	//	else
	//		m_Pos = m_Target->GetPos() - m_TargetPivot * m_Resolution + m_TargetOffset;
	//}

	if (m_Target)
	{
		if (!m_Target->GetActive())
			m_Target = nullptr;

		else
		{
			m_LookPos = m_Target->GetPos() - m_TargetPivot * m_Resolution + m_TargetOffset;

			float Length = m_LookPos.Distance(m_PrevLookPos);

			if (Length >= 5.f)
			{
				SetLookPosition(Length);
			}

			CalculateDiff(DeltaTime);
		}
	}

	// 카메라가 월드를 벗어나지 못하도록 만들어준다.
	if (m_Pos.x < 0.f)
		m_Pos.x = 0.f;

	else if (m_Pos.x + m_Resolution.x > m_WorldResolution.x)
		m_Pos.x = m_WorldResolution.x - m_Resolution.x;

	if (m_Pos.y < 0.f)
		m_Pos.y = 0.f;

	else if (m_Pos.y + m_Resolution.y > m_WorldResolution.y)
		m_Pos.y = m_WorldResolution.y - m_Resolution.y;

	CInput::GetInst()->ComputeWorldMousePos(m_Pos);
}
