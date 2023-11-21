#include "Input.h"
#include "Collision/CollisionManager.h"
#include "Resource/ResourceManager.h"
#include "GameObject/GameObject.h"

DEFINITION_SINGLE(CInput)

CInput::CInput()	:
	m_MouseLDown(false),
	m_MouseLPush(false),
	m_MouseLUp(false),
	m_MouseObj(nullptr)
{
}

CInput::~CInput()
{
	{
		auto	iter = m_mapKeyState.begin();
		auto	iterEnd = m_mapKeyState.end();

		for (; iter != iterEnd; ++iter)
		{
			SAFE_DELETE(iter->second);
		}

		m_mapKeyState.clear();
	}

	{
		auto	iter = m_mapBindKey.begin();
		auto	iterEnd = m_mapBindKey.end();

		for (; iter != iterEnd; ++iter)
		{
			for (int i = 0; i < (int)Input_Type::End; ++i)
			{
				size_t	Size = iter->second->vecFunction[i].size();

				for (size_t j = 0; j < Size; ++j)
				{
					SAFE_DELETE(iter->second->vecFunction[i][j]);
				}
			}

			SAFE_DELETE(iter->second);
		}

		m_mapBindKey.clear();
	}
}

CGameObject* CInput::GetMouseObj()
{
	return m_MouseObj.Get();
}

void CInput::ComputeWorldMousePos(const Vector2& CameraPos)
{
	m_MouseWorldPos = m_MousePos + CameraPos;
}

