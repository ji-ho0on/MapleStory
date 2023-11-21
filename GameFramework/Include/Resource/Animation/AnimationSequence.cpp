
#include "AnimationSequence.h"

CAnimationSequence::CAnimationSequence()
{
}

CAnimationSequence::~CAnimationSequence()
{
}

void CAnimationSequence::AddFrame(const Vector2& Start, const Vector2& End)
{
	AnimationFrameData	Data = {};

	Data.Start = Start;
	Data.End = End;

	// ���� �Ǻ��� �������� ������ ���� ���ܸ� ���� -1.f, -1.f�� �����Ѵ�.
	Data.Pivot = Vector2(-1.f, -1.f);

	m_vecFrame.push_back(Data);
}

void CAnimationSequence::AddFrame(const Vector2& Start, const Vector2& End, const Vector2& Pivot)
{
	AnimationFrameData	Data = {};

	Data.Start = Start;
	Data.End = End;
	Data.Pivot = Pivot;

	m_vecFrame.push_back(Data);
}

void CAnimationSequence::AddFrame(float PosX, float PosY, float SizeX, float SizeY)
{
	AnimationFrameData	Data = {};

	Data.Start = Vector2(PosX, PosY);
	Data.End = Vector2(PosX + SizeX, PosY + SizeY);

	// ���� �Ǻ��� �������� ������ ���� ���ܸ� ���� -1.f, -1.f�� �����Ѵ�.
	Data.Pivot = Vector2(-1.f, -1.f);

	m_vecFrame.push_back(Data);
}

void CAnimationSequence::AddFrame(float PosX, float PosY, float SizeX, float SizeY, float PivotX, float PivotY)
{
	AnimationFrameData	Data = {};

	Data.Start = Vector2(PosX, PosY);
	Data.End = Vector2(PosX + SizeX, PosY + SizeY);
	Data.Pivot = Vector2(PivotX, PivotY);

	m_vecFrame.push_back(Data);
}
