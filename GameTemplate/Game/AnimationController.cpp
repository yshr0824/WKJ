#include "stdafx.h"
#include "AnimationController.h"

AnimationController::AnimationController() 
{
	//待機ステートに切り替える。
	m_animation.Play(animwalk, 0.3f);
}

AnimationController::~AnimationController()
{
	delete currentState;
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

	return true;
}

template<class T>inline void AnimationController::ChangeState()
{
	//待機状態に切り替え。
	if (currentState != nullptr) {
		//現在のステートを破棄する。
		delete currentState;
	}
	//次の状態のインスタンスを作成する。
	currentState = new T;
}

void AnimationController::Update()
{

	//現在の状態によって処理が変わる更新処理を実行。
	currentState->Update();
	if (GetAsyncKeyState('J')) {
		//現在の状態にジャンプ可能か問い合わせを行う。
		if (currentState->IsPossibleJump()) {
			m_animation.Play(animjump, 0.3f);
		}
	}
	//現在の状態が無敵か問い合わせを行う。
	if (currentState->IsInvincible()) {
	}


	if (g_pad->IsPress(enButtonY)) {
		m_animation.Play(animwalk, 0.3f);
	}

	if (g_pad->IsPress(enButtonX)) {
		m_animation.Play(animrun, 0.3f);
	}

	if (g_pad->IsTrigger(enButtonA)) {
		m_animation.Play(animjump, 0.3f);
	}
	
	

	//アニメーションを呼び出す

	m_animation.Update(1.0f / 30.0f);
}
