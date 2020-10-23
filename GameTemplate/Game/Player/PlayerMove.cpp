#include "stdafx.h"
#include "PlayerMove.h"
#include "Asiba.h"
#include "Player.h"

PlayerMove::PlayerMove(Player* pl) :
	m_player(pl)
{
	{
		//キャラクターコントローラーを初期化。
		m_charaCon.Init(
			m_radius,			//半径。 
			m_high,			//高さ。
			m_movePos		//初期位置。
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
	//左スティックの入力量を受け取る。
	float lStick_x = g_pad->GetLStickXF();
	float lStick_y = g_pad->GetLStickYF();
	//カメラの前方方向と右方向を取得。
	CVector3 cameraForward = g_camera3D.GetForward();
	CVector3 cameraRight = g_camera3D.GetRight();
	//XZ平面での前方方向、右方向に変換する。
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	////XZ成分の移動速度をクリア。
	//m_moveSpeed.x = 0.0f;
	//m_moveSpeed.z = 0.0f;

	m_moveSp += cameraForward * lStick_y * m_speed;	//奥方向への移動速度を加算。
	m_moveSp += cameraRight * lStick_x * m_speed;		//右方向への移動速度を加算。
	//壁ずり
	if (m_kabeTachi) {
		m_moveSp.y -= 10.0f * 1 / 60;
		if (m_moveSp.y > 0.0f) {
			m_moveSp.y = 0.0f;
		}
	}
	else {
		m_moveSp.y -= 100.0f * 1 / 60;
	}
	//ジャンプ
	Jump();
	//走る
	if (g_pad->IsPress(enButtonX)) {
		m_moveSp.x += m_moveSp.x * m_runSpeed;
		m_moveSp.z += m_moveSp.z * m_runSpeed;
	}
	//摩擦
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
	if (g_pad->IsTrigger(enButtonA) //Aボタンが押されたら
		&& m_charaCon.IsOnGround()  //かつ、地面に居たら
		) {
		//ジャンプする。
		m_moveSp.y = m_jumpSpeed;	//上方向に速度を設定して、
	}
	//二段ジャンプ
	if (m_2jumpnum > 0) {
		if (g_pad->IsTrigger(enButtonA)
			&& m_charaCon.IsJump())
		{
			m_moveSp.y = m_jumpSpeed;
			m_2jumpnum -= 1;

		}
	}
	//ジャンプ回数が上限でない場合、地面にいるときジャンプ回数を加算する。
	if (m_charaCon.IsOnGround()
		&& m_2jumpnum < m_2jumpLimit)
	{
		m_2jumpnum += 1;
	}
	//壁ジャンプ
	if (m_kabeTachi
		&& g_pad->IsTrigger(enButtonA)
		&& !m_charaCon.IsOnGround()) {
		m_moveSp.y = m_jumpSpeed;
		//法線の方向にジャンプさせる。
		CVector3 HitNorm = m_charaCon.GethitNormalXZ();
		HitNorm *= m_wallkick;
		m_moveSp = { HitNorm.x,m_jumpSpeed,HitNorm.z };
		//ジャンプ回数が上限でない場合、ジャンプ回数を加算する。
		if (m_2jumpnum < m_2jumpLimit) {
			m_2jumpnum += 1;
		}
	}
	//天井判定
	UpHit();
}

void PlayerMove::UpHit()
{
	const float stature = (m_radius * 2 + m_high);									//身長
	float nextPos = m_movePos.y + m_moveSp.y + stature;							//playerの現在地 + 身長 + m_movespeeed.y。
	const std::vector<Asiba*>& asibas = m_player->GetAsiba();
	for (int h = 0; h < asibas.size(); h++)
	{
		float diffX = asibas.at(h)->GetPos().x - m_movePos.x;				//playerとasibaの距離を測る。
		float diffZ = asibas.at(h)->GetPos().z - m_movePos.z;
		const float Boxsize = 40.0f;												//asibaのサイズ
		if (
			fabsf(diffX) < Boxsize + m_radius &&									//絶対値にしてマイナスをなくす。
			fabsf(diffZ) < Boxsize + m_radius
			)
		{
			float playerHead = m_movePos.y + stature;								//プレイヤーの頭の位置。
			if ((asibas.at(h)->GetPos().y - playerHead) > 0.0f) {			//playerの頭からasibaの位置が上にあるかの判定。
				if (asibas.at(h)->GetPos().y <= nextPos) {					//asibaの位置がnextPos以下かの判定
					m_moveSp.y = 0.0f;											//m_movespeed.yを0にする→それ以上上に受けなくなり重力で落ちてくる
				}
			}
		}
	}
}
