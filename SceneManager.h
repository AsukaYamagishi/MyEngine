#pragma once
#include "GameScene.h"
#include "Title.h"
#include "EndGame.h"

#include <stack>

class SceneManager
{

public:    //サブクラス
	//シーン遷移番号
	enum SceneNo {
		titleScene,
		gameScene,
		endScene,

		MAX
	};

#pragma region 変数
private: //メンバ変数
	static DirectXCommon* dxCommon;
	static KeyboardInput* input;
	static Audio* audio;
	//GameScene* game = nullptr;
	//Title* title = nullptr;
	//EndGame* end = nullptr;

	//SceneNo sceneNo;

#pragma endregion

#pragma region 静的メンバ関数

private: //静的メンバ関数
	static std::stack<AbstructScene *> scenes;
public: //静的メンバ関数
	static void ChangeScene(SceneNo sceneNo,bool sceneStackClear = false);
#pragma endregion
#pragma region ゲッター/セッター
	//a
#pragma endregion

#pragma region メンバ関数
public: //メンバ関数
	//コンストラクタ
	SceneManager();
	//デストラクタ
	~SceneManager();
	//初期化
	void Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio);
	//毎フレーム更新処理
	void Update();
	//描画
	void Draw();
#pragma endregion
};

