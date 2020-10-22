#pragma once
#include "character/CharacterController.h"
class Player2
{
public:
	Player2();
	~Player2();
	void Update();
	void Draw();
	CVector3 m_moveSpeed = CVector3::Zero();
	CVector3 m_position = CVector3::Zero();
private:
	SkinModel m_model;									//スキンモデル。
};

