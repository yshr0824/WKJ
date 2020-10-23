#pragma once
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	
	//�J�����̒����_��ݒ肷��
	void SetTarget(CVector3 target)
	{
		m_target = target;
	}
	void SetPosition(CVector3 pos)
	{
		m_position.x = pos.x;
		m_position.y = pos.y += 100.0;
		m_position.z = pos.z += 300.0;
		
	}
private:
	CVector3 m_target = CVector3::Zero();				//�J�����̒����_
	CVector3 m_position = { 0.0f, 100.0f, -350.0f };	//�J�����̍��W
	CVector3 m_toCameraPos = CVector3::Zero();			//���_�̈ʒu
	const float m_cameraRot = 3.0f;						//�J�����̉�]���x

};

