#pragma once
#include "GameObject.h"
#include <vector>

class GameObjectManager
{
#pragma region 関数
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameObjectManager(DirectXCommon* dxCommon);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameObjectManager();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="dxCommon">基礎部分</param>
	void Init();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// オブジェクトをvectorに追加
	/// </summary>
	template<class T, class...Args>
	T* AddGameObject(Args... args) {
		T* obj = new T(args...);
		objects.emplace_back(obj);
		return obj;
	};

#pragma endregion

#pragma region 変数
private:
	DirectXCommon* dxCommon = nullptr;

	//ゲームオブジェクト
	std::vector<std::shared_ptr<GameObject>> objects;
#pragma endregion
};

