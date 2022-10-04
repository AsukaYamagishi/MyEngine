#pragma once
#include "SafeDelete.h"
#include "Code/DirectXBase/DirectXCommon.h"
#include <DirectXMath.h>
#include "Code/Audio/Audio.h"
#include "KeyboardInput.h"
#include "Sprite.h"

#include "Code/Scene/AbstructScene.h"

using namespace Microsoft::WRL;
using namespace DirectX;

//ゲームシーン
class Title :
	public AbstructScene
{
#pragma region 変数
private: //静的メンバ変数
	

private: //メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	
	//ゲームシーン用
	Sprite* spriteBG = nullptr;

#pragma endregion

#pragma region 静的メンバ関数

private: //静的メンバ関数
public: //静的メンバ関数
#pragma endregion

#pragma region ゲッター/セッター
	//a
#pragma endregion

#pragma region メンバ関数
public: //メンバ関数
	//コンストラクタ
	Title(DirectXCommon* dxCommon, Audio* audio);
	//デストラクタ
	~Title();
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="dxCommon">基礎</param>
	/// <param name="audio">音楽</param>
	void Init() override;
	//毎フレーム更新処理
	void Update() override;
	//描画
	void Draw() override;
#pragma endregion
};
