#include "stdafx.h"
#include "Player.h"
#include "Asiba.h"
//#include "PlayerMove.h"

Player::Player() :
	m_move(this), //PlayerMoveクラスは引数付きのコンストラクタしかもっていないので、ここで呼び出す。
	m_playerturn(this)
{

}


Player::~Player()
{
	
}

bool Player::Start()
{	
	m_animation = NewGO<AnimationController>(enGameObjectPrio_Middle, "animation");
	m_animation->SetModel(m_model);
	m_position = m_move.GetMovePos();
	m_moveSpeed = m_move.GetMoveSp();
	m_rotation = m_playerturn.GetTurnRot();
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);

	
	return true;

}


void Player::Update()
{
	//移動処理
	m_move.Execute();
	m_position = m_move.GetMovePos();
	m_moveSpeed = m_move.GetMoveSp();
	
	//回転処理
	m_playerturn.Execute(m_moveSpeed);
	m_rotation = m_playerturn.GetTurnRot();

	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX(), 0.0f);	//3dsMaxで設定されているアニメーションでキャラが回転しているので、補正を入れる。
	qRot.Multiply(m_rotation, qRot);


	IGameObjectManager().RegistShadowCaster(&m_model);

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, qRot, CVector3::One());

	
	
	
}

void Player::Draw(/*int renderModer*/)
{

	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		renderMode
	);
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		renderMode2 
	);
}

