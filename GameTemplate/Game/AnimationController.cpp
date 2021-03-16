#include "stdafx.h"
#include "AnimationController.h"

AnimationController::AnimationController() 
{
	//�ҋ@�X�e�[�g�ɐ؂�ւ���B
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

	//�A�j���[�V�����̏������B
	m_animation.Init(
		*m_model,					//�A�j���[�V�����𗬂��X�L�����f���B
									//����ŃA�j���[�V�����ƃX�L�����f�����֘A�t�������B
		m_animationCrip,			//�A�j���[�V�����N���b�v�̔z��B
		4							//�A�j���[�V�����N���b�v�̐��B
	);

	return true;
}

template<class T>inline void AnimationController::ChangeState()
{
	//�ҋ@��Ԃɐ؂�ւ��B
	if (currentState != nullptr) {
		//���݂̃X�e�[�g��j������B
		delete currentState;
	}
	//���̏�Ԃ̃C���X�^���X���쐬����B
	currentState = new T;
}

void AnimationController::Update()
{

	//���݂̏�Ԃɂ���ď������ς��X�V���������s�B
	currentState->Update();
	if (GetAsyncKeyState('J')) {
		//���݂̏�ԂɃW�����v�\���₢���킹���s���B
		if (currentState->IsPossibleJump()) {
			m_animation.Play(animjump, 0.3f);
		}
	}
	//���݂̏�Ԃ����G���₢���킹���s���B
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
	
	

	//�A�j���[�V�������Ăяo��

	m_animation.Update(1.0f / 30.0f);
}
