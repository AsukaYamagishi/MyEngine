#pragma once
#include <DirectXMath.h>
#include "AbstructScene.h"
#include "../DirectXBase/SafeDelete.h"
#include "../DirectXBase/DirectXCommon.h"
#include "../DirectXBase/DebugText.h"
#include "../Input/KeyboardInput.h"
#include "../Audio/Audio.h"
#include "../2d/Sprite.h"
#include "../3d/Obj/ObjDraw.h"

using namespace Microsoft::WRL;
using namespace DirectX;

//ゲームシーン
class EndScene :
	public AbstructScene
{
#pragma region 変数
private: //静的メンバ変数
	

private: //メンバ変数
	DirectXCommon* dxCommon = nullptr;
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
	EndScene(DirectXCommon* dxCommon, Audio* audio);
	//デストラクタ
	~EndScene();
	//初期化
	void Init() override;
	//毎フレーム更新処理
	void Update() override;
	//描画
	void Draw() override;
#pragma endregion
};

