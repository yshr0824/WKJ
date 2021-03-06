#include "stdafx.h"
#include "RenderTarget.h"

RenderTarget::RenderTarget()
{
}

RenderTarget::~RenderTarget()
{
	Release();
}

void RenderTarget::Release()
{
	if (m_depthStencilView != nullptr) {
		m_depthStencilView->Release();
		m_depthStencilView = nullptr;
	}
	if (m_depthStencilTex != nullptr) {
		m_depthStencilTex->Release();
		m_depthStencilTex = nullptr;
	}

	if (m_renderTargetView != nullptr) {
		m_renderTargetView->Release();
		m_renderTargetView = nullptr;
	}
	if (m_renderTargetTex != nullptr) {
		m_renderTargetTex->Release();
		m_renderTargetTex = nullptr;
	}
	if (m_renderTargetSRV != nullptr) {
		m_renderTargetSRV->Release();
	}
}

void RenderTarget::Create(unsigned int w, unsigned int h, DXGI_FORMAT texFormat)
{
	//D3Dデバイスを取得。
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	//1.レンダリングターゲットとなるテクスチャを作成。
	D3D11_TEXTURE2D_DESC texDesc = { 0 };

	//////////////////////////////////////////////////////////////
	//ここからテクスチャ作成。
	//////////////////////////////////////////////////////////////
	//〇テクスチャの横の解像度。
	texDesc.Width = 1280;
	//〇テクスチャの縦の解像度。
	texDesc.Height = 720;
	//×ミップマップレベル。1でいい。
	texDesc.MipLevels = 1;
	//〇テクスチャ配列のサイズ。1でいい。
	texDesc.ArraySize = 1;
	//×テクスチャのフォーマット。
	//×RGBAの各要素8bitの32bitフォーマットにする。
	//×このパラメータは今後変更するので、注目。
	//R8G8B8A8 = R=8bit G=8bit B=8bit A=8bit  変更する(例 R16G16B16, R32G32B32A32)
	texDesc.Format = texFormat;
	//×テクスチャの使用用途を決める。
	//×レンダリングターゲットのテクスチャは、
	//×レンダリングターゲット、ShaderResourceView、UnorderedAccessViewとしてバインドする。
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
	//×マルチサンプリングの数。1でいい。
	texDesc.SampleDesc.Count = 1;
	//×マルチサンプリングの品質。0でいい。
	texDesc.SampleDesc.Quality = 0;
	//〇テクスチャの読み書きのされ方。D3D11_USAGE_DEFAULTでいい。
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	//〇CPUからのアクセスの仕方。アクセスしないので0でよい。
	texDesc.CPUAccessFlags = 0;
	//×0でよい。
	texDesc.MiscFlags = 0;
	//〇テクスチャを作成。
	d3dDevice->CreateTexture2D(&texDesc, nullptr, &m_renderTargetTex);

	//2.レンダリングターゲットビューの作成

		//////////////////////////////////////////////////////////////
		//ここからレンダリングターゲットビューの作成。
		//////////////////////////////////////////////////////////////
		//〇レンダリングターゲットビューを作成するためのデータを設定する。。
	D3D11_RENDER_TARGET_VIEW_DESC viewDesc;
	//〇フォーマットはテクスチャと同じにする。
	viewDesc.Format = texDesc.Format;
	//〇2Dテクスチャを扱うことを指定する。
	viewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	//×0でいい。
	viewDesc.Texture2D.MipSlice = 0;
	//〇レンダリングターゲットビューの作成。
	d3dDevice->CreateRenderTargetView(m_renderTargetTex, &viewDesc, &m_renderTargetView);

	//3.シェーダーリソースビューの作成


		//////////////////////////////////////////////////////////////a
		//ここからシェーダーリソースビューの作成。
		//////////////////////////////////////////////////////////////

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	//〇フォーマットはテクスチャと同じでよい。
	srvDesc.Format = texDesc.Format;
	//〇2次元テクスチャとして扱う。
	srvDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
	//〇ミップマップレベルもテクスチャと同じでよい。
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
	//×0でいい。
	srvDesc.Texture2D.MostDetailedMip = 0;
	//〇SRVを作成する。
	d3dDevice->CreateShaderResourceView(m_renderTargetTex, &srvDesc, &m_renderTargetSRV);

	//4.デプスステンシルテクスチャの作成
	D3D11_TEXTURE2D_DESC depthTexDesc = texDesc;

	//////////////////////////////////////////////////////////////
	//ここからデプスステンシルテクスチャの作成。
	//////////////////////////////////////////////////////////////
	//〇デプスステンシルビューにバインドする。
	depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	//×32bit浮動小数点のデプスステンシルバッファを作成する。
	depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
	//〇デプスステンシルテクスチャを作成する。
	d3dDevice->CreateTexture2D(&depthTexDesc, nullptr, &m_depthStencilTex);

	//5.デプスステンシルビューの作成

		//////////////////////////////////////////////////////////////
		//ここからデプスステンシルビューの作成。
		//////////////////////////////////////////////////////////////
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	//〇フォーマットは深度ステンシルと同じにする。
	depthStencilViewDesc.Format = depthTexDesc.Format;
	//〇2Dテクスチャを扱うことを指定する。
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	//×0でいい。
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	//×0でいい。
	depthStencilViewDesc.Flags = 0;
	//〇デプスステンシルビューを作成。
	d3dDevice->CreateDepthStencilView(m_depthStencilTex, &depthStencilViewDesc, &m_depthStencilView);
	//6.todo ビューポート。
	{
		m_viewport.TopLeftX = 0;
		m_viewport.TopLeftY = 0;
		m_viewport.Width = w;
		m_viewport.Height = h;
		m_viewport.MinDepth = 0.0f;
		m_viewport.MaxDepth = 1.0f;
	}
}

void RenderTarget::ClearRenderTarget(float* clearColor)
{
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();

	d3dDeviceContext->ClearRenderTargetView(m_renderTargetView, clearColor);
	d3dDeviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}