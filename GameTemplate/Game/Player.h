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
	void Draw();		//�`��B
	void Move();		//�ړ������B
	void Turn();		//��]�����B
	void Jump();		//�W�����v�B
	void UpHit();		//�㔻��B
	//position���擾����
	CVector3 GetPosition() 
	{
		return m_position;		//Player�̍��W 
	}
	void Setasiba(std::vector<Asiba*> asiba)
	{
		for (Asiba* a : asiba) {
			m_asibaVector.push_back(a);
		}
	}

private:
	const float m_jumpSpeed = 26.0f;					//�W�����v���x�B
	const float m_speed = 0.7f;							//�ړ����x�B
	const float m_runSpeed = 0.04f;						//����Ƃ��̉����B
	const float m_wallkick = 35.0f;						//�ǃW�����v�B
	bool m_kabeTachi = false;							//�ǂɐG���Ă邩�̔���B
	const float m_friction = -0.08f;					//���C�́B
	const int m_2jumpLimit = 1;							//�Q�i�K�W�����v�ł���񐔂̏���B
	int m_2jumpnum = 1;									//�Q�i�K�W�����v�ł���񐔁B
	SkinModel m_model;									//�X�L�����f���B
	std::vector<Asiba*> m_asibaVector;					//����̉ϒ��z��B
	CVector3 m_position = CVector3::Zero();				//Player�̍��W�B
	CVector3 m_moveSpeed = CVector3::Zero();			//Player�̑��x�B
	CharacterController m_charaCon;						//�L�����R���B
	const float m_radius = 20.0f;						//�L�����R���̔��a�B
	const float m_high = 50.0f;							//�L�����R���̍���
	CQuaternion m_rotation = CQuaternion::Identity();	//Player�̉�]�B


};

