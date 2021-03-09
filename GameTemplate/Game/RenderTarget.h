#pragma once
class RenderTarget
{
public:
	RenderTarget();
	~RenderTarget();
	void Release();
	void Create(unsigned int w, unsigned int h, DXGI_FORMAT texFormat);
	void ClearRenderTarget(float* clearColor);

	ID3D11RenderTargetView* GetRenderTargetView()
	{
		return m_renderTargetView;
	}
	ID3D11DepthStencilView* GetDepthStensilView()
	{
		return m_depthStencilView;
	}
	ID3D11ShaderResourceView* GetRenderTargetSRV()
	{
		return m_renderTargetSRV;
	}
	D3D11_VIEWPORT* GetViewport()
	{
		return &m_viewport;
	}
private:
	ID3D11Texture2D* m_renderTargetTex = nullptr;		//!<�����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`���B
	ID3D11RenderTargetView* m_renderTargetView = nullptr;		//!<�����_�[�^�[�Q�b�g�r���[�B
	ID3D11ShaderResourceView* m_renderTargetSRV = nullptr;		//!<�����_�����O�^�[�Q�b�g��SRV
	ID3D11Texture2D* m_depthStencilTex = nullptr;		//!<�f�v�X�X�e���V���ƂȂ�e�N�X�`���B
	ID3D11DepthStencilView* m_depthStencilView = nullptr;		//!<�f�v�X�X�e���V���r���[�B
	D3D11_VIEWPORT				m_viewport;							//!<�r���[�|�[�g�B
};