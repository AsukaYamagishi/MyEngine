#pragma once
#include <stack>
#include "../Scene/TitleScene.h"
#include "../Scene/GameScene.h"
#include "../Scene/EndScene.h"

class SceneManager
{
public:    //サブクラス
	//シーン遷移番号
	enum SceneNo {
		TITLE,
		GAMEPLAY,
		END,

		MAX //最大数管理
	};

#pragma region 変数
private: //メンバ変数
	static DirectXCommon* dxCommon;
	static Audio* audio;
private: //静的メンバ変数
	static std::stack<AbstructScene *> scenes; //シーンスタック
#pragma endregion

#pragma region 静的メンバ関数
public: //静的メンバ関数
	/// <summary>
	/// シーンチェンジ
	/// </summary>
	/// <param name="sceneNo">シーン名</param>
	/// <param name="sceneStackClear">全てのシーンを初期化するか</param>
	static void ChangeScene(SceneNo sceneNo,bool sceneStackClear = false);
#pragma endregion

#pragma region メンバ関数
public: //メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="dxCommon">DirectX基礎</param>
	/// <param name="audio">音楽リソース</param>
	SceneManager(DirectXCommon* dxCommon, Audio* audio);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneManager();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	
	/// <summary>
	/// 毎フレーム更新処理
	/// </summary>
	void Update();
	
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
#pragma endregion
};

