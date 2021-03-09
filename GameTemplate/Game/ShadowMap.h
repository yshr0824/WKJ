#pragma once
#include "RenderTarget.h"

class SkinModel;
class ShadowMap 
{
public:
	ShadowMap();
	~ShadowMap();
	/// <summary>
	/// ���C�g�r���[�s��ƁA���C�g�v���W�F�N�V�����s����X�V�B
	/// 
	CMatrix GetLighViewMatrix() 
	{
		return m_lightViewMatrix;
	}
	CMatrix GetLightProjMatrix() 
	{
		return m_lightProjMatrix;
	}
	/// </summary>
	/// <param name="lightCameraPos"></param>
	/// <param name="lightCameraTarget"></param>
	void Update(CVector3 lightCameraPos, CVector3 lightCameraTarget);
	//�������𖾎��I�ɌĂԊ֐�
	void Init();
	/// <summary>
	/// �V���h�E�}�b�v�Ƀ��C�g���猩���[�x�l���������ށB
	/// </summary>
	void RenderToShadowMap();
	void RegistShadowCaster(SkinModel* shadowCaster)
	{
		m_shadowCasters.push_back(shadowCaster);
	}
	/// <summary>
	/// �V���h�E�}�b�v��SRV���擾�B
	/// </summary>
	/// <returns>�V���h�E�}�b�v��SRV</returns>
	ID3D11ShaderResourceView* GetShadowMapSRV()
	{
		return m_shadowMapRT.GetRenderTargetSRV();
	}
private:
	CVector3 m_lightCameraPosition;					//���C�g�J�����̎��_�B
	CVector3 m_lightCameraTarget;					//���C�g�J�����̒����_�B
	CMatrix m_lightViewMatrix;						//���C�g�r���[�s��B
	CMatrix m_lightProjMatrix;						//���C�g�v���W�F�N�V�����s��B
	RenderTarget m_shadowMapRT;						//�V���h�E�}�b�v��`�悷�郌���_�����O�^�[�Q�b�g�B
	std::vector< SkinModel*> m_shadowCasters;		//�V���h�E�L���X�^�[�̔z��B
};

