#pragma once

#include "GameObject.h"

class CSealBreakCard :
    public CGameObject
{
	friend class CScene;

protected:
	CSealBreakCard();
	CSealBreakCard(const CSealBreakCard& Obj);
	virtual ~CSealBreakCard();

private:
	bool	m_PickUpState;
	class CPlayer* m_ItemOwner;

public:
	bool GetPickUpState()	const
	{
		return m_PickUpState;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};

