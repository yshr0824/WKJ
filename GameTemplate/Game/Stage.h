#pragma once
#include "physics/PhysicsStaticObject.h"
class Asiba;
class Stage : public IGameObject
{
public:
	Stage();
	~Stage();
	bool Start();
	void Draw();
	std::vector<Asiba*> Getasiba()const{			
		return m_asibaVector;
	}
private:
	std::vector<Asiba*> m_asibaVector;				//asiba�̉ϒ��z��
	SkinModel m_model;
	PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g
};



