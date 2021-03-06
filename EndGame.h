#pragma once
#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Sprite.h"
#include "CalculationObject.h"
#include "DebugText.h"
#include "Audio.h"
#include "KeyboardInput.h"
#include "ModelDraw.h"

#include "AbstructScene.h"

using namespace Microsoft::WRL;
using namespace DirectX;

//ゲームシーン
class EndGame :
	public AbstructScene
{
#pragma region 変数
private: //静的メンバ変数
	

private: //メンバ変数
	DirectXCommon* dxCommon = nullptr;
	KeyboardInput* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;

	//ゲームシーン用
	Sprite* spriteBG = nullptr;
	Sprite* sprite1 = nullptr;

	//Audio::SoundData soundData[2];
#pragma endregion

#pragma region 関数
public: //メンバ関数
	//コンストラクタ
	EndGame();
	//デストラクタ
	~EndGame();
	//初期化
	void Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio) override;
	//毎フレーム更新処理
	void Update() override;
	//描画
	void Draw() override;
#pragma endregion
};

