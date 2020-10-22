#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Stage.h"
#include "GameCamera.h"

Game::Game()
{
	
}

Game::~Game()
{
	DeleteGO(m_gamecamera);
	DeleteGO(m_stage);
	DeleteGO(m_player);
}

bool Game::Start()
{
	m_gamecamera = NewGO<GameCamera>(0, "gamecamera");
	m_stage = NewGO<Stage>(0, "stage");
	m_player = NewGO<Player>(0, "player");
	m_player->Setasiba(m_stage->Getasiba());
	
	return true;
}

void Game::Update()
{
	m_gamecamera->SetTarget(m_player->GetPosition());
	m_gamecamera->SetPosition(m_player->GetPosition());
	/*if (g_pad->IsTrigger(enButtonA))
	{
		if (m_player != nullptr) {
			DeleteGO(m_player);
			m_player = nullptr;
		}
		
	}
	if (g_pad->IsTrigger(enButtonB))
	{
		m_player = NewGO<Player>(0,"player");
	}*/
}
