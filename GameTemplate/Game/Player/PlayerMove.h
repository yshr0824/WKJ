#pragma once

#include "character/CharacterController.h"
class Player;

/// <summary>
/// プレイヤーの移動処理
/// </summary>
class PlayerMove : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pl">移動させるプレイヤー</param>
	PlayerMove(Player* pl);
	/// <summary>
	/// 移動処理を実行する。
	/// </summary>
	/// 
	bool Start();
	void Execute();
	void SetMovePos(const CVector3& pos)
	{
		m_movePos = pos;
	}
	const CVector3& GetMovePos() const
	{
		return m_movePos;
	}
	void SetMoveSp(const CVector3& sp)
	{
		m_moveSp = sp;
	}
	const CVector3& GetMoveSp() const
	{
		return m_moveSp;
	}
	friend class Player;
private:
	void Jump();
	void UpHit();
private:
	Player* m_player = nullptr;
	CVector3 m_movePos = CVector3::Zero();       //PlayerMoveの座標。
	CVector3 m_moveSp = CVector3::Zero();			//PlayerMoveの速度。
	//CVector3 m_moveSpeed = CVector3::Zero();			//Playerの速度。  
	//CVector3 m_position = CVector3::Zero();			//Playerの座標。
	const float m_speed = 0.7f;							//移動速度。
	const float m_jumpSpeed = 26.0f;					//ジャンプ速度。
	const int m_2jumpLimit = 1;							//２段階ジャンプできる回数の上限。
	int m_2jumpnum = 1;									//２段階ジャンプできる回数。
	const float m_wallkick = 35.0f;						//壁ジャンプ。
	const float m_runSpeed = 0.04f;						//走るときの加速。
	const float m_friction = -0.08f;					//摩擦力。
	bool m_kabeTachi = false;							//壁に触ってるかの判定。
	CharacterController m_charaCon;						//キャラコン。
	const float m_radius = 20.0f;						//キャラコンの半径。
	const float m_high = 50.0f;							//キャラコンの高さ

};

