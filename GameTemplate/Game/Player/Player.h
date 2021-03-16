#pragma once
#include "character/CharacterController.h"
#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"

#include "PlayerMove.h"
#include "PlayerTurn.h"
#include "AnimationController.h"
class Asiba;
//class PlayerMove;
class Player: public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Draw(/*int renderMode*/);		//描画。
	//void Move();		//移動処理。
	//void Turn();		//回転処理。
	//void Jump();		//ジャンプ。
	//void UpHit();		//天井判定。
	//positionを取得する
	const CVector3& GetPosition() const 
	{
		return m_position;		//Playerの座標。
	}
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	const CVector3& GetSpeed() const
	{
		return m_moveSpeed;		//Playerの速度。
	}
	void SetSpeed(const CVector3& sp)
	{
		m_moveSpeed = sp;
	}
	const CQuaternion& GetRot() const
	{
		return m_rotation;
	}
	void SetRot(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	void Setasiba(const std::vector<Asiba*>& asiba)
	{
		for (Asiba* p : asiba) {
			m_asibaVector.push_back(p);
		}
	}
	const std::vector<Asiba*>& GetAsiba() const
	{
		return m_asibaVector;
	}
	friend class PlayerMove;
private:
	SkinModel m_model;									//スキンモデル。
	std::vector<Asiba*> m_asibaVector;					//足場の可変長配列。
	CVector3 m_position = CVector3::Zero();				//Playerの座標。
	CVector3 m_moveSpeed = CVector3::Zero();			//Playerの速度。
	const float m_radius = 20.0f;						//キャラコンの半径。
	const float m_high = 50.0f;							//キャラコンの高さ
	CQuaternion m_rotation = CQuaternion::Identity();	//Playerの回転。
	PlayerMove m_move;									//移動処理。
	PlayerTurn m_playerturn;							//旋回処理。
	AnimationController* m_animation = nullptr;
	CharacterController m_charaCon;						//キャラコン。
	int renderMode = 1;	//０なら通常描画、１ならシルエット描画。
	int renderMode2 = 0;
};

