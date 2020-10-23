#pragma once

class Player;

class PlayerTurn
{
public:
	PlayerTurn(Player* pl);
	void const Execute(const CVector3& sp);
	void SetturnSp(const CVector3& pos)
	{
		m_turnSpeed = pos;
	}
	const CVector3& GetturnSp() const
	{
		return m_turnSpeed;
	}
	void SetturnRot(const CQuaternion& rot)
	{
		m_turnRotation = rot;
	}
	const CQuaternion& GetturnRot() const
	{
		return m_turnRotation;
	}
	friend class Player;
private:
	Player* m_player = nullptr;
	CVector3 m_turnSpeed = CVector3::Zero();					//Turnで使うspeed。
	CQuaternion m_turnRotation = CQuaternion::Identity();		//turnで使うrotaition。
};