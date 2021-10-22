#include "stdafx.h"
#include "IdleAnimation.h"
#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"
IdleAnimation::IdleAnimation()
{



}

IdleAnimation::~IdleAnimation()
{

}

void IdleAnimation::Enter()
{
	m_animationCrip[0].Load(L"Assets/animData/idle.tka");
	m_animationCrip[0].SetLoopFlag(true);

	//m_idleanimation = m_animcontroller->GetAnimation();
	//アニメーションの初期化。
	m_idleanimation.Init(
		*m_model,					//アニメーションを流すスキンモデル。
									//これでアニメーションとスキンモデルが関連付けされる。
		m_animationCrip,			//アニメーションクリップの配列。
		1							//アニメーションクリップの数。
	);
}

void IdleAnimation::Leave()
{
}

bool IdleAnimation::Start()
{


	return true;
}

void IdleAnimation::Update()
{
	m_idleanimation.Play(0, 0.3f);

	//アニメーションを呼び出す

	m_idleanimation.Update(1.0f / 30.0f);

}
