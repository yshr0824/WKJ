#include "stdafx.h"
#include "PlayerTurn.h"
#include "Player.h"

PlayerTurn::PlayerTurn(Player* pl) :
	m_player(pl)
{
	SetTurnSp(m_player->GetSpeed());
	SetTurnRot(m_player->GetRot());
}

void const PlayerTurn::Execute(const CVector3& sp) 
{
	m_turnSpeed = sp;
	if (fabsf(m_turnSpeed.x) < 0.001f
		&& fabsf(m_turnSpeed.z) < 0.001f) {
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	float angle = atan2(m_turnSpeed.x, m_turnSpeed.z);
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	m_turnRotation.SetRotation(CVector3::AxisY(), angle);
}
