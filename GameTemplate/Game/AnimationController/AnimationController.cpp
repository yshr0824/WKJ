#include "stdafx.h"
#include "AnimationController.h"

AnimationController::AnimationController() 
{

}

AnimationController::~AnimationController()
{

}

bool AnimationController::Start()
{
	m_animationCrip[animidle].Load(L"Assets/animData/idle.tka");
	m_animationCrip[animidle].SetLoopFlag(true);

	m_animationCrip[animwalk].Load(L"Assets/animData/walk.tka");
	m_animationCrip[animwalk].SetLoopFlag(true);

	m_animationCrip[animrun].Load(L"Assets/animData/run.tka");
	m_animationCrip[animrun].SetLoopFlag(true);

	m_animationCrip[animjump].Load(L"Assets/animData/jump.tka");
	m_animationCrip[animjump].SetLoopFlag(false);

	//アニメーションの初期化。
	m_animation.Init(
		*m_model,					//アニメーションを流すスキンモデル。
									//これでアニメーションとスキンモデルが関連付けされる。
		m_animationCrip,			//アニメーションクリップの配列。
		4							//アニメーションクリップの数。
	);


	//delete currentState;

	return true;
}

//template<class T>inline void AnimationController::ChangeState()
//{
//	////待機状態に切り替え。
//	//if (currentState != nullptr) {
//	//	//現在のステートを破棄する。
//	//	delete currentState;
//	//}
//	////次の状態のインスタンスを作成する。
//	//currentState = new T;
//}

void AnimationController::Update()
{
	/*if (m_animation.IsPlaying() == false) {
		m_animation.Play(animidle, 0.3f);
	}*/
	
	if (fabsf(g_pad->GetLStickXF()) > 0.001f || fabsf(g_pad->GetLStickYF()) > 0.001f)
	{
		m_isMove = true;
		if (m_isMove == true)
		{
			if (m_isJump == false) {

				if (m_isrun == false) {
					m_animation.Play(animwalk, 0.3f);
				}
				if (g_pad->IsPress(enButtonX)) {
					m_isrun = true;
					if (m_isrun == true)
					{
						m_animation.Play(animrun, 0.3f);
					}
				}
				else {
					m_isrun = false;
				}
			}
		}
		m_isMove = false;
	}
	
	if (fabsf(g_pad->GetLStickXF()) < 0.001f && fabsf(g_pad->GetLStickYF()) < 0.001f)
	{
		if (m_isJump == false) {
			m_animation.Play(animidle, 0.3f);
		}
		
	}
	
	if (g_pad->IsPress(enButtonA)) {
		m_isJump = true;
		if (m_isJump == true) {
			m_animation.Play(animjump, 0.3f);

		}
	}
	else {
		m_isJump = false;
	}
	
	

	//アニメーションを呼び出す

	m_animation.Update(1.0f / 30.0f);
}
