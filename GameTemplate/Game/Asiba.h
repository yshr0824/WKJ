#pragma once
class Player;
class Asiba : public IGameObject
{
public:
	Asiba();
	~Asiba();
	bool Start() override;
	void Update();
	void Draw();
	
	void SetPos(const CVector3& pos) 
	{
		m_position = pos;
	}
	void SetRot(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	CVector3 GetPos()
	{
		return m_position;
	}
private:
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();
	Player* m_player = nullptr;
	SkinModel m_model;
};

