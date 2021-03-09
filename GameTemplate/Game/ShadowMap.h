#pragma once
#include "RenderTarget.h"

class SkinModel;
class ShadowMap 
{
public:
	ShadowMap();
	~ShadowMap();
	/// <summary>
	/// ライトビュー行列と、ライトプロジェクション行列を更新。
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
	//初期化を明示的に呼ぶ関数
	void Init();
	/// <summary>
	/// シャドウマップにライトから見た深度値を書き込む。
	/// </summary>
	void RenderToShadowMap();
	void RegistShadowCaster(SkinModel* shadowCaster)
	{
		m_shadowCasters.push_back(shadowCaster);
	}
	/// <summary>
	/// シャドウマップのSRVを取得。
	/// </summary>
	/// <returns>シャドウマップのSRV</returns>
	ID3D11ShaderResourceView* GetShadowMapSRV()
	{
		return m_shadowMapRT.GetRenderTargetSRV();
	}
private:
	CVector3 m_lightCameraPosition;					//ライトカメラの視点。
	CVector3 m_lightCameraTarget;					//ライトカメラの注視点。
	CMatrix m_lightViewMatrix;						//ライトビュー行列。
	CMatrix m_lightProjMatrix;						//ライトプロジェクション行列。
	RenderTarget m_shadowMapRT;						//シャドウマップを描画するレンダリングターゲット。
	std::vector< SkinModel*> m_shadowCasters;		//シャドウキャスターの配列。
};

