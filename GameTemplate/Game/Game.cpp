#include "stdafx.h"
#include "Game.h"
#include "Player/Player.h"
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
	m_stage = NewGO<Stage>(enGameObjectPrio_Middle, "stage");
	m_player = NewGO<Player>(enGameObjectPrio_Middle, "player");
	m_gamecamera = NewGO<GameCamera>(enGameObjectPrio_Low, "gamecamera");
	m_player->Setasiba(m_stage->Getasiba());
	
	return true;
}

void Game::Update()
{
	m_gamecamera->SetTarget(m_player->GetPosition());
	m_gamecamera->SetPosition(m_player->GetPosition());
	

	////Effekseerカメラ行列を設定。
	////まずはEffeseerの行列型の変数に、カメラ行列とプロジェクション行列をコピー。
	////126行目〜134行目を毎フレーム呼び出す
	//Effekseer::Matrix44 efCameraMat;
	//g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
	//Effekseer::Matrix44 efProjMat;
	//g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
	////カメラ行列とプロジェクション行列を設定。
	//m_effekseerRenderer->SetCameraMatrix(efCameraMat);
	//m_effekseerRenderer->SetProjectionMatrix(efProjMat);
	////Effekseerを更新。
	//m_effekseerManager->Update();
}



//void Game::InitEffekseer()
//{
//	//レンダラーを初期化。
//	m_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
//		g_graphicsEngine->GetD3DDevice(),			//D3Dデバイス。
//		g_graphicsEngine->GetD3DDeviceContext(),	//D3Dデバイスコンテキスト。
//		20000										//板ポリの最大数。
//	);
//	//エフェクトマネージャを初期化。
//	m_effekseerManager = Effekseer::Manager::Create(10000);
//
//	// 描画用インスタンスから描画機能を設定
//	m_effekseerManager->SetSpriteRenderer(m_effekseerRenderer->CreateSpriteRenderer());
//	m_effekseerManager->SetRibbonRenderer(m_effekseerRenderer->CreateRibbonRenderer());
//	m_effekseerManager->SetRingRenderer(m_effekseerRenderer->CreateRingRenderer());
//	m_effekseerManager->SetTrackRenderer(m_effekseerRenderer->CreateTrackRenderer());
//	m_effekseerManager->SetModelRenderer(m_effekseerRenderer->CreateModelRenderer());
//
//	// 描画用インスタンスからテクスチャの読込機能を設定
//	// 独自拡張可能、現在はファイルから読み込んでいる。
//	m_effekseerManager->SetTextureLoader(m_effekseerRenderer->CreateTextureLoader());
//	m_effekseerManager->SetModelLoader(m_effekseerRenderer->CreateModelLoader());
//
//}
