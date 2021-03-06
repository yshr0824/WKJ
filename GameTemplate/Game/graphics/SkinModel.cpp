#include "stdafx.h"
#include "SkinModel.h"
#include "SkinModelDataManager.h"
#include "SkinModelEffect.h"

SkinModel::~SkinModel()
{
	if (m_cb != nullptr) {
		//定数バッファを解放。
		m_cb->Release();
	}
	if (m_samplerState != nullptr) {
		//サンプラステートを解放。
		m_samplerState->Release();
	}
	//ライト用の定数バッファの解放。
	if (m_lightCb != nullptr) {
		m_lightCb->Release();
	}
}
void SkinModel::Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis)
{
	//スケルトンのデータを読み込む。
	InitSkeleton(filePath);

	//定数バッファの作成。
	InitConstantBuffer();

	//サンプラステートの初期化。
	InitSamplerState();
	//ディレクションライトの初期化。
	InitDirectionLight();
	//深度ステートの初期化
	InitDepthStencilState();
	//SkinModelDataManagerを使用してCMOファイルのロード。
	m_modelDx = g_skinModelDataManager.Load(filePath, m_skeleton);

	m_enFbxUpAxis = enFbxUpAxis;
}
void SkinModel::InitSkeleton(const wchar_t* filePath)
{
	//スケルトンのデータを読み込む。
	//cmoファイルの拡張子をtksに変更する。
	std::wstring skeletonFilePath = filePath;
	//文字列から.cmoファイル始まる場所を検索。
	int pos = (int)skeletonFilePath.find(L".cmo");
	//.cmoファイルを.tksに置き換える。
	skeletonFilePath.replace(pos, 4, L".tks");
	//tksファイルをロードする。
	bool result = m_skeleton.Load(skeletonFilePath.c_str());
	if ( result == false ) {
		//スケルトンが読み込みに失敗した。
		//アニメーションしないモデルは、スケルトンが不要なので
		//読み込みに失敗することはあるので、ログ出力だけにしておく。
#ifdef _DEBUG
		char message[256];
		sprintf(message, "tksファイルの読み込みに失敗しました。%ls\n", skeletonFilePath.c_str());
		OutputDebugStringA(message);
#endif
	}
}
void SkinModel::InitDepthStencilState()
{
	//Hands-On 奥のモノを手前に描画する深度ステンシルステートを作ってみよう。
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = true;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	desc.DepthFunc = D3D11_COMPARISON_GREATER;
	desc.StencilEnable = false;
	desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//D3Dデバイスを取得。
	auto d3ddevice = g_graphicsEngine->GetD3DDevice();
	//デプスステンシルステートを作成。
	ID3D11DepthStencilState* depthStencilState;
	d3ddevice->CreateDepthStencilState(&desc, &depthStencilState);
}
void SkinModel::InitConstantBuffer()
{
	//作成するバッファのサイズをsizeof演算子で求める。
	int bufferSize = sizeof(SVSConstantBuffer);
	//どんなバッファを作成するのかをせてbufferDescに設定する。
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//０でクリア。
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//バッファで想定されている、読み込みおよび書き込み方法。
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//バッファは16バイトアライメントになっている必要がある。
																//アライメントって→バッファのサイズが16の倍数ということです。
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//バッファをどのようなパイプラインにバインドするかを指定する。
																//定数バッファにバインドするので、D3D11_BIND_CONSTANT_BUFFERを指定する。
	bufferDesc.CPUAccessFlags = 0;								//CPU アクセスのフラグです。
																//CPUアクセスが不要な場合は0。
	//作成。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_cb);
	//続いて、ライト用の定数バッファを作成。
		//作成するバッファのサイズを変更するだけ。
	bufferSize = sizeof(SLight);
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);
}
void SkinModel::InitDirectionLight()
{
	m_light.directionLight.direction[0] = { 1.0f, -1.0f, 0.0f, 0.0f };
	CVector4 cameralightpos = m_light.directionLight.direction[0]*-500.0f;
	m_light.directionLight.direction[0].Normalize();
	m_light.directionLight.color[0] = { 0.4f, 0.4f, 0.4f, 1.0f };

	m_light.directionLight.direction[1] = { -1.0f, 1.0f, 0.0f, 0.0f };
	m_light.directionLight.direction[1].Normalize();
	m_light.directionLight.color[1] = { 0.4f, 0.4f, 0.4f, 1.0f };

	m_light.directionLight.direction[2] = { 0.0f, -1.0f, 1.0f, 0.0f };
	m_light.directionLight.direction[2].Normalize();
	m_light.directionLight.color[2] = { 0.4f, 0.4f, 0.4f, 1.0f };

	m_light.directionLight.direction[3] = { 1.0f, 1.0f, -1.0f, 0.0f };
	m_light.directionLight.direction[3].Normalize();
	m_light.directionLight.color[3] = { 0.4f, 0.4f, 0.4f, 1.0f };

	m_light.specPow = 15.0f;
}
void SkinModel::InitSamplerState()
{
	//テクスチャのサンプリング方法を指定するためのサンプラステートを作成。
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}
void SkinModel::UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale)
{
	//3dsMaxと軸を合わせるためのバイアス。
	CMatrix mBias = CMatrix::Identity();
	if (m_enFbxUpAxis == enFbxUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(CMath::PI * -0.5f);
	}
	CMatrix transMatrix, rotMatrix, scaleMatrix;
	//平行移動行列を作成する。
	transMatrix.MakeTranslation( position );
	//回転行列を作成する。
	rotMatrix.MakeRotationFromQuaternion( rotation );
	rotMatrix.Mul(mBias, rotMatrix);
	//拡大行列を作成する。
	scaleMatrix.MakeScaling(scale);
	//ワールド行列を作成する。
	//拡大×回転×平行移動の順番で乗算するように！
	//順番を間違えたら結果が変わるよ。
	m_worldMatrix.Mul(scaleMatrix, rotMatrix);
	m_worldMatrix.Mul(m_worldMatrix, transMatrix);

	//スケルトンの更新。
	m_skeleton.Update(m_worldMatrix);
}
void SkinModel::Draw( CMatrix viewMatrix, CMatrix projMatrix,int renderMode)
{
	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());

	ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();

	auto shadowMap = g_goMgr.GetShadowMap();
	//定数バッファの内容を更新。
	SVSConstantBuffer vsCb;
	vsCb.mWorld = m_worldMatrix;
	vsCb.mProj = projMatrix;
	vsCb.mView = viewMatrix;

	//ライトカメラのビュー、プロジェクション行列を送る。
	vsCb.mLightProj = shadowMap->GetLightProjMatrix();
	vsCb.mLightView = shadowMap->GetLighViewMatrix();
	if (m_isShadowReciever == true) {
		vsCb.isShadowReciever = 1;
	}
	else {
		vsCb.isShadowReciever = 0;
	}

	d3dDeviceContext->UpdateSubresource(m_cb, 0, nullptr, &vsCb, 0, 0);
	//視点を設定
	m_light.eyePos = g_camera3D.GetPosition();
	//ライト用の定数バッファを更新。
	d3dDeviceContext->UpdateSubresource(m_lightCb, 0, nullptr, &m_light, 0, 0);
	//定数バッファをGPUに転送。
	d3dDeviceContext->VSSetConstantBuffers(0, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(0, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(2, 1, &m_lightCb);
	//サンプラステートを設定。
	d3dDeviceContext->PSSetSamplers(0, 1, &m_samplerState);
	//ボーン行列をGPUに転送。
	m_skeleton.SendBoneMatrixArrayToGPU();

	//エフェクトにクエリを行う。
	m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
		auto modelMaterial = reinterpret_cast<SkinModelEffect*>(material);
		modelMaterial->SetRenderMode(renderMode);
	});

	//描画。
	m_modelDx->Draw(
		d3dDeviceContext,
		state,
		m_worldMatrix,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
		/*viewMatrix,
		projMatrix*/
	);
}