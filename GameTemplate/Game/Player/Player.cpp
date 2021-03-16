#include "stdafx.h"
#include "Player.h"
#include "Asiba.h"
//#include "PlayerMove.h"

Player::Player() :
	m_move(this), //PlayerMove�N���X�͈����t���̃R���X�g���N�^���������Ă��Ȃ��̂ŁA�����ŌĂяo���B
	m_playerturn(this)
{

}


Player::~Player()
{
	
}

bool Player::Start()
{	
	m_animation = NewGO<AnimationController>(enGameObjectPrio_Middle, "animation");
	m_animation->SetModel(m_model);
	m_position = m_move.GetMovePos();
	m_moveSpeed = m_move.GetMoveSp();
	m_rotation = m_playerturn.GetTurnRot();
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);

	
	return true;

}


void Player::Update()
{
	//�ړ�����
	m_move.Execute();
	m_position = m_move.GetMovePos();
	m_moveSpeed = m_move.GetMoveSp();
	
	//��]����
	m_playerturn.Execute(m_moveSpeed);
	m_rotation = m_playerturn.GetTurnRot();

	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX(), 0.0f);	//3dsMax�Őݒ肳��Ă���A�j���[�V�����ŃL��������]���Ă���̂ŁA�␳������B
	qRot.Multiply(m_rotation, qRot);


	IGameObjectManager().RegistShadowCaster(&m_model);

	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, qRot, CVector3::One());

	
	
	
}

void Player::Draw(/*int renderModer*/)
{

	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		renderMode
	);
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		renderMode2 
	);
}

