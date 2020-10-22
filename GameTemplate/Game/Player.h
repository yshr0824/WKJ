#pragma once
#include "character/CharacterController.h"
class Asiba;
class Player: public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Draw();		//描画。
	void Move();		//移動処理。
	void Turn();		//回転処理。
	void Jump();		//ジャンプ。
	void UpHit();		//上判定。
	//positionを取得する
	CVector3 GetPosition() 
	{
		return m_position;		//Playerの座標 
	}
	void Setasiba(std::vector<Asiba*> asiba)
	{
		for (Asiba* a : asiba) {
			m_asibaVector.push_back(a);
		}
	}

private:
	const float m_jumpSpeed = 26.0f;					//ジャンプ速度。
	const float m_speed = 0.7f;							//移動速度。
	const float m_runSpeed = 0.04f;						//走るときの加速。
	const float m_wallkick = 35.0f;						//壁ジャンプ。
	bool m_kabeTachi = false;							//壁に触ってるかの判定。
	const float m_friction = -0.08f;					//摩擦力。
	const int m_2jumpLimit = 1;							//２段階ジャンプできる回数の上限。
	int m_2jumpnum = 1;									//２段階ジャンプできる回数。
	SkinModel m_model;									//スキンモデル。
	std::vector<Asiba*> m_asibaVector;					//足場の可変長配列。
	CVector3 m_position = CVector3::Zero();				//Playerの座標。
	CVector3 m_moveSpeed = CVector3::Zero();			//Playerの速度。
	CharacterController m_charaCon;						//キャラコン。
	const float m_radius = 20.0f;						//キャラコンの半径。
	const float m_high = 50.0f;							//キャラコンの高さ
	CQuaternion m_rotation = CQuaternion::Identity();	//Playerの回転。


};

