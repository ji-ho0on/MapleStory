#pragma once

#include "Scene.h"

#include "../GameObject/Card.h"

enum class EMonster_Type
{
	Hector,
	WhiteFang,
	Max
};

struct MonsterSpawnInfo
{
	bool			Spawn;
	int				SpawnNumber;
	Vector2			Pos;
	EMonster_Type	Type;
};

class CTheSeed2F :
	public CScene
{
	friend class CSceneManager;

protected:
	CTheSeed2F();
	virtual ~CTheSeed2F();

public:
	bool Init();
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);

private:
	bool				m_RedCardOn;
	class CRedCard* m_RedCard;

	bool				m_BlueCardOn;
	class CBlueCard* m_BlueCard;

	bool				m_GreenCardOn;
	class CGreenCard* m_GreenCard;

	bool				m_YellowCardOn;
	class CYellowCard* m_YellowCard;

	CCard* m_SelectedCard;

	MonsterSpawnInfo	m_SpawnInfo[21];
	float				m_SpawnTime;

	std::vector<std::string>	m_vecSequenceKey[(int)ECard_Color::Max];

public:
	void SelectCard();
	void ChangeCard(CCard* ChangeCard);
	void ResetSpawn(int SpawnNumber);

private:
	void CreateAnimationSequence();
	void PlayerAnimationSequence();
	void PlayerEffectAnimationSequence();
	void MonsterAnimationSequence();
	void ObjectAnimationSequence1();
	void ObjectAnimationSequence2();
};