#include "stdafx.h"
#include "Player2.h"

Player2::Player2()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");
}

Player2::~Player2()
{

}

void Player2::Update()
{
	if (g_pad[0].IsPress(enButtonRight)) {
		m_position.x -= 10.0;
	}
	if (g_pad[0].IsPress(enButtonLeft)) {
		m_position.x += 10.0;
	}
	if (g_pad[0].IsPress(enButtonUp)) {
		m_position.y += 10.0f;
	}
	if (g_pad[0].IsPress(enButtonDown)) {
		m_position.y -= 10.0f;
	}
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}

void Player2::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
