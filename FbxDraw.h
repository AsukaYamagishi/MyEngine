#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>

#include "FbxModel.h"
#include "FbxInput.h"
#include "Code/Camera/Camera.h"

class FbxDraw
{
#pragma region 定数
protected: //エイリアス
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;


public: //定数
	//ボーンの最大数
	static const int MAX_BONES = 32;

public: //サブクラス
	//定数バッファ用データ構造体(座標変換行列用)
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
	};
	//定数バッファ用データ構造体(スキニング)
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};
#pragma endregion

#pragma region 関数
public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 毎フレーム更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// モデルのセット
	/// </summary>
	/// <param name="model">FBXモデル</param>
	void SetModel(FbxModel* model) { this->model = model; }

	/// <summary>
	/// アニメーション再生
	/// </summary>
	/// <param name="isLoop">ループするか</param>
	void PlayAnimation(bool isLoop = false);

	/// <summary>
	/// アニメーション再生停止
	/// </summary>
	void StopAnimation() { isPlay = false; }

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void Draw(ID3D12GraphicsCommandList* cmdList);


	//ゲッター
	Vector3 GetScale() { return scale; }
	Vector3 GetPosition() { return position; }
	Vector3 GetRotation() { return rotation; }

	//セッター
	void SetScale(Vector3 nextScale) { scale = nextScale; }
	void SetPosition(Vector3 nextPos) { position = nextPos; }
	void SetRotation(Vector3 nextRotate) { rotation = nextRotate; }

public: //静的メンバ関数
	//セッター
	static void SetDevice(ID3D12Device* dev) { FbxDraw::dev = dev; }
	static void SetCamera(Camera* cam) { FbxDraw::cam = cam; }

	/// <summary>
	/// グラフィックスパイプラインの生成
	/// </summary>
	static void CreateGraphicsPipeline();
#pragma endregion
	
#pragma region 変数
protected: //メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource> constBuffTransform;
	//定数バッファ(スキン)
	ComPtr<ID3D12Resource> constBuffSkin;

private: //静的メンバ変数
	//デバイス
	static ID3D12Device* dev;
	//カメラ
	static Camera* cam;
	//ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootSignature;
	//パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelineState;

	//ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	//xyz軸周りのローカル回転角
	XMFLOAT3 rotation = { 0,0,0 };
	//ローカル座標
	XMFLOAT3 position = { 0,0,0 };
	//ローカルワールド変換行列
	XMMATRIX matWorld;
	//モデル
	FbxModel* model = nullptr;
	//1フレームの時間
	FbxTime frameTime;
	//アニメーション開始時間
	FbxTime startTime;
	//アニメーション終了時間
	FbxTime endTime;
	//現在時間(アニメーション)
	FbxTime currentTime;
	//アニメーション再生中
	bool isPlay = false;
	//アニメーションループ再生
	bool isLoop = false;
#pragma endregion
};

