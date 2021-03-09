#include "stdafx.h"
#include "Stage.h"
#include "Asiba.h"
#include "level/Level.h"
Stage::Stage()
{
	Level level;
	wchar_t* a = L"Assets/level/haikei.tkl";
	level.Init(a, [&](auto fuckModel) {
		if (wcscmp(fuckModel.name, L"asiba") == 0)
		{
			m_asibaVector.push_back( NewGO<Asiba>(enGameObjectPrio_Middle, "asiba"));
			m_asibaVector.back()->SetPos(fuckModel.position);
			m_asibaVector.back()->SetRot(fuckModel.rotation);
		}
		fuckModel.position;
		fuckModel.rotation;
		fuckModel.name;
		return true;
		});
	
}

Stage::~Stage()
{
}

bool Stage::Start()
{
	
	
	m_model.Init(L"Assets/modelData/haikei.cmo");
	
	m_model.SetShadowReciever(true);

	m_physicsStaticObject.CreateMeshObject(m_model, CVector3::Zero(), CQuaternion::Identity());
	return true;
}



void Stage::Draw()
{
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());

	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		renderMode
	);
}
