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
	

	////Effekseer�J�����s���ݒ�B
	////�܂���Effeseer�̍s��^�̕ϐ��ɁA�J�����s��ƃv���W�F�N�V�����s����R�s�[�B
	////126�s�ځ`134�s�ڂ𖈃t���[���Ăяo��
	//Effekseer::Matrix44 efCameraMat;
	//g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
	//Effekseer::Matrix44 efProjMat;
	//g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
	////�J�����s��ƃv���W�F�N�V�����s���ݒ�B
	//m_effekseerRenderer->SetCameraMatrix(efCameraMat);
	//m_effekseerRenderer->SetProjectionMatrix(efProjMat);
	////Effekseer���X�V�B
	//m_effekseerManager->Update();
}



//void Game::InitEffekseer()
//{
//	//�����_���[���������B
//	m_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
//		g_graphicsEngine->GetD3DDevice(),			//D3D�f�o�C�X�B
//		g_graphicsEngine->GetD3DDeviceContext(),	//D3D�f�o�C�X�R���e�L�X�g�B
//		20000										//�|���̍ő吔�B
//	);
//	//�G�t�F�N�g�}�l�[�W�����������B
//	m_effekseerManager = Effekseer::Manager::Create(10000);
//
//	// �`��p�C���X�^���X����`��@�\��ݒ�
//	m_effekseerManager->SetSpriteRenderer(m_effekseerRenderer->CreateSpriteRenderer());
//	m_effekseerManager->SetRibbonRenderer(m_effekseerRenderer->CreateRibbonRenderer());
//	m_effekseerManager->SetRingRenderer(m_effekseerRenderer->CreateRingRenderer());
//	m_effekseerManager->SetTrackRenderer(m_effekseerRenderer->CreateTrackRenderer());
//	m_effekseerManager->SetModelRenderer(m_effekseerRenderer->CreateModelRenderer());
//
//	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
//	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
//	m_effekseerManager->SetTextureLoader(m_effekseerRenderer->CreateTextureLoader());
//	m_effekseerManager->SetModelLoader(m_effekseerRenderer->CreateModelLoader());
//
//}
