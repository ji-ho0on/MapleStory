
#include "Scene.h"
#include "SceneResource.h"
#include "Camera.h"
#include "SceneCollision.h"
#include "../GameObject/TileMap.h"
#include "../Widget/EventMenu.h"
#include "../Widget/CharacterMenu.h"
#include "../Widget/CommunityMenu.h"
#include "../Widget/SettingMenu.h"
#include "../Widget/SubMenu.h"

CScene::CScene()
{
	m_Resource = new CSceneResource;
	m_Camera = new CCamera;
	m_Collision = new CSceneCollision;
}

CScene::~CScene()
{
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		m_ObjList[i].clear();
	}

	SAFE_DELETE(m_Collision);
	SAFE_DELETE(m_Camera);
	SAFE_DELETE(m_Resource);
}

void CScene::SetTileMap(CTileMap* TileMap)
{
	m_TileMap = TileMap;
}

void CScene::SetPlayer(CGameObject* Player)
{
	m_Player = Player;
}

void CScene::SetCharacterStatus(CWidgetWindow* CharacterStatus)
{
	m_CharacterStatus = CharacterStatus;
}

bool CScene::Init()
{
	m_EventMenu = CreateWidgetWindow<CEventMenu>("EventMenu");
	m_EventMenu->SetPos(710.f, 578.f);
	m_EventMenu->SetEnable(false);
	m_EventMenu->SetZOrder(1);


	m_CharacterMenu = CreateWidgetWindow<CCharacterMenu>("CharacterMenu");
	m_CharacterMenu->SetPos(745.f, 500.f);
	m_CharacterMenu->SetEnable(false);
	m_CharacterMenu->SetZOrder(1);


	m_CommunityMenu = CreateWidgetWindow<CCommunityMenu>("CommunityMenu");
	m_CommunityMenu->SetPos(780.f, 526.f);
	m_CommunityMenu->SetEnable(false);
	m_CommunityMenu->SetZOrder(1);


	m_SettingMenu = CreateWidgetWindow<CSettingMenu>("SettingMenu");
	m_SettingMenu->SetPos(815.f, 552.f);
	m_SettingMenu->SetEnable(false);
	m_SettingMenu->SetZOrder(1);


	m_SubMenu = CreateWidgetWindow<CSubMenu>("SubMenu");
	m_SubMenu->SetPos(850.f, 526.f);
	m_SubMenu->SetEnable(false);
	m_SubMenu->SetZOrder(1);

	return true;
}

void CScene::Update(float DeltaTime)
{
	// �̷��� �� �����ϼ��� ����....
	// std::list<CSharedPtr<class CGameObject>>::iterator

	// auto : ����� ���ÿ� ������ ������ ���־�� �Ѵ�.
	// ���Ե� Ÿ������ Ÿ���� ����ȴ�.
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		auto	iter = m_ObjList[i].begin();
		auto	iterEnd = m_ObjList[i].end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->m_Start)
			{
				(*iter)->Start();
			}

			if (!(*iter)->GetActive())
			{
				// ����Ʈ���� �����ϴ� ���� SharedPtr�� �Ҹ��ڰ� ȣ��Ǿ�
				// ī��Ʈ�� �����Ѵ�.
				iter = m_ObjList[i].erase(iter);
				iterEnd = m_ObjList[i].end();
				continue;
			}

			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Update(DeltaTime);

			++iter;
		}
	}

	auto	iter1 = m_vecWidgetWindow.begin();
	auto	iter1End = m_vecWidgetWindow.end();

	for (; iter1 != iter1End;)
	{
		if (!(*iter1)->GetActive())
		{
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}

		else if (!(*iter1)->GetEnable())
		{
			++iter1;
			continue;
		}

		(*iter1)->Update(DeltaTime);
		++iter1;
	}

	m_Camera->Update(DeltaTime);
}

