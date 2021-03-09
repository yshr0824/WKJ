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
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
	//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
	//atan2を使用して、角度を求めている。
	//これが回転角度になる。
	float angle = atan2(m_turnSpeed.x, m_turnSpeed.z);
	//atanが返してくる角度はラジアン単位なので
	//SetRotationDegではなくSetRotationを使用する。
	m_turnRotation.SetRotation(CVector3::AxisY(), angle);
}
