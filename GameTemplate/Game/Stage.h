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
	std::vector<Asiba*> m_asibaVector;				//asibaの可変長配列
	SkinModel m_model;
	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクト
};



