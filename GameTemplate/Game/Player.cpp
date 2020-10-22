#include "stdafx.h"
#include "Player.h"
#include "Asiba.h"

Player::Player()
{

}


Player::~Player()
{

}

bool Player::Start()
{
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		m_radius,			//���a�B 
		m_high,			//�����B
		m_position		//�����ʒu�B
	);
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	return false;
}


void Player::Update()
{

	Move();	
	Turn(); 

	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX(), 0.0f);	//3dsMax�Őݒ肳��Ă���A�j���[�V�����ŃL��������]���Ă���̂ŁA�␳������B
	qRot.Multiply(m_rotation, qRot);
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, qRot, CVector3::One());
}
void Player::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Player::Move()
{
	//m_position.x += g_pad->GetLStickXF() * 5.0f;
	//m_position.z += g_pad->GetLStickYF() * 5.0f;
	//���X�e�B�b�N�̓��͗ʂ��󂯎��B
	float lStick_x = g_pad->GetLStickXF();
	float lStick_y = g_pad->GetLStickYF();
	//�J�����̑O�������ƉE�������擾�B
	CVector3 cameraForward = g_camera3D.GetForward();
	CVector3 cameraRight = g_camera3D.GetRight();
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	////XZ�����̈ړ����x���N���A�B
	//m_moveSpeed.x = 0.0f;
	//m_moveSpeed.z = 0.0f;




	m_moveSpeed += cameraForward * lStick_y * m_speed;	//�������ւ̈ړ����x�����Z�B
	m_moveSpeed += cameraRight * lStick_x * m_speed;		//�E�����ւ̈ړ����x�����Z�B
	//�ǂ���
	if (m_kabeTachi) {
		m_moveSpeed.y -= 10.0f * 1 / 60;
		if (m_moveSpeed.y > 0.0f) {
			m_moveSpeed.y = 0.0f;
		}
	}
	else {
		m_moveSpeed.y -= 100.0f * 1 / 60;
	}
	//�W�����v
	Jump();
	//����
	if (g_pad->IsPress(enButtonX)) {
		m_moveSpeed.x += m_moveSpeed.x * m_runSpeed;
		m_moveSpeed.z += m_moveSpeed.z * m_runSpeed;
	}
	//���C
	//if (m_charaCon.IsOnGround()) {
		//m_moveSpeed += m_moveSpeed * m_speedUp;
	m_moveSpeed.x += m_moveSpeed.x * m_friction;
	m_moveSpeed.z += m_moveSpeed.z * m_friction;

	//}

	m_position = m_charaCon.Execute(0.5f, m_moveSpeed);
	m_kabeTachi = m_charaCon.GetkabeHit();
}

void Player::Turn()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	m_rotation.SetRotation(CVector3::AxisY(), angle);
}

void Player::Jump()
{
	if (g_pad->IsTrigger(enButtonA) //A�{�^���������ꂽ��
		&& m_charaCon.IsOnGround()  //���A�n�ʂɋ�����
		) {
		//�W�����v����B
		m_moveSpeed.y = m_jumpSpeed;	//������ɑ��x��ݒ肵�āA
	}
	//��i�W�����v
	if (m_2jumpnum > 0) {
		if (g_pad->IsTrigger(enButtonA)
			&& m_charaCon.IsJump())
		{
			m_moveSpeed.y = m_jumpSpeed;
			m_2jumpnum -= 1;

		}
	}
	//�W�����v�񐔂�����łȂ��ꍇ�A�n�ʂɂ���Ƃ��W�����v�񐔂����Z����B
	if (m_charaCon.IsOnGround()
		&& m_2jumpnum < m_2jumpLimit)
	{
		m_2jumpnum += 1;
	}
	//�ǃW�����v
	if (m_kabeTachi
		&& g_pad->IsTrigger(enButtonA)
		&& !m_charaCon.IsOnGround()) {
		m_moveSpeed.y = m_jumpSpeed;
		//�@���̕����ɃW�����v������B
		CVector3 HitNorm = m_charaCon.GethitNormalXZ();
		HitNorm *= m_wallkick;
		m_moveSpeed = { HitNorm.x,m_jumpSpeed,HitNorm.z };
		//�W�����v�񐔂�����łȂ��ꍇ�A�W�����v�񐔂����Z����B
		if (m_2jumpnum < m_2jumpLimit) {
			m_2jumpnum += 1;
		}
	}
	UpHit();
}

void Player::UpHit()
{
	const float stature = (m_radius * 2 + m_high);									//�g��
	float nextPos = m_position.y + m_moveSpeed.y + stature;							//player�̌��ݒn + �g�� + m_movespeeed.y�B
	for (int h = 0; h < m_asibaVector.size(); h++)
	{
		float diffX = m_asibaVector.at(h)->GetPos().x - m_position.x;				//player��asiba�̋����𑪂�B
		float diffZ = m_asibaVector.at(h)->GetPos().z - m_position.z;
		const float Boxsize = 40.0f;												//asiba�̃T�C�Y
		if (
			fabsf(diffX) < Boxsize + m_radius &&									//��Βl�ɂ��ă}�C�i�X���Ȃ����B
			fabsf(diffZ) < Boxsize + m_radius
			)
		{
			float playerHead = m_position.y + stature;								//�v���C���[�̓��̈ʒu�B
			if ((m_asibaVector.at(h)->GetPos().y - playerHead) > 0.0f) {			//player�̓�����asiba�̈ʒu����ɂ��邩�̔���B
				if (m_asibaVector.at(h)->GetPos().y <= nextPos) {					//asiba�̈ʒu��nextPos�ȉ����̔���
					m_moveSpeed.y = 0.0f;											//m_movespeed.y��0�ɂ��遨����ȏ��Ɏ󂯂Ȃ��Ȃ�d�͂ŗ����Ă���
				}
			}
		}
	}
}


