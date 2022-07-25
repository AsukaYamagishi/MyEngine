#pragma once
#include "SafeDelete.h"
#include "DirectXCommon.h"
#include "ModelDraw.h"
#include "ModelManager.h"
#include <DirectXMath.h>

class Player {
#pragma region 定数
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
#pragma endregion

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="dxCommon">基礎部分</param>
	void Init(DirectXCommon *dxCommon);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();
#pragma endregion

#pragma region 変数
public:
	ModelDraw *player = nullptr;
	
private:
	DirectXCommon *dxCommon = nullptr;
	float move = 0.5f;
	int hp = 10;
#pragma endregion
};