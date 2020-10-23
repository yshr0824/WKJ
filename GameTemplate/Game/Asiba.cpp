#include "stdafx.h"
#include "Asiba.h"
#include "Player/Player.h"
Asiba::Asiba()
{
}

Asiba::~Asiba()
{
	
}

bool Asiba::Start()
{
	m_model.Init(L"Assets/modelData/asiba.cmo");
	return true;
}

void Asiba::Update()
{

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Asiba::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
