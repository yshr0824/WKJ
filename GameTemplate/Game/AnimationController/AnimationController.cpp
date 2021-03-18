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

	//�A�j���[�V�����̏������B
	m_animation.Init(
		*m_model,					//�A�j���[�V�����𗬂��X�L�����f���B
									//����ŃA�j���[�V�����ƃX�L�����f�����֘A�t�������B
		m_animationCrip,			//�A�j���[�V�����N���b�v�̔z��B
		4							//�A�j���[�V�����N���b�v�̐��B
	);


	//delete currentState;

	return true;
}

//template<class T>inline void AnimationController::ChangeState()
//{
//	////�ҋ@��Ԃɐ؂�ւ��B
//	//if (currentState != nullptr) {
//	//	//���݂̃X�e�[�g��j������B
//	//	delete currentState;
//	//}
//	////���̏�Ԃ̃C���X�^���X���쐬����B
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
	
	

	//�A�j���[�V�������Ăяo��

	m_animation.Update(1.0f / 30.0f);
}
