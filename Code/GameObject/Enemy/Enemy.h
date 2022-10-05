#pragma once
#include "../../GameObject/GameObjectBase.h"
#include "../../Manager/GameObjectManager.h"
#include "../../3d/Obj/ObjDraw.h"
#include "../../Manager/ModelManager.h"
#include "../Player/PlayerBase.h"


class Enemy :
    public GameObjectBase
{
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
	Enemy(DirectXCommon* dxCommon, std::weak_ptr<GameObjectManager> gameObjManager, std::weak_ptr<CollisionManager> collisionManager, Vector3 startPos, PlayerBase* player);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy();

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

#pragma endregion

#pragma region 変数
private:
	std::weak_ptr<GameObjectManager> gameObjManager;
	std::weak_ptr<CollisionManager> collisionManager;

	//モデル
	std::shared_ptr<ObjDraw> enemy;
	//1fのキー入力に対する移動量
	float move = -0.1f;
	//1f内での合計移動量
	Vector3 velocity = { 0,0,0 };

	PlayerBase* player;

	int liveTime = 0;	//生存時間
#pragma endregion
};

