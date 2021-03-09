#include "stdafx.h"
#include "ShadowMap.h"


ShadowMap::ShadowMap()
{
	
}
ShadowMap::~ShadowMap()
{
}

void ShadowMap::Init()
{
	//�V���h�E�}�b�v�����p�̃����_�����O�^�[�Q�b�g���쐬�B
	//�𑜓x��2048�~2048�B
	//�e�N�X�`���̃t�H�[�}�b�g��R�����݂̂�32bit���������_�^�B //�V���h�[�}�b�v��R�����݂̂ł����B
	m_shadowMapRT.Create(
		1280,
		720,
		DXGI_FORMAT_R32_FLOAT
	);
}

void ShadowMap::RenderToShadowMap()
{
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//�����_�����O�^�[�Q�b�g��؂�ւ���B
	ID3D11RenderTargetView* rts[] = {
		m_shadowMapRT.GetRenderTargetView()
	};
	d3dDeviceContext->OMSetRenderTargets(1, rts, m_shadowMapRT.GetDepthStensilView());
	//�r���[�|�[�g��ݒ�B
	d3dDeviceContext->RSSetViewports(1, m_shadowMapRT.GetViewport());
	//�V���h�E�}�b�v���N���A�B
	//��ԉ���Z��1.0�Ȃ̂ŁA1.0�œh��Ԃ��B
	float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //red,green,blue,alpha
	m_shadowMapRT.ClearRenderTarget(clearColor);

	//�V���h�E�L���X�^�[���V���h�E�}�b�v�Ƀ����_�����O�B
	for (auto& caster : m_shadowCasters) {
		caster->Draw(
			m_lightViewMatrix,
			m_lightProjMatrix,
			2
		);
	}
	//�L���X�^�[���N���A
	m_shadowCasters.clear();
}
void ShadowMap::Update(CVector3 lightCameraPos, CVector3 lightCameraTarget)
{
	m_lightCameraTarget = lightCameraTarget;
	m_lightCameraPosition = lightCameraPos;

	//���C�g�̕������v�Z����B
	auto lightDir = m_lightCameraTarget - m_lightCameraPosition;
	if (lightDir.Length() < 0.0001f) {
		//���C�g�J�����̒����_�Ǝ��_���߂�����B
		//���炭�o�O�Ȃ̂ŁA�N���b�V��������B
		std::abort();
	}
	//���K�����āA�����x�N�g���ɕϊ�����B
	lightDir.Normalize();
	//���C�g�̕����ɂ���āA���C�g�J�����̏���������߂�B
	CVector3 lightCameraUpAxis;
	if (fabsf(lightDir.y) > 0.99998f) {
		//�قڐ^��or�^���������Ă���̂ŁA1,0,0��������Ƃ���B
		lightCameraUpAxis = CVector3::AxisX();
	}
	else {
		//�^��������Ă��Ȃ��Ƃ��́A0,1,0��������Ƃ���B
		lightCameraUpAxis = CVector3::AxisY();
	}
	//�J�����̏���������܂����̂ŁA���C�g�r���[�s����v�Z����B
	m_lightViewMatrix.MakeLookAt(
		m_lightCameraPosition,	//���_(���C�g�̈ʒu)
		m_lightCameraTarget,	//�����_(���C�g�̌��Ă���^�[�Q�b�g)
		lightCameraUpAxis		//�J�����̏����
								//���(0,1,0)��NG
	);

	//���C�g�v���W�F�N�V�����s����쐬����B
	//���z������̉e�𗎂Ƃ������Ȃ�A���s���e�s����쐬����B
	m_lightProjMatrix.MakeOrthoProjectionMatrix(
		3000,
		3000,
		0.1f,
		5000.0f
	);
}


