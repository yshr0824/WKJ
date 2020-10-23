#include "stdafx.h"
#include "PlayerMove.h"
#include "Asiba.h"
#include "Player.h"

PlayerMove::PlayerMove(Player* pl) :
	m_player(pl)
{
	{
		//�L�����N�^�[�R���g���[���[���������B
		m_charaCon.Init(
			m_radius,			//���a�B 
			m_high,			//�����B
			m_movePos		//�����ʒu�B
		);
		SetmovePos(m_player->GetPosition());
		SetmoveSp(m_player->GetSpeed());
	}
}

bool PlayerMove::Start()
{
	return true;
}

void PlayerMove::Execute()
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

	m_moveSp += cameraForward * lStick_y * m_speed;	//�������ւ̈ړ����x�����Z�B
	m_moveSp += cameraRight * lStick_x * m_speed;		//�E�����ւ̈ړ����x�����Z�B
	//�ǂ���
	if (m_kabeTachi) {
		m_moveSp.y -= 10.0f * 1 / 60;
		if (m_moveSp.y > 0.0f) {
			m_moveSp.y = 0.0f;
		}
	}
	else {
		m_moveSp.y -= 100.0f * 1 / 60;
	}
	//�W�����v
	Jump();
	//����
	if (g_pad->IsPress(enButtonX)) {
		m_moveSp.x += m_moveSp.x * m_runSpeed;
		m_moveSp.z += m_moveSp.z * m_runSpeed;
	}
	//���C
	//if (m_charaCon.IsOnGround()) {
		//m_moveSpeed += m_moveSpeed * m_speedUp;
	m_moveSp.x += m_moveSp.x * m_friction;
	m_moveSp.z += m_moveSp.z * m_friction;

	//}
	m_movePos = m_charaCon.Execute(0.5f, m_moveSp);
	m_kabeTachi = m_charaCon.GetkabeHit();
}
void PlayerMove::Jump()
{
	if (g_pad->IsTrigger(enButtonA) //A�{�^���������ꂽ��
		&& m_charaCon.IsOnGround()  //���A�n�ʂɋ�����
		) {
		//�W�����v����B
		m_moveSp.y = m_jumpSpeed;	//������ɑ��x��ݒ肵�āA
	}
	//��i�W�����v
	if (m_2jumpnum > 0) {
		if (g_pad->IsTrigger(enButtonA)
			&& m_charaCon.IsJump())
		{
			m_moveSp.y = m_jumpSpeed;
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
		m_moveSp.y = m_jumpSpeed;
		//�@���̕����ɃW�����v������B
		CVector3 HitNorm = m_charaCon.GethitNormalXZ();
		HitNorm *= m_wallkick;
		m_moveSp = { HitNorm.x,m_jumpSpeed,HitNorm.z };
		//�W�����v�񐔂�����łȂ��ꍇ�A�W�����v�񐔂����Z����B
		if (m_2jumpnum < m_2jumpLimit) {
			m_2jumpnum += 1;
		}
	}
	//�V�䔻��
	UpHit();
}

void PlayerMove::UpHit()
{
	const float stature = (m_radius * 2 + m_high);									//�g��
	float nextPos = m_movePos.y + m_moveSp.y + stature;							//player�̌��ݒn + �g�� + m_movespeeed.y�B
	const std::vector<Asiba*>& asibas = m_player->GetAsiba();
	for (int h = 0; h < asibas.size(); h++)
	{
		float diffX = asibas.at(h)->GetPos().x - m_movePos.x;				//player��asiba�̋����𑪂�B
		float diffZ = asibas.at(h)->GetPos().z - m_movePos.z;
		const float Boxsize = 40.0f;												//asiba�̃T�C�Y
		if (
			fabsf(diffX) < Boxsize + m_radius &&									//��Βl�ɂ��ă}�C�i�X���Ȃ����B
			fabsf(diffZ) < Boxsize + m_radius
			)
		{
			float playerHead = m_movePos.y + stature;								//�v���C���[�̓��̈ʒu�B
			if ((asibas.at(h)->GetPos().y - playerHead) > 0.0f) {			//player�̓�����asiba�̈ʒu����ɂ��邩�̔���B
				if (asibas.at(h)->GetPos().y <= nextPos) {					//asiba�̈ʒu��nextPos�ȉ����̔���
					m_moveSp.y = 0.0f;											//m_movespeed.y��0�ɂ��遨����ȏ��Ɏ󂯂Ȃ��Ȃ�d�͂ŗ����Ă���
				}
			}
		}
	}
}
