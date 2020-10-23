#include "stdafx.h"
#include "GameCamera.h"

GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	//注視点から視点のベクトルを計算する
	m_toCameraPos = m_target - m_position;
	//視点の位置を高くする
	m_toCameraPos.y += 200.0f;
	//プレイヤーの足元から少し上を見る
	m_target.y += 100.0f;
	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 100.0f, 400.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetNear(1.0f);
	g_camera3D.SetFar(10000.0f);
	g_camera3D.Update();

	return false;
}

void GameCamera::Update()
{

	CVector3 m_toCameraPosOld = m_toCameraPos;
	//padの入力でカメラを回す
	float x = g_pad->GetRStickXF();
	float y = g_pad->GetRStickYF();
	//Y軸周りの回転
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), m_cameraRot * x);
	qRot.Multiply(m_toCameraPos);
	//X軸周りの回転
	//X軸周りの回転。
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY(), m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, m_cameraRot * y);
	qRot.Multiply(m_toCameraPos);

	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	CVector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	
	if (toPosDir.y < -0.5f) {
		//カメラが上向きすぎ。
		m_toCameraPos = m_toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		//カメラが下向きすぎ。
		m_toCameraPos = m_toCameraPosOld;
	}
	//視点を計算する。
	CVector3 pos = m_target + m_toCameraPos;

	g_camera3D.SetTarget(m_target);
	g_camera3D.SetPosition(pos);
	g_camera3D.Update();

}
