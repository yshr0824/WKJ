#pragma once

class Player;

class PlayerTurn
{
public:
	PlayerTurn(Player* pl);
	void const Execute(const CVector3& sp);
	void SetTurnSp(const CVector3& pos)
	{
		m_turnSpeed = pos;
	}
	const CVector3& GetTurnSp() const
	{
		return m_turnSpeed;
	}
	void SetTurnRot(const CQuaternion& rot)
	{
		m_turnRotation = rot;
	}
	const CQuaternion& GetTurnRot() const
	{
		return m_turnRotation;
	}
	friend class Player;
private:
	Player* m_player = nullptr;
	CVector3 m_turnSpeed = CVector3::Zero();					//Turnで使うspeed。
	CQuaternion m_turnRotation = CQuaternion::Identity();		//turnで使うrotaition。
};