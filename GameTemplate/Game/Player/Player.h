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
	void Draw(/*int renderMode*/);		//�`��B
	//void Move();		//�ړ������B
	//void Turn();		//��]�����B
	//void Jump();		//�W�����v�B
	//void UpHit();		//�V�䔻��B
	//position���擾����
	const CVector3& GetPosition() const 
	{
		return m_position;		//Player�̍��W�B
	}
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	const CVector3& GetSpeed() const
	{
		return m_moveSpeed;		//Player�̑��x�B
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
	SkinModel m_model;									//�X�L�����f���B
	std::vector<Asiba*> m_asibaVector;					//����̉ϒ��z��B
	CVector3 m_position = CVector3::Zero();				//Player�̍��W�B
	CVector3 m_moveSpeed = CVector3::Zero();			//Player�̑��x�B
	const float m_radius = 20.0f;						//�L�����R���̔��a�B
	const float m_high = 50.0f;							//�L�����R���̍���
	CQuaternion m_rotation = CQuaternion::Identity();	//Player�̉�]�B
	PlayerMove m_move;									//�ړ������B
	PlayerTurn m_playerturn;							//���񏈗��B
	AnimationController* m_animation = nullptr;
	CharacterController m_charaCon;						//�L�����R���B
	int renderMode = 1;	//�O�Ȃ�ʏ�`��A�P�Ȃ�V���G�b�g�`��B
	int renderMode2 = 0;
};