bool CInput::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	AddBindKey("D", 'D');
	AddBindKey("A", 'A');
	AddBindKey("W", 'W');
	AddBindKey("S", 'S');
	AddBindKey("Z", 'Z');
	AddBindKey("MouseLButton", VK_LBUTTON);
	AddBindKey("Space", VK_SPACE);
	AddBindKey("1", '1');
	AddBindKey("2", '2');
	AddBindKey("3", '3');
	AddBindKey("UpKey", VK_UP);
	AddBindKey("DownKey", VK_DOWN);
	AddBindKey("LeftKey", VK_LEFT);
	AddBindKey("RightKey", VK_RIGHT);

	// ������
	AddBindKey("OpenTileMapEditor", 'T');
	SetKeyCtrl("OpenTileMapEditor");

	m_Ctrl = false;
	m_Alt = false;
	m_Shift = false;

	m_MouseProfile = CCollisionManager::GetInst()->FindProfile("Mouse");


	CResourceManager::GetInst()->CreateAnimationSequence("MouseNormal",
		"MouseNormal", TEXT("MapleStory/Mouse/Cursor_Normal_0.bmp"), TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("MouseNormal", 0.f, 0.f, 24.f, 28.f, 0 / 24.f, 3 / 28.f);

	CResourceManager::GetInst()->SetColorKey("MouseNormal", 255, 0, 255);


	std::vector<std::wstring>	vecFileName;

	for (int i = 0; i <= 1; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
		wsprintf(FileName, TEXT("MapleStory/Mouse/Cursor_MouseOvered_%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	CResourceManager::GetInst()->CreateAnimationSequence("MouseOvered",
		"MouseOvered", vecFileName, TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("MouseOvered", 0.f, 0.f, 29.f, 30.f, 3 / 29.f, 6 / 30.f);
	CResourceManager::GetInst()->AddAnimationFrame("MouseOvered", 0.f, 0.f, 30.f, 28.f, 4 / 30.f, 4 / 28.f);

	CResourceManager::GetInst()->SetColorKey("MouseOvered", 255, 0, 255);


	CResourceManager::GetInst()->CreateAnimationSequence("MouseClick",
		"MouseClick", TEXT("MapleStory/Mouse/Cursor_Click_0.bmp"), TEXTURE_PATH);

	CResourceManager::GetInst()->AddAnimationFrame("MouseClick", 0.f, 0.f, 25.f, 23.f, 4 / 25.f, 1 / 23.f);

	CResourceManager::GetInst()->SetColorKey("MouseClick", 255, 0, 255);

	m_MouseObj = new CGameObject;

	m_MouseObj->SetName("Mouse");

	m_MouseObj->Init();

	m_MouseObj->SetSize(32.f, 31.f);

	m_MouseObj->CreateAnimation();

	m_MouseObj->AddAnimation("MouseNormal");
	m_MouseObj->AddAnimation("MouseOvered", true, 0.5f);
	m_MouseObj->AddAnimation("MouseClick");

	ShowCursor(FALSE);
	m_ShowCursor = false;

	return true;
}

void CInput::Update(float DeltaTime)
{
	UpdateMouse(DeltaTime);

	UpdateKeyState(DeltaTime);

	UpdateBindKey(DeltaTime);
}

void CInput::PostUpdate(float DeltaTime)
{
	m_MouseObj->PostUpdate(DeltaTime);
}

void CInput::Render(HDC hDC, float DeltaTime)
{
	m_MouseObj->Render(hDC, DeltaTime);
}

void CInput::UpdateMouse(float DeltaTime)
{
	POINT	ptMouse;

	// ��ũ�� ��ǥ�� ���´�.
	GetCursorPos(&ptMouse);

	// ��ũ�� ��ǥ�� ������ ��ǥ�� �����Ѵ�.
	ScreenToClient(m_hWnd, &ptMouse);

	m_MouseMove.x = (float)ptMouse.x - m_MousePos.x;
	m_MouseMove.y = (float)ptMouse.y - m_MousePos.y;


	m_MousePos.x = (float)ptMouse.x;
	m_MousePos.y = (float)ptMouse.y;

	RECT	rc = {};
	GetClientRect(m_hWnd, &rc);

	if (rc.left <= ptMouse.x && ptMouse.x <= rc.right &&
		rc.top <= ptMouse.y && ptMouse.y <= rc.bottom)
	{
		if (m_ShowCursor)
		{
			m_ShowCursor = false;
			ShowCursor(FALSE);
		}
	}

	else
	{
		if (!m_ShowCursor)
		{
			m_ShowCursor = true;
			ShowCursor(TRUE);
		}
	}



	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_MouseLDown && !m_MouseLPush)
		{
			m_MouseLDown = true;
			m_MouseLPush = true;

			m_MouseObj->ChangeAnimation("MouseClick");
		}

		else
		{
			m_MouseLDown = false;

			m_MouseObj->ChangeAnimation("MouseClick");
		}
	}

	else if (m_MouseLPush)
	{
		m_MouseLDown = false;
		m_MouseLPush = false;
		m_MouseLUp = true;

		m_MouseObj->ChangeAnimation("MouseNormal");
	}

	else if (m_MouseLUp)
	{
		m_MouseLUp = false;

		m_MouseObj->ChangeAnimation("MouseNormal");
	}

	m_MouseObj->SetPos(m_MouseWorldPos.x, m_MouseWorldPos.y);

	m_MouseObj->Update(DeltaTime);
}

void CInput::UpdateKeyState(float DeltaTime)
{
	if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
		m_Ctrl = true;

	else
		m_Ctrl = false;

	if (GetAsyncKeyState(VK_MENU) & 0x8000)
		m_Alt = true;

	else
		m_Alt = false;

	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		m_Shift = true;

	else
		m_Shift = false;

	auto	iter = m_mapKeyState.begin();
	auto	iterEnd = m_mapKeyState.end();

	for (; iter != iterEnd; ++iter)
	{
		bool	KeyPush = false;

		if (GetAsyncKeyState(iter->second->key) & 0x8000)
		{
			KeyPush = true;
		}

		// Ű�� ������ ���
		if (KeyPush)
		{
			// Down�� Push ��� false��� �� Ű�� ���� ���� ���̴�.
			// �׷��Ƿ� �Ѵ� true�� �����Ѵ�.
			if (!iter->second->Down && !iter->second->Push)
			{
				iter->second->Down = true;
				iter->second->Push = true;
			}

			// Down�� Push ���� �ϳ��� true��� Down�� false��
			// �Ǿ�� �Ѵ�. Push�� �̹� ������ true�� ����Ǿ���.
			else
				iter->second->Down = false;
		}

		// Ű�� �ȴ������� ��� Push�� true���
		// ���� �����ӿ� Ű�� ������ �ִٰ� ���� �������ٴ� ���̴�.
		else if (iter->second->Push)
		{
			iter->second->Up = true;
			iter->second->Push = false;
			iter->second->Down = false;
		}

		else if (iter->second->Up)
			iter->second->Up = false;
	}
}

void CInput::UpdateBindKey(float DeltaTime)
{
	auto	iter = m_mapBindKey.begin();
	auto	iterEnd = m_mapBindKey.end();

	for (; iter != iterEnd; ++iter)
	{
		if (iter->second->key->Down &&
			iter->second->Ctrl == m_Ctrl &&
			iter->second->Alt == m_Alt &&
			iter->second->Shift == m_Shift)
		{
			size_t	Size = iter->second->vecFunction[(int)Input_Type::Down].size();

			for (size_t i = 0; i < Size; ++i)
			{
				iter->second->vecFunction[(int)Input_Type::Down][i]->func();
			}
		}

		if (iter->second->key->Push &&
			iter->second->Ctrl == m_Ctrl &&
			iter->second->Alt == m_Alt &&
			iter->second->Shift == m_Shift)
		{
			size_t	Size = iter->second->vecFunction[(int)Input_Type::Push].size();

			for (size_t i = 0; i < Size; ++i)
			{
				iter->second->vecFunction[(int)Input_Type::Push][i]->func();
			}
		}

		if (iter->second->key->Up &&
			iter->second->Ctrl == m_Ctrl &&
			iter->second->Alt == m_Alt &&
			iter->second->Shift == m_Shift)
		{
			size_t	Size = iter->second->vecFunction[(int)Input_Type::Up].size();

			for (size_t i = 0; i < Size; ++i)
			{
				iter->second->vecFunction[(int)Input_Type::Up][i]->func();
			}
		}
	}
}

void CInput::SetKeyCtrl(const std::string& Name, bool Ctrl)
{
	BindKey* Key = FindBindKey(Name);

	if (!Key)
		return;

	Key->Ctrl = Ctrl;
}

void CInput::SetKeyAlt(const std::string& Name, bool Alt)
{
	BindKey* Key = FindBindKey(Name);

	if (!Key)
		return;

	Key->Alt = Alt;
}

void CInput::SetKeyShift(const std::string& Name, bool Shift)
{
	BindKey* Key = FindBindKey(Name);

	if (!Key)
		return;

	Key->Shift = Shift;
}

KeyState* CInput::FindKeyState(unsigned char Key)
{
	auto	iter = m_mapKeyState.find(Key);

	// ��ã���� ���
	if (iter == m_mapKeyState.end())
		return nullptr;

	// iter->first : key
	// iter->second : value
	return iter->second;
}

BindKey* CInput::FindBindKey(const std::string& Name)
{
	auto	iter = m_mapBindKey.find(Name);

	// ��ã���� ���
	if (iter == m_mapBindKey.end())
		return nullptr;

	// iter->first : key
	// iter->second : value
	return iter->second;
}

bool CInput::AddBindKey(const std::string& Name, 
	unsigned char Key)
{
	// ���� �̸����� BindKey�� ��ϵǾ� ���� ���
	if (FindBindKey(Name))
		return false;

	BindKey* NewKey = new BindKey;

	// �ش� Ű�� �̹� KeyState�� ��ϵǾ� �ִ����� ã�´�.
	KeyState* State = FindKeyState(Key);

	// ����� �ȵǾ� ���� ��� KeyState�� ���� ����Ѵ�.
	if (!State)
	{
		State = new KeyState;

		State->key = Key;

		m_mapKeyState.insert(std::make_pair(Key, State));
	}

	NewKey->key = State;
	NewKey->Name = Name;

	m_mapBindKey.insert(std::make_pair(Name, NewKey));

	return true;
}

void CInput::ClearCallback()
{
	auto	iter = m_mapBindKey.begin();
	auto	iterEnd = m_mapBindKey.end();

	for (; iter != iterEnd; ++iter)
	{
		for (int i = 0; i < (int)Input_Type::End; ++i)
		{
			size_t	Size = iter->second->vecFunction[i].size();

			for (size_t j = 0; j < Size; ++j)
			{
				SAFE_DELETE(iter->second->vecFunction[i][j]);
			}

			iter->second->vecFunction[i].clear();
		}
	}
}