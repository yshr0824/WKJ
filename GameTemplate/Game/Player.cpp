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
	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		m_radius,			//半径。 
		m_high,			//高さ。
		m_position		//初期位置。
	);
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	return false;
}


void Player::Update()
{

	Move();	
	Turn(); 

	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX(), 0.0f);	//3dsMaxで設定されているアニメーションでキャラが回転しているので、補正を入れる。
	qRot.Multiply(m_rotation, qRot);
	//ワールド行列の更新。
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




	m_moveSpeed += cameraForward * lStick_y * m_speed;	//奥方向への移動速度を加算。
	m_moveSpeed += cameraRight * lStick_x * m_speed;		//右方向への移動速度を加算。
	//壁ずり
	if (m_kabeTachi) {
		m_moveSpeed.y -= 10.0f * 1 / 60;
		if (m_moveSpeed.y > 0.0f) {
			m_moveSpeed.y = 0.0f;
		}
	}
	else {
		m_moveSpeed.y -= 100.0f * 1 / 60;
	}
	//ジャンプ
	Jump();
	//走る
	if (g_pad->IsPress(enButtonX)) {
		m_moveSpeed.x += m_moveSpeed.x * m_runSpeed;
		m_moveSpeed.z += m_moveSpeed.z * m_runSpeed;
	}
	//摩擦
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
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
	//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
	//atan2を使用して、角度を求めている。
	//これが回転角度になる。
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	//atanが返してくる角度はラジアン単位なので
	//SetRotationDegではなくSetRotationを使用する。
	m_rotation.SetRotation(CVector3::AxisY(), angle);
}

void Player::Jump()
{
	if (g_pad->IsTrigger(enButtonA) //Aボタンが押されたら
		&& m_charaCon.IsOnGround()  //かつ、地面に居たら
		) {
		//ジャンプする。
		m_moveSpeed.y = m_jumpSpeed;	//上方向に速度を設定して、
	}
	//二段ジャンプ
	if (m_2jumpnum > 0) {
		if (g_pad->IsTrigger(enButtonA)
			&& m_charaCon.IsJump())
		{
			m_moveSpeed.y = m_jumpSpeed;
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
		m_moveSpeed.y = m_jumpSpeed;
		//法線の方向にジャンプさせる。
		CVector3 HitNorm = m_charaCon.GethitNormalXZ();
		HitNorm *= m_wallkick;
		m_moveSpeed = { HitNorm.x,m_jumpSpeed,HitNorm.z };
		//ジャンプ回数が上限でない場合、ジャンプ回数を加算する。
		if (m_2jumpnum < m_2jumpLimit) {
			m_2jumpnum += 1;
		}
	}
	UpHit();
}

void Player::UpHit()
{
	const float stature = (m_radius * 2 + m_high);									//身長
	float nextPos = m_position.y + m_moveSpeed.y + stature;							//playerの現在地 + 身長 + m_movespeeed.y。
	for (int h = 0; h < m_asibaVector.size(); h++)
	{
		float diffX = m_asibaVector.at(h)->GetPos().x - m_position.x;				//playerとasibaの距離を測る。
		float diffZ = m_asibaVector.at(h)->GetPos().z - m_position.z;
		const float Boxsize = 40.0f;												//asibaのサイズ
		if (
			fabsf(diffX) < Boxsize + m_radius &&									//絶対値にしてマイナスをなくす。
			fabsf(diffZ) < Boxsize + m_radius
			)
		{
			float playerHead = m_position.y + stature;								//プレイヤーの頭の位置。
			if ((m_asibaVector.at(h)->GetPos().y - playerHead) > 0.0f) {			//playerの頭からasibaの位置が上にあるかの判定。
				if (m_asibaVector.at(h)->GetPos().y <= nextPos) {					//asibaの位置がnextPos以下かの判定
					m_moveSpeed.y = 0.0f;											//m_movespeed.yを0にする→それ以上上に受けなくなり重力で落ちてくる
				}
			}
		}
	}
}


