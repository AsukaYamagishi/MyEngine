#pragma once
#include "../../DirectXBase/DirectXCommon.h"
#include "../Vector3.h"
#include "../../GameObject/GameObjectBase.h"
#include "../../3d/Obj/ObjDraw.h"
#include "../ModelManager.h"

class Bullet
	:public GameObjectBase
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
	Bullet(DirectXCommon* dxCommon, std::weak_ptr<CollisionManager> collisionManager, Vector3 startPos, Vector3 shotVelocity);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Bullet();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="dxCommon">基礎</param>
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
#pragma endregion

#pragma region 変数
private:
	//バレットモデル
	std::shared_ptr<ObjDraw> bullet;
	//移動量
	Vector3 velocity = { 0,0,0 };
	//生存時間
	int liveTimer = 0;

};

