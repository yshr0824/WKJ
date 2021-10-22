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
	//�A�j���[�V�����̏������B
	m_idleanimation.Init(
		*m_model,					//�A�j���[�V�����𗬂��X�L�����f���B
									//����ŃA�j���[�V�����ƃX�L�����f�����֘A�t�������B
		m_animationCrip,			//�A�j���[�V�����N���b�v�̔z��B
		1							//�A�j���[�V�����N���b�v�̐��B
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

	//�A�j���[�V�������Ăяo��

	m_idleanimation.Update(1.0f / 30.0f);

}
