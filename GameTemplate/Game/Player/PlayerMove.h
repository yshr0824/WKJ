#pragma once

#include "character/CharacterController.h"
class Player;

/// <summary>
/// �v���C���[�̈ړ�����
/// </summary>
class PlayerMove : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pl">�ړ�������v���C���[</param>
	PlayerMove(Player* pl);
	/// <summary>
	/// �ړ����������s����B
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
	CVector3 m_movePos = CVector3::Zero();       //PlayerMove�̍��W�B
	CVector3 m_moveSp = CVector3::Zero();			//PlayerMove�̑��x�B
	//CVector3 m_moveSpeed = CVector3::Zero();			//Player�̑��x�B  
	//CVector3 m_position = CVector3::Zero();			//Player�̍��W�B
	const float m_speed = 0.7f;							//�ړ����x�B
	const float m_jumpSpeed = 26.0f;					//�W�����v���x�B
	const int m_2jumpLimit = 1;							//�Q�i�K�W�����v�ł���񐔂̏���B
	int m_2jumpnum = 1;									//�Q�i�K�W�����v�ł���񐔁B
	const float m_wallkick = 35.0f;						//�ǃW�����v�B
	const float m_runSpeed = 0.04f;						//����Ƃ��̉����B
	const float m_friction = -0.08f;					//���C�́B
	bool m_kabeTachi = false;							//�ǂɐG���Ă邩�̔���B
	CharacterController m_charaCon;						//�L�����R���B
	const float m_radius = 20.0f;						//�L�����R���̔��a�B
	const float m_high = 50.0f;							//�L�����R���̍���

};

