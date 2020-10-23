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
	//�����_���王�_�̃x�N�g�����v�Z����
	m_toCameraPos = m_target - m_position;
	//���_�̈ʒu����������
	m_toCameraPos.y += 200.0f;
	//�v���C���[�̑������班���������
	m_target.y += 100.0f;
	//�J�������������B
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
	//pad�̓��͂ŃJ��������
	float x = g_pad->GetRStickXF();
	float y = g_pad->GetRStickYF();
	//Y������̉�]
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), m_cameraRot * x);
	qRot.Multiply(m_toCameraPos);
	//X������̉�]
	//X������̉�]�B
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY(), m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, m_cameraRot * y);
	qRot.Multiply(m_toCameraPos);

	//�J�����̉�]�̏�����`�F�b�N����B
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	CVector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	
	if (toPosDir.y < -0.5f) {
		//�J����������������B
		m_toCameraPos = m_toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		//�J�����������������B
		m_toCameraPos = m_toCameraPosOld;
	}
	//���_���v�Z����B
	CVector3 pos = m_target + m_toCameraPos;

	g_camera3D.SetTarget(m_target);
	g_camera3D.SetPosition(pos);
	g_camera3D.Update();

}
