#pragma once
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	
	//カメラの注視点を設定する
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
	CVector3 m_target = CVector3::Zero();				//カメラの注視点
	CVector3 m_position = { 0.0f, 100.0f, -350.0f };	//カメラの座標
	CVector3 m_toCameraPos = CVector3::Zero();			//視点の位置
	const float m_cameraRot = 3.0f;						//カメラの回転速度

};

