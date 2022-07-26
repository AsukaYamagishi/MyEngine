#pragma once
#include "SafeDelete.h"
#include "DirectXCommon.h"
#include "ModelDraw.h"
#include "ModelManager.h"
#include <DirectXMath.h>

enum class PlayerType {
	MELLE, //近距離
	SHOT, //遠距離
};

class PlayerBase {
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
	PlayerBase(PlayerType type, ModelInput* model);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerBase();

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


private:
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// 攻撃処理
	/// </summary>
	virtual void Attack();

#pragma endregion

#pragma region 変数
private:
	DirectXCommon *dxCommon = nullptr;
	
	//プレイヤーモデル
	std::shared_ptr<ModelDraw> player;
	//座標
	Vector3 pos = { 0,0,0 };
	//攻撃タイプ
	PlayerType type;
	//1fのキー入力に対する移動量
	float move = 0.3f;
	//1f内での合計移動量
	Vector3 velocity = { 0,0,0 };
	
	//体力
	int hp = 100;
#pragma endregion
};