void CScene::PostUpdate(float DeltaTime)
{
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		auto	iter = m_ObjList[i].begin();
		auto	iterEnd = m_ObjList[i].end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->m_Start)
			{
				(*iter)->Start();
			}

			if (!(*iter)->GetActive())
			{
				// ����Ʈ���� �����ϴ� ���� SharedPtr�� �Ҹ��ڰ� ȣ��Ǿ�
				// ī��Ʈ�� �����Ѵ�.
				iter = m_ObjList[i].erase(iter);
				iterEnd = m_ObjList[i].end();
				continue;
			}

			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}

			(*iter)->PostUpdate(DeltaTime);

			++iter;
		}
	}

	auto	iter1 = m_vecWidgetWindow.begin();
	auto	iter1End = m_vecWidgetWindow.end();

	for (; iter1 != iter1End;)
	{
		if (!(*iter1)->GetActive())
		{
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}

		else if (!(*iter1)->GetEnable())
		{
			++iter1;
			continue;
		}

		(*iter1)->PostUpdate(DeltaTime);
		++iter1;
	}

	iter1 = m_vecWidgetWindow.begin();
	iter1End = m_vecWidgetWindow.end();

	for (; iter1 != iter1End;)
	{
		if (!(*iter1)->GetActive())
		{
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}

		else if (!(*iter1)->GetEnable())
		{
			++iter1;
			continue;
		}

		m_Collision->AddWidgetWindow(*iter1);
		++iter1;
	}

	m_Collision->CollisionMouse(DeltaTime);

	m_Collision->Collision(DeltaTime);
}

void CScene::Render(HDC hDC, float DeltaTime)
{
	// ��� ����� �����Ѵ�. (Y����)
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		m_ObjList[i].sort(SortY);

		auto	iter = m_ObjList[i].begin();
		auto	iterEnd = m_ObjList[i].end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->m_Start)
			{
				(*iter)->Start();
			}

			if (!(*iter)->GetActive())
			{
				// ����Ʈ���� �����ϴ� ���� SharedPtr�� �Ҹ��ڰ� ȣ��Ǿ�
				// ī��Ʈ�� �����Ѵ�.
				iter = m_ObjList[i].erase(iter);
				iterEnd = m_ObjList[i].end();
				continue;
			}

			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Render(hDC, DeltaTime);

			++iter;
		}
	}

	// WidgetComponent ���
	// ���ŵ� ���� ������Ʈ�� �����Ѵ�.
	{
		auto	iter = m_WidgetComponentList.begin();
		auto	iterEnd = m_WidgetComponentList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				iter = m_WidgetComponentList.erase(iter);
				iterEnd = m_WidgetComponentList.end();
				continue;
			}

			++iter;
		}

		// �����Ѵ�.
		m_WidgetComponentList.sort(SortYWidgetComponent);

		iter = m_WidgetComponentList.begin();
		iterEnd = m_WidgetComponentList.end();

		for (; iter != iterEnd; ++iter)
		{
			if (!(*iter)->GetEnable())
			{
				continue;
			}

			(*iter)->Render(hDC, DeltaTime);
		}
	}

	// ��������� ��ü�� ��µ� ���Ŀ� UI�� ����Ѵ�.
	if (m_vecWidgetWindow.size() > 1)
		std::sort(m_vecWidgetWindow.begin(), m_vecWidgetWindow.end(), CScene::SortWidget);

	auto	iter1 = m_vecWidgetWindow.begin();
	auto	iter1End = m_vecWidgetWindow.end();

	for (; iter1 != iter1End;)
	{
		if (!(*iter1)->GetActive())
		{
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}

		else if (!(*iter1)->GetEnable())
		{
			++iter1;
			continue;
		}

		(*iter1)->Render(hDC, DeltaTime);
		++iter1;
	}



	// UI�� ����� ���Ŀ� ���콺�� ����Ѵ�.
}

bool CScene::SortY(const CSharedPtr<CGameObject>& Src, const CSharedPtr<CGameObject>& Dest)
{
	// �߹� �������� ������ �����ؾ� �ϱ� ������ �߹��� Y�� �����ش�.
	float	SrcY = Src->GetPos().y + (1.f - Src->GetPivot().y) * Src->GetSize().y;
	float	DestY = Dest->GetPos().y + (1.f - Dest->GetPivot().y) * Dest->GetSize().y;

	return SrcY < DestY;
}

bool CScene::SortYWidgetComponent(
	const CSharedPtr<class CWidgetComponent>& Src,
	const CSharedPtr<class CWidgetComponent>& Dest)
{
	return Src->GetBottom() < Dest->GetBottom();
}

bool CScene::SortWidget(const CSharedPtr<CWidgetWindow>& Src, const CSharedPtr<CWidgetWindow>& Dest)
{
	return Src->GetZOrder() < Dest->GetZOrder();
}
