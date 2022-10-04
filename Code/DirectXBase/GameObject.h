#pragma once
#include "DirectXCommon.h"
#include "../Vector3.h"
#include "../Collision/CollisionInfo.h"

class CollisionManager;
class GameObjectManager;

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
	/// マネージャのセット
	/// </summary>
	/// <param name="gameObjectManager"></param>
	static void SetManager(std::weak_ptr<GameObjectManager> gameObjectManager);

	/// <summary>
	/// オブジェクト生成関数
	/// </summary>
	/// <typeparam name="Object">生成したいオブジェクトテンプレート</typeparam>
	/// <typeparam name="...Args">可変長引数テンプレート</typeparam>
	/// <returns></returns>
	template<class Object,class ...Args>
	static Object* Create(Args ...args);

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
	
	// 自分が所属しているマネージャー
	static std::weak_ptr<GameObjectManager> gameObjectManager;
	std::vector<std::shared_ptr<BaseCollider>> colliders;

};

template<class Object, class ...Args>
inline Object* GameObject::Create(Args ...args)
{
	Object* obj = new Object(args...);
	gameObjectManager.lock()->AddGameObject(obj);
	return obj;
}
