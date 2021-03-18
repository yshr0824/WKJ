#include "stdafx.h"
#include "WalkAnimation.h"

WalkAnimation::WalkAnimation()
{
}

WalkAnimation::~WalkAnimation()
{
}

bool WalkAnimation::Start()
{
	m_animationCrip.Load(L"Assets/animData/walk.tka");
	m_animationCrip.SetLoopFlag(true);

	
	return false;
}

void WalkAnimation::Update()
{
	m_animation.Play(0, 0.3f);

	//アニメーションを呼び出す

	m_animation.Update(1.0f / 30.0f);
}
