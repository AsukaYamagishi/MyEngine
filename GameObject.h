#pragma once
#include "DirectXCommon.h"
#include "Vector3.h"
#include "CollisionInfo.h"

class CollisionManager;

class GameObject
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
	GameObject(DirectXCommon* dxCommon);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameObject();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="dxCommon">基礎</param>
	virtual void Init();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	void AddCollider(std::shared_ptr<BaseCollider> collider, std::weak_ptr<CollisionManager>  collisionManager);
	virtual void OnCollision(CollisionInfo info) {	}

	Vector3 GetPos() { return pos; }

	bool GetDeleteFlag() { return deleteFlag; }
#pragma endregion

#pragma region 変数
protected:
	DirectXCommon* dxCommon = nullptr;
	//削除フラグ
	bool deleteFlag = false;

	//座標
	Vector3 pos = { 0,0,0 };
	
	std::vector<std::shared_ptr<BaseCollider>> colliders;
};

