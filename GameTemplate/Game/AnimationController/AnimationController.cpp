#include "stdafx.h"
#include "AnimationController.h"



AnimationController::AnimationController()
{
	//初期ステートは待機。
	ChangeState(&m_idelAnimation);
}

AnimationController::~AnimationController()
{
}

bool AnimationController::Start()
{
	/*m_animationCrip[animidle].Load(L"Assets/animData/idle.tka");
	m_animationCrip[animidle].SetLoopFlag(true);

	m_animationCrip[animwalk].Load(L"Assets/animData/walk.tka");
	m_animationCrip[animwalk].SetLoopFlag(true);

	m_animationCrip[animrun].Load(L"Assets/animData/run.tka");
	m_animationCrip[animrun].SetLoopFlag(true);*/

	/*m_animationCrip[0].Load(L"Assets/animData/jump.tka");
	m_animationCrip[0].SetLoopFlag(false);*/


	//アニメーションの初期化。
	//m_animation.Init(
	//	*m_model,					//アニメーションを流すスキンモデル。
	//								//これでアニメーションとスキンモデルが関連付けされる。
	//	m_animationCrip,			//アニメーションクリップの配列。
	//	1							//アニメーションクリップの数。
	//);



	m_idelAnimation.SetIdelModel(*m_model);

	return true;
}
void AnimationController::ChangeState(IPlayerState* nextState)
{
	//待機状態に切り替え。
	if (m_currentState != nullptr) {
		m_currentState->Leave();
	}
	m_currentState = nextState;
	m_currentState->Enter();
}
void AnimationController::Update()
{


	//if (fabsf(g_pad->GetLStickXF()) > 0.001f || fabsf(g_pad->GetLStickYF()) > 0.001f)
	//{
	//	if (m_isJump == false) {
	//		m_isMove = true;
	//		if (m_isMove == true)
	//		{
	//			if (m_isJump == false) {

	//				if (m_isrun == false) {
	//					m_animation.Play(animwalk, 0.3f);		//walkアニメーション
	//				}
	//				if (g_pad->IsPress(enButtonX)) {			//runアニメーション
	//					m_isrun = true;
	//					if (m_isrun == true)
	//					{
	//						m_animation.Play(animrun, 0.3f);
	//					}
	//				}
	//				else {
	//					m_isrun = false;
	//				}
	//			}
	//		}
	//		m_isMove = false;
	//	}

	//}
	//
	//if (fabsf(g_pad->GetLStickXF()) < 0.001f && fabsf(g_pad->GetLStickYF()) < 0.001f)
	//{
	//	m_animation.Play(animidle, 0.3f);
	//}
	//else if (m_isJump == false && m_animation.IsPlaying() == false) {
	//	m_animation.Play(animidle, 0.3f);
	//}
	////上方向に力がかかっていてかつ、地面にいない　→ジャンプと落下のアニメーションがいる。
	//if (g_pad->IsPress(enButtonA) ) {
	//	m_isJump = true;
	//	if (m_isJump == true) {
	//		m_animation.Play(animjump, 0.3f);

	//	}
	//	m_isJump = false;
	//}

	m_currentState->Update();
	if (GetAsyncKeyState('J')) {
		if (m_currentState->IsPossibleJump()) {
			//m_animation.Play(0, 0.3f);
		}
	}

	//if (GetAsyncKeyState('A')) {
	//	ChangeState(&idleState);
	//}

	//if (GetAsyncKeyState('S')) {
	//	//移動状態に切り替え。
	//	ChangeState(&moveState);
	//}

	if (fabsf(g_pad->GetLStickXF()) < 0.001f && fabsf(g_pad->GetLStickYF()) < 0.001f) {
		//死亡状態に切り替え。
		ChangeState(&m_idelAnimation);
	}


	//アニメーションを呼び出す

	m_animation.Update(1.0f / 30.0f);



}
