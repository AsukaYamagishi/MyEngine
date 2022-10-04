#pragma once
#include "SafeDelete.h"
#include "Code/DirectXBase/DirectXCommon.h"
#include "ModelDraw.h"
#include "ModelManager.h"
#include <DirectXMath.h>
#include "GameObject.h"
#include "GameObjectManager.h"

enum class PlayerType {
	MELLE, //近距離
	SHOT, //遠距離
};

class PlayerBase 
	: public GameObject{
#pragma region 定数
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
#pragma endregion

#pragma region 関数
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerBase(DirectXCommon* dxCommon,std::shared_ptr<CollisionManager> collisionManager, PlayerType type);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerBase();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="dxCommon">基礎部分</param>
	void Init() override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	void OnCollision(CollisionInfo info) override;
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
	std::weak_ptr<CollisionManager> collisionManager;
	
	//プレイヤーモデル
	std::shared_ptr<ModelDraw> player;
	//攻撃タイプ
	PlayerType type;
	//1fのキー入力に対する移動量
	float move = 0.5f;
	//1f内での合計移動量
	Vector3 velocity = { 0,0,0 };
	
	//体力
	int hp = 100;

	//前後への移動量
	float flontMove;
#pragma endregion
